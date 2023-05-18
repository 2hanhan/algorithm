/**
 * @file last-stone-weight-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-16
 * 1049. 最后一块石头的重量 II
 * https://leetcode.cn/problems/last-stone-weight-ii/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <math.h>
using namespace std;

class Solution
{
public:
    int lastStoneWeightII(vector<int> &stones)
    {

        int sum = 0;
        for (int i = 0; i < stones.size(); i++)
        {
            sum += stones[i];
        }

        vector<int> DP((sum >> 1) + 1, 0);
        for (int i = 0; i < stones.size(); i++)
        {
            for (int j = (sum >> 1); j >= stones[i]; j--)
            {
                DP[j] = max(stones[i] + DP[j - stones[i]], DP[j]);
            }
        }

        return abs(sum - 2 * DP[sum >> 1]);
    }
};