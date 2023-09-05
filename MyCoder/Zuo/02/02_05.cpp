/**
 * @file 02_05.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-18
 * 数据结构设计之O(1)实现setAll
 * setAll(value)将hash表格中所有的元素设置为value
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    unordered_map<int, pair<int, int>> mymap;

    int current_time;
    int set_all_time;
    int all;

    Solution() : current_time(0)
    {
    }

    void insert(int key, int value)
    {
        mymap[key] = make_pair(value, current_time++);
    }

    void set_all(int value)
    {
        set_all_time = current_time;
        all = value;
    }

    int get(int key)
    {
        if (mymap.find(key) != mymap.end())
        {
            if (mymap[key].second < set_all_time)
            {
                return mymap[key].first;
            }
            else
            {
                return all;
            }
        }
    }
};

int main()
{
    Solution solution;

    return 0;
}