/**
 * @file 3sum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-22
 * - 4.8 三数之和
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

// 哈希表法
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
        // 找出a + b + c = 0
        for (int i = 0; i < nums.size(); i++)
        {
            // 排序之后如果第一个元素已经大于零，那么不可能凑成三元组
            if (nums[i] > 0)
            {
                break;
            }
            if (i > 0 && nums[i] == nums[i - 1])
            { // 三元组元素a去重
                continue;
            }

            unordered_set<int> set;
            // nums[i] 看做 a
            // set中存的之前的nums[j]看做b
            // 新的nums[j] 看做 c
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (j > i + 2 && nums[j] == nums[j - 1] && nums[j - 1] == nums[j - 2])
                {
                    continue; // 元素b去重
                    // 第一个 nums[j]==x 是可以存入set的
                    // 第二个 nums[j]==x 如果 a + x + nums[j] ！= 0 不会产生异常
                    // 第二个 nums[j]==x 如果 a + x + nums[j] == 0 会触发【E2】把set中的x给删除掉
                    // 如果触发【E2】把set中的x给删除掉了
                    // 第三个 nums[j]==x 又可以放入set，
                    // 将导致后续相同的nums[j]符合 a + x + nums[j] == 0，因为nums[j]并没有放入set，导致会导致重复，
                    // 所有不能放入第三个
                }

                int b = 0 - (nums[i] + nums[j]);
                if (set.find(b) != set.end())
                {
                    result.push_back({nums[i], nums[j], b});
                    set.erase(b); // 元素c去重【E2】防止set已有的元素x，重复与相同的nums[j]求和获得重复的结果，
                }
                else
                {
                    set.insert(nums[j]);
                }
            }
        }
        return result;
    }
};

// 双指针写法
// class Solution
// {
// public:
//     vector<vector<int>> threeSum(vector<int> &nums)
//     {
//         vector<vector<int>> result;
//         // 对nums排序
//         sort(nums.begin(), nums.end());

//         for (int i = 0; i < nums.size(); i++)
//         {
//             // 排序后最小的大于0和一定大于0
//             if (nums[i] > 0)
//                 break;

//             // 对i去重
//             if (i > 0)
//             {
//                 if (nums[i] == nums[i - 1])
//                     continue;
//             }

//             int left = i + 1;
//             int right = nums.size() - 1;
//             while (left < right)
//             {
//                 if (nums[i] + nums[left] + nums[right] > 0)
//                 {
//                     right--;
//                 }
//                 else if (nums[i] + nums[left] + nums[right] < 0)
//                 {
//                     left++;
//                 }
//                 else
//                 {
//                     result.push_back(vector<int>{nums[i], nums[left], nums[right]});
//                     right--;
//                     left++;
//                     // 对left去重
//                     while (left < right && nums[left] == nums[left - 1])
//                     {
//                         left++;
//                     }
//                     // 对right去重
//                     while (left < right && nums[right] == nums[right + 1])
//                     {
//                         right--;
//                     }
//                 }
//             }
//         }
//         return result;
//     }
// };