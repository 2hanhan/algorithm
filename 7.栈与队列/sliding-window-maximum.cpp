/**
 * @file sliding-window-maximum.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 * https://leetcode.cn/problems/sliding-window-maximum/
 * 滑动窗口最大值
 * sliding-window-maximum
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <deque>
using namespace std;

class Solution
{
private:
    // 自定一个单调队列从大到小 保存了最大(包括N个相等的)之后递减的序列
    class MyQueue
    {
    public:
        deque<int> que;
        void pop(int value)
        {
            // 需要弹出的value等于队列中的最大值
            if (!que.empty() && value == que.front())
                que.pop_front();
        }
        void push(int value)
        {
            // 保存了最大(包括N个相等的)
            //  把que中小于value的全部删除
            while (!que.empty() && value > que.back())
            {
                que.pop_back();
            }
            // 在que大于等于vale的后边添加value
            que.push_back(value);
        }

        // 取出最大值，即队列第一个
        int max()
        {
            return que.front();
        }
    };

public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        MyQueue que;
        // 初始化先把第一个划窗的k个数放进去
        for (int i = 0; i < k; i++)
        {
            que.push(nums[i]);
        }
        // 第一个划窗的k个数的最大值
        vector<int> result;
        result.push_back(que.max());
        for (int i = k; i < nums.size(); i++)
        {
            que.pop(nums[i - k]); // i-k移出划窗
            que.push(nums[i]);    // i加入划窗
            result.push_back(que.max());
        }
        return result;
    }
};