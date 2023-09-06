/**
 * @file keys-and-rooms.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-19
 * 841. 钥匙和房间
 * https://leetcode.cn/problems/keys-and-rooms/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    bool canVisitAllRooms(vector<vector<int>> &rooms)
    {

        vector<bool> visited(rooms.size(), false);
        queue<int> keys;
        visited[0] = true;
        int count = 1;
        for (int i = 0; i < rooms[0].size(); i++)
        {
            keys.push(rooms[0][i]);
        }

        while (!keys.empty())
        {
            int current_room = keys.front();
            keys.pop();
            if (visited[current_room])
            {
                continue;
            }
            else
            {
                visited[current_room] = true;
                count++;
            }
            for (int i = 0; i < rooms[current_room].size(); i++)
            {
                keys.push(rooms[current_room][i]);
            }
        }

        return count == rooms.size();
    }
};