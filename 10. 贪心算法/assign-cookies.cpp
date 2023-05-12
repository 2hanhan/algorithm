/**
 * @file assign-cookies.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 455. 分发饼干
 * https://leetcode.cn/problems/assign-cookies/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int findContentChildren(vector<int> &g, vector<int> &s)
    {
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int p1 = 0;
        int p2 = 0;
        while (p1 < g.size() && p2 < s.size())
        {
            if (s[p2] >= g[p1])
            {
                p2++;
                p1++;
            }
            else
                p2++;
        }
        return p1;
    }
};