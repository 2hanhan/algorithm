/**
 * @file 4sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-23
 * - 4.9 四数之和
 * @copyright Copyright (c) 2022
 * - 注意
 * - (long) int + int 和(long) int * int 
 * - 使用(long)防止求和后溢出
 */

#include <vector>
#include <algorithm>
using namespace std;

// 双指针操作
class Solution
{
public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            // 剪枝操作去除一定不符合条件的
            // 4*最小的>target
            if ((long)4 * nums[i] > target)
            {
                break;
            }
            // 最小的大于0，并且最小>=target
            if (nums[i] > target && nums[i] >= 0)
            {
                break;
            }

            // 对a去重复
            if (i > 0 && nums[i] == nums[i - 1])
            {
                continue;
            }
            for (int j = i + 1; j < nums.size(); j++)
            {
                // 剪枝操作去除一定不符合条件的
                // 3*最小的>target
                if ((long)3 * nums[j] > target - nums[i])
                {
                    break;
                }
                // 最小的大于0，并且最小>=target
                if (nums[j] > target - nums[i] && nums[j] >= 0 - nums[i])
                {
                    break;
                }

                // 对b去重复
                if (j > i + 1 && nums[j] == nums[j - 1])
                {
                    continue;
                }
                int left = j + 1;
                int right = nums.size() - 1;
                while (left < right)
                {
                    if ((long)nums[i] + nums[j] + nums[left] + nums[right] > target) // long防止相加后爆掉
                    {
                        right--;
                    }
                    else if ((long)nums[i] + nums[j] + nums[left] + nums[right] < target) // long防止相加后爆掉
                    {
                        left++;
                    }
                    else
                    {
                        result.push_back(vector<int>({nums[i], nums[j], nums[left], nums[right]}));
                        right--;
                        left++;
                        // 对c去重
                        while (left < right && nums[right + 1] == nums[right])
                        {
                            right--;
                        }
                        // 对d去重
                        while (left < right && nums[left - 1] == nums[left])
                        {
                            left--;
                        }
                    }
                }
            }
        }

        return result;
    }
};