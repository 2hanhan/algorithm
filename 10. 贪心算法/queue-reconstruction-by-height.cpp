/**
 * @file queue-reconstruction-by-height.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 406. 根据身高重建队列
 * https://leetcode.cn/problems/queue-reconstruction-by-height/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

class Solution
{
public:
    static bool cmp(const vector<int> &a, const vector<int> &b)
    {
        if (a[0] == b[0])
            return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        // 首先按照身高排序，高的在前面，相同身高的，前面人数少的在前面
        sort(people.begin(), people.end(), cmp);

        // 再根据前面有几个人，进行插入
        list<vector<int>> que;
        for (int i = 0; i < people.size(); i++)
        {
            int position = people[i][1];
            list<vector<int>>::iterator it = que.begin();
            while (position--)
            {
                it++;
            }
            que.insert(it, people[i]);
        }

        return vector<vector<int>>(que.begin(), que.end());
    }
};