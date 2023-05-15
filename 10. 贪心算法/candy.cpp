/**
 * @file candy.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 135. 分发糖果
 * https://leetcode.cn/problems/candy/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;
class Solution
{
public:
    int candy(vector<int> &ratings)
    {
        vector<int> candys(ratings.size(), 1);
        // 从左到右来一遍多的就多个一个，少的就只给一个
        for (int i = 1; i < ratings.size(); i++)
        {
            candys[i] = ratings[i] > ratings[i - 1] ? candys[i - 1] + 1 : 1;
        }
        // 从右到左来一遍多的就多个一个，少的就维持不变
        for (int i = ratings.size() - 2; i >= 0; i--)
        {
            if (ratings[i] > ratings[i + 1])
            {
                // 原本糖数不满足的，重新给糖
                if (candys[i] <= candys[i + 1])
                    candys[i] = candys[i + 1] + 1;
            }
        }
        // 统计糖总数
        int result = 0;
        for (int i = 0; i < candys.size(); i++)
        {
            result += candys[i];
        }
        return result;
    }
};