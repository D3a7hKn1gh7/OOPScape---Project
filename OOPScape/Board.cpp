#include "Board.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

bool Board::isAllowedChar(char c)
{
    return c == '*' || c == ' ' || c == 'S' || c == 'F' || c == 'E' || c == 'T';
}

bool Board::isInside(int x, int y) const
{
    return x >= 0 && y >= 0 && x < n && y < n;
}

char Board::at(int x, int y) const
{
    if (!isInside(x, y))
        throw std::out_of_range("Board::at - coordinates outside the board");
    return grid[y][x];
}

void Board::set(int x, int y, char value)
{
    if (!isInside(x, y))
        throw std::out_of_range("Board::set - coordinates outside the board");
    grid[y][x] = value;
}

void Board::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Cannot open level file: " + filename);

    std::string firstLine;
    if (!std::getline(file, firstLine))
        throw std::runtime_error("Level file is empty: " + filename);

    std::istringstream sizeStream(firstLine);
    int parsedN = 0;
    if (!(sizeStream >> parsedN))
        throw std::runtime_error("First line must contain the board size n");

    if (parsedN < 2 || parsedN > 64)
        throw std::runtime_error("Board size n must be between 2 and 64, got: "
            + std::to_string(parsedN));

    n = parsedN;
    grid.clear();
    enemyPositions.clear();
    trapPositions.clear();
    startPos = Point{ -1, -1 };
    exitPos = Point{ -1, -1 };

    int countS = 0;
    int countF = 0;

    for (int row = 0; row < n; ++row)
    {
        std::string line;
        if (!std::getline(file, line))
            throw std::runtime_error("Level file has fewer than n rows (missing row "
                + std::to_string(row) + ")");

        if (static_cast<int>(line.size()) != n)
            throw std::runtime_error("Row " + std::to_string(row)
                + " does not contain exactly n characters (expected " + std::to_string(n)
                + ", got " + std::to_string(line.size()) + ")");

        for (int col = 0; col < n; ++col)
        {
            char c = line[col];
            if (!isAllowedChar(c))
                throw std::runtime_error("Invalid character '" + std::string(1, c)
                    + "' at row " + std::to_string(row) + ", col " + std::to_string(col));

            if (c == 'S')
            {
                ++countS;
                startPos = Point{ col, row };
            }
            else if (c == 'F')
            {
                ++countF;
                exitPos = Point{ col, row };
            }
            else if (c == 'E')
            {
                enemyPositions.push_back(Point{ col, row });
            }
            else if (c == 'T')
            {
                trapPositions.push_back(Point{ col, row });
            }
        }

        grid.push_back(line);
    }

    if (countS != 1)
        throw std::runtime_error("Level must contain exactly one 'S', found: "
            + std::to_string(countS));

    if (countF != 1)
        throw std::runtime_error("Level must contain exactly one 'F', found: "
            + std::to_string(countF));
}