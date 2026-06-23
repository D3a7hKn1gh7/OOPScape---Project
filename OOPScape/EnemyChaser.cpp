#include "ChaserEnemy.h"
#include "BoardUtils.h"
#include <vector>
#include <queue>

// Finds the shortest path from enemyPos to heroPos using BFS and moves
// the enemy one step along that path. Returns true if a path was found.
static bool tryMoveTowardsHeroBFS(Point& enemyPos, const Point& heroPos, const Board& board)
{
    int n = board.size();
    int W = n;
    std::vector<int> parent(W * W, -1);
    std::queue<Point> q;
    int start = enemyPos.y * W + enemyPos.x;
    int goal = heroPos.y * W + heroPos.x;
    parent[start] = start;
    q.push(enemyPos);
    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };
    bool found = false;

    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();
        int curI = cur.y * W + cur.x;
        if (curI == goal)
        {
            found = true;
            break;
        }
        for (int k = 0; k < 4; ++k)
        {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if (!isWalkable(nx, ny, board)) continue;
            int ni = ny * W + nx;
            if (parent[ni] != -1) continue;
            parent[ni] = curI;
            q.push(Point{ nx, ny });
        }
    }

    if (!found)
        return false;

    int cur = goal;
    while (parent[cur] != start && cur != start)
        cur = parent[cur];

    if (cur == start)
        return false;

    enemyPos.x = cur % W;
    enemyPos.y = cur / W;
    return true;
}

void ChaserEnemy::moveTowards(const Point& heroPos, const Board& board)
{
    Point pos = position;
    if (tryMoveTowardsHeroBFS(pos, heroPos, board))
        position = pos;
}