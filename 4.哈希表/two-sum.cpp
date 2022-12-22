/**
 * @file two-sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-22
 * - 4.5 两数之和
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <unordered_map>
using namespace std;

// 哈希表方式求解
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> map; // <value,index>
        for (int i = 0; i < nums.size(); i++)
        {
            auto iter = map.find(target - nums[i]);
            if (iter != map.end())
            {
                return {iter->second, i};
            }
            else
            {
                map.insert(pair<int, int>(nums[i], i));
            }
        }
        return {};
    }
};

// 遍历方式求解
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] + nums[j] == target)
                    return {i, j};
            }
        }
        return {};
    }
};
