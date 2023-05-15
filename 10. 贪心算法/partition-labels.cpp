/**
 * @file partition-labels.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 763. 划分字母区间
 * https://leetcode.cn/problems/partition-labels/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<int> partitionLabels(string s)
    {

        // 统计最远距离
        unordered_map<char, int> map;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (map.find(s[i]) == map.end())
                map[s[i]] = i;
        }
        // 获取结果
        vector<int> result;
        int left = 0;
        int right = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (right >= i)
                right = right > map[s[i]] ? right : map[s[i]];
            else
            {
                result.push_back(i - left);
                left = i;
                right = map[s[i]];
            }
        }
        //统计最后一个区间长度
        result.push_back(right + 1 - left);
        return result;
    }
};