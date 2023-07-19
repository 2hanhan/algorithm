/**
 * @file squares-of-a-sorted-array.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-05
 * 977. 有序数组的平方
 * https://leetcode.cn/problems/squares-of-a-sorted-array/
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<int> sortedSquares(vector<int> &nums)
    {
        vector<int> numsquares(nums.size());
        int k = nums.size() - 1;
        for (int i = 0, j = k; i <= j;)
        {
            int ii = nums[i] * nums[i], jj = nums[j] * nums[j];

            if (ii < jj)
            {
                numsquares[k] = jj;
                j--;
                k--;
            }
            else
            {
                numsquares[k] = ii;
                i++;
                k--;
            }
        }
        return numsquares;
    }
};


class Solution {
public:
    vector<vector<int>> generateMatrix(int n) 
    {
        int count = 1;
        vector<vector<int>> res(n, vector<int>(n, n*n));

        for(int i = 0;i < n/2;n++)
        {   
            //四个起点坐标
            int x1 = i;
            int y1 = i;

            int x2 = n-1-i;
            int y2 = i;

            int x3 = n-1-i;
            int y3 = n-1-i;

            int x4 = i;
            int y4 = n-1-i;
            for(int j = 0;j<n-1-i;j++)
            {
                res[x1][y1++] = count*count;
                count++;
            }
                        for(int j = 0;j<n-1-i;j++)
            {
                res[x2++][y2] = count*count;
                count++;
            }
                        for(int j = 0;j<n-1-i;j++)
            {
                res[x3][y3--] = count*count;
                count++;
            }
                        for(int j = 0;j<n-1-i;j++)
            {
                res[x4--][y4] = count*count;
                count++;
            }

        }

        return res;
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入数组数组大小 n" << std::endl;
    cin >> n;

    vector<int> nums(n);
    cout << "依次从小到大输入n个数字作为输入" << std::endl;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }

    Solution solution;
    vector<int> numsquares = solution.sortedSquares(nums);

    cout << "输入数组:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << nums[i] << " ";
    }

    cout << endl
         << "排序结果:" << endl;

    for (int i = 0; i < numsquares.size(); i++)
    {
        cout << numsquares[i] << " ";
    }
    std::cout << std::endl;

    cout << "-----结束-----" << endl;
    return 0;
}