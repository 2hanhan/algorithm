/**
 * @file top-k-frequent-elements.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 * https://leetcode.cn/problems/top-k-frequent-elements/
 * 前 K 个高频元素
 * 返回高频元素可以按照任意顺序
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution
{
public:
    // 自定义比较器
    class MyComparison
    {
    public:
        bool operator()(const pair<int, int> &left, const pair<int, int> &right)
        {
            return left.second > right.second;
        }
    };

    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        // step 1 统计元素出现个数
        // key：元素 ，value：出现次数
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++)
        {
            map[nums[i]]++;
        }
        // step 2 使用小根堆求解
        priority_queue<pair<int, int>, vector<pair<int, int>>, MyComparison> pri_que;
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++)
        {
            pri_que.push(*it);
            if (pri_que.size() > k)
            {
                pri_que.pop(); // 小根堆弹出最小值
            }
        }
        // step 3 从堆里取出结果放入vector<int>
        vector<int> result;
        for (int i = 0; i < k; i++)
        {
            result.push_back(pri_que.top().first);
            pri_que.pop();
        }
        return result;
    }
};