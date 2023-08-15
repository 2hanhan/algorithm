/**
 * @file fibonacci-number.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 * 509. 斐波那契数
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
using namespace std;
class Solution
{
public:
    vector<int> nums;
    int fib(int n)
    {
        if (n <= 0)
            return 0;

        nums.resize(n + 1, 1);
        for (int i = 2; i < n + 1; i++)
        {
            nums[i] = nums[i - 1] + nums[i - 2];
        }

        return nums[n];
    }
};
