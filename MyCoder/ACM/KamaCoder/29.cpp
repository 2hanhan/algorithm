/**
 * @file 29. 安排超市
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-11
 * 29. 安排超市
 * 给定一个 n*n 的地图。地图是上下左右四联通的，但是不能斜向行走。
 * 其中：*代表障碍，不可通行；.代表路，可以通行；#代表房子。房子也是可以通行的。
 * 现在需要在一些地方安排一些超市（不能安排在障碍物上，可以安排在路上或者房子上，超市也是可以通行的），
 * 每个房子至少可以到达一个超市。同时由于成本原因，超市的数量需要尽可能的少。
 * 在超市数量最少的情况下，每个房子到达最近的超市的距离之和需要尽可能小。
 * 你的任务是计算超市最少的数量，以及最小的距离之和。
 *
 * 输入
 * 第一行包含一个正整数 n，代表地图的大小（1 <= n <= 50）。 接下来的 n 行，每行包含一个长度为 n 的字符串，表示整个地图。
 *
 * 输出
 * 输出两个整数，用空格隔开。分别代表超市的最小数量、最小的距离之和。
 *
实例：
输入
3
#.#
.**
*.#
输出
2 2
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>

using namespace std;

int direction[4][2] = {0, 1, 0, -1, 1, 0, -1, 0};
// 广度优先搜索
void bfs(const int &n, const vector<string> &map, vector<vector<int>> &supermarket,
         int i, int j, unordered_map<int, pair<bool, int>> &supermarket_distance)
{
    int current_supermarket, min_current_supermarket_distance;
    if (supermarket[i][j] == 0) // 当前位置未搜索过
    {
        current_supermarket = supermarket_distance.size() + 1;
        min_current_supermarket_distance = INT_MAX;
    }
    else
    {
        current_supermarket = supermarket[i][j];
        if (supermarket_distance[supermarket[i][j]].first)
            min_current_supermarket_distance = supermarket_distance[supermarket[i][j]].second; // 之前此区域到超市的最小距离
        else
            return; // 此区域没房子直接返回
    }

    bool have_house = map[i][j] == '#';                         // 统计是否有房子
    int current_supermarket_distance = 0, current_distance = 0; // 各个房子到超市距离，此次搜索到超市距离
    queue<pair<int, int>> positons;
    vector<vector<bool>> have_access(n, vector<bool>(n, false));

    positons.push({i, j});
    have_access[i][j] = true;                // 此次bfs是否搜索过
    supermarket[i][j] = current_supermarket; // 当前区块编号

    while (!positons.empty())
    {
        current_distance++;
        int current_positon_size = positons.size();
        for (int i = 0; i < current_positon_size; i++)
        {
            int current_x = positons.front().first;
            int current_y = positons.front().second;
            positons.pop();
            for (int j = 0; j < 4; j++)
            {
                int next_x = current_x + direction[j][0];
                int next_y = current_y + direction[j][1];
                if (next_x >= n || next_y >= n || next_x < 0 || next_y < 0)
                    continue;

                if (map[next_x][next_y] != '*' && !have_access[next_x][next_y])
                {
                    have_access[next_x][next_y] = true;
                    supermarket[next_x][next_y] = current_supermarket;
                    positons.push({next_x, next_y});

                    if (map[next_x][next_y] == '#') // 是房子的统计累积到超市的距离
                    {
                        have_house = true;
                        current_supermarket_distance += current_distance;
                    }
                }
            }
        }
    }

    if (current_supermarket_distance < min_current_supermarket_distance)
    {
        supermarket_distance[current_supermarket] = {have_house, current_supermarket_distance}; // 更新该区域各个房子到超市的最大距离
    }
}

int main()
{
    int n;
    cin >> n;
    vector<string> map;
    for (int i = 0; i < n; i++)
    {
        string x;
        cin >> x;
        map.push_back(x);
    }

    vector<vector<int>> supermarket(n, vector<int>(n, 0));    // 每个区块可以开超市的编号
    unordered_map<int, pair<bool, int>> supermarket_distance; // 区块超市编号，区块是否有房子(没房子就不用开超市)，该区块各个房子到超市的距离
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (map[i][j] == '*')
                continue;
            else
                bfs(n, map, supermarket, i, j, supermarket_distance);
        }
    }

    // 统计有房子的区块个数，各个区块中各个房子到超市的距离
    int all_supermarket = 0, all_supermarket_distance = 0;
    for (auto it = supermarket_distance.begin(); it != supermarket_distance.end(); it++)
    {
        if ((*it).second.first)
        {
            all_supermarket++;
            all_supermarket_distance += (*it).second.second;
        }
    }
    cout << all_supermarket << " " << all_supermarket_distance << endl;
}