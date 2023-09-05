/**
 * @file 17_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-30
 * 378. 有序矩阵中第 K 小的元素
 * https://leetcode.cn/problems/kth-smallest-element-in-a-sorted-matrix/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 矩阵中小于等于value的个数 ，以及最接近x的数
    pair<int, int> noMoreNum(const vector<vector<int>> &matrix, int value)
    {
        pair<int, int> ans = {0, INT_MIN};
        int M = matrix.size();
        int N = matrix[0].size();
        int best_num = 0;
        int count = 0;

        int i = 0;
        int j = N - 1;
        while (i < M && j >= 0)
        {
            if (matrix[i][j] <= value)
            {
                ans.first += j + 1;                              // 矩阵中小于等于value的个数
                ans.second = max<int>(ans.second, matrix[i][j]); // 小于等于value的数，越大越解决valu
                i++;
            }
            else
            {
                j--;
            }
        }

        return ans;
    }
    // 二分查找小于等于k的数的个数
    int kthSmallest(vector<vector<int>> &matrix, int k)
    {
        int M = matrix.size();
        int N = matrix[0].size();

        int left = matrix[0][0];
        int right = matrix[M - 1][N - 1];

        int result = 0;
        while (left <= right)
        {
            int mid = left + ((right - left) >> 1);
            pair<int, int> ans = noMoreNum(matrix, mid);

            if (ans.first < k)
            {
                left = mid + 1;
            }
            else
            {
                result = ans.second;
                right = mid - 1;
            }
        }
        return result;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<vector<int>> matrix;
    int k;
    int result = solution.kthSmallest(matrix, k);
    cout << "result:" << result << endl;

    // 结束计时
    auto end = std::chrono::high_resolution_clock::now();

    // 计算耗时
    std::chrono::duration<double> duration = end - start;
    double seconds = 1000 * duration.count();

    // 输出结果
    std::cout << endl;
    std::cout << "Elapsed time: " << std::fixed << std::setprecision(2) << seconds << " ms\n";

    return 0;
}