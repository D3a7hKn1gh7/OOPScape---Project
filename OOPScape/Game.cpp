#include "Game.h"
#include "Knight.h"
#include "ChaserEnemy.h"
#include "ConsoleUtils.h"
#include <iostream>

Game::Game() = default;

void Game::loadLevel(const std::string& filename)
{
    enableAnsiColors();
    board.loadFromFile(filename);

    hero = std::make_unique<Knight>(board.getStartPosition(), 100, 3);
    board.set(hero->getPosition().x, hero->getPosition().y, ' ');

    enemies.clear();
    for (const Point& p : board.getEnemyPositions())
    {
        enemies.push_back(std::make_unique<ChaserEnemy>(p));
        board.set(p.x, p.y, ' ');
    }

    traps.clear();
    for (const Point& p : board.getTrapPositions())
    {
        traps.push_back(Trap{ p, 25, false });
        board.set(p.x, p.y, ' ');
    }

    explored.assign(board.size(), std::vector<bool>(board.size(), false));

    gameOver = false;
    playerWon = false;

    updateFog();
}

void Game::updateFog()
{
    Point heroPos = hero->getPosition();
    for (int y = 0; y < board.size(); ++y)
    {
        for (int x = 0; x < board.size(); ++x)
        {
            int dx = x - heroPos.x;
            int dy = y - heroPos.y;
            if (dx * dx + dy * dy <= fogRadius * fogRadius)
                explored[y][x] = true;
        }
    }
}

void Game::printBoard() const
{
    system("cls");
    Point heroPos = hero->getPosition();

    for (int y = 0; y < board.size(); ++y)
    {
        for (int x = 0; x < board.size(); ++x)
        {
            Point cur{ x, y };

            int dx = x - heroPos.x;
            int dy = y - heroPos.y;
            bool inRange = (dx * dx + dy * dy <= fogRadius * fogRadius);

            if (!explored[y][x])
            {
                std::cout << ' ';
                continue;
            }

            if (cur == heroPos)
            {
                std::cout << (hero->isInvulnerable() ? Color::Cyan : Color::Green);
                std::cout << (hero->isInvulnerable() ? 'K' : 'H');
                std::cout << Color::Reset;
                continue;
            }

            if (inRange)
            {
                bool isEnemyHere = false;
                for (const auto& e : enemies)
                {
                    if (e->isAlive() && e->getPosition() == cur)
                    {
                        isEnemyHere = true;
                        break;
                    }
                }
                if (isEnemyHere)
                {
                    std::cout << Color::Red << 'E' << Color::Reset;
                    continue;
                }

                bool isTrapHere = false;
                for (const auto& t : traps)
                {
                    if (!t.triggered && t.position == cur)
                    {
                        isTrapHere = true;
                        break;
                    }
                }
                if (isTrapHere)
                {
                    std::cout << Color::Yellow << 'T' << Color::Reset;
                    continue;
                }
            }

            char cell = board.at(x, y);
            if (cell == 'F')
                std::cout << Color::Yellow << cell << Color::Reset;
            else
                std::cout << cell;
        }
        std::cout << "\n";
    }

    int hp = hero->getHealth();
    int maxHp = 100;
    int barLength = 20;
    int filled = (hp * barLength) / maxHp;

    std::cout << "HP: [";
    std::cout << Color::Green;
    for (int i = 0; i < filled; ++i)
        std::cout << '#';
    std::cout << Color::Reset;
    for (int i = filled; i < barLength; ++i)
        std::cout << '.';
    std::cout << "] " << hp << "/" << maxHp;

    if (hero->isInvulnerable())
        std::cout << Color::Cyan << " [shield active]" << Color::Reset;
    std::cout << "\n";
}

void Game::moveHero(int dx, int dy)
{
    Point pos = hero->getPosition();
    int nx = pos.x + dx;
    int ny = pos.y + dy;

    if (!board.isInside(nx, ny))
    {
        std::cout << "Cannot move outside the board.\n";
        return;
    }

    if (board.at(nx, ny) == '*')
    {
        std::cout << "There is a wall in the way.\n";
        return;
    }

    hero->setPosition(Point{ nx, ny });
}

void Game::checkHeroAgainstTrap()
{
    Point pos = hero->getPosition();
    for (Trap& trap : traps)
    {
        if (!trap.triggered && trap.position == pos)
        {
            trap.triggered = true;
            if (!hero->isInvulnerable())
            {
                hero->takeDamage(trap.damage);
                std::cout << Color::Yellow << "You stepped on a trap! -"
                    << trap.damage << " HP" << Color::Reset << "\n";
            }
            else
            {
                std::cout << Color::Cyan << "Your shield absorbed the trap!"
                    << Color::Reset << "\n";
            }
        }
    }
}

void Game::processCommand(char command)
{
    switch (command)
    {
    case 'L': moveHero(-1, 0); break;
    case 'R': moveHero(1, 0);  break;
    case 'U': moveHero(0, -1); break;
    case 'D': moveHero(0, 1);  break;
    default:
        std::cout << "Unknown command.\n";
        break;
    }
}

void Game::moveEnemies()
{
    for (auto& enemy : enemies)
    {
        if (enemy->isAlive())
            enemy->moveTowards(hero->getPosition(), board);
    }
}

bool Game::checkWinCondition() const
{
    return hero->getPosition() == board.getExitPosition();
}

bool Game::checkLoseCondition() const
{
    if (hero->isInvulnerable())
        return false;

    Point heroPos = hero->getPosition();
    for (const auto& enemy : enemies)
    {
        if (enemy->isAlive() && enemy->getPosition() == heroPos)
            return true;
    }

    if (hero->getHealth() <= 0)
        return true;

    return false;
}

void Game::run()
{
    while (!gameOver)
    {
        // 1. Print current board state
        printBoard();

        // 2. Read player command
        std::cout << "Command (L/R/U/D/OOP/Q): ";
        std::string input;
        if (!(std::cin >> input))
            break;

        // 3. Execute player action
        if (input == "Q" || input == "q")
        {
            std::cout << "Game exited by player.\n";
            break;
        }
        else if (input == "OOP")
        {
            if (hero->useAbility())
                std::cout << Color::Cyan << "Shield activated for 3 turns!"
                << Color::Reset << "\n";
        }
        else if (input.size() == 1)
        {
            char c = static_cast<char>(std::toupper(static_cast<unsigned char>(input[0])));
            processCommand(c);
            checkHeroAgainstTrap();
        }
        else
        {
            std::cout << "Unknown command.\n";
            continue;
        }

        // 4. Check win/lose after player's move
        if (checkWinCondition())
        {
            printBoard();
            std::cout << Color::Green << "\n*** Victory! You reached the exit! ***"
                << Color::Reset << "\n";
            gameOver = true;
            playerWon = true;
            break;
        }
        if (checkLoseCondition())
        {
            std::cout << Color::Red << "\n*** Defeat! An enemy caught you! ***"
                << Color::Reset << "\n";
            gameOver = true;
            break;
        }

        // 5. Enemies move one step each
        moveEnemies();

        // 6. Check win/lose after enemies move
        if (checkLoseCondition())
        {
            std::cout << Color::Red << "\n*** Defeat! An enemy caught you! ***"
                << Color::Reset << "\n";
            gameOver = true;
            break;
        }

        // 7. Update fog and tick down timed abilities
        updateFog();
        hero->onTurnEnd();
    }
}