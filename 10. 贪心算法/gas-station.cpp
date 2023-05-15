/**
 * @file gas-station.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-13
 * 134. 加油站
 * https://leetcode.cn/problems/gas-station/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>

using namespace std;
class Solution
{
public:
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost)
    {
        int start = 0;
        int sum = 0;    
        int curSum = 0; 
        for (int i = 0; i < gas.size(); i++)
        {
            // 当前的油耗超过了加的油，尝试从下一站开始
            curSum += gas[i] - cost[i];
            if (curSum < 0)
            {
                start = i + 1;
                curSum = 0;
            }
            // 总共的油耗是否大于总共的油，总油够用就一定存在一个可以实现的出发点
            sum += gas[i] - cost[i];
        }
        if (sum < 0)
            return -1;
        return start;
    }
};