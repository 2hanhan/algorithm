/**
 * @file spiral-matrix-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-05
 * - 6. 螺旋矩阵II
 * - 主要思路：
 * - 1. 循环问题处理每段循环的开闭区间应该保持一致
 * - 2. 一圈分四段，每段使用类似的边界条件
 * - 3. 总共处理的圈数为n/2，向下取整，
 * - 4. 如果是奇数情况，矩阵中心位置会有一个，不满一圈的部分单独处理
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> generateMatrix(int n)
    {
        vector<vector<int>> nnmatirx(n, vector<int>(n, 0));

        //圈数，当前大小
        int k = 0, count = 1;
        while (k < n / 2)
        {

            int i = k, j = k;
            for (; j < n - k - 1; j++)
            {
                nnmatirx[i][j] = count;
                count++;
            }
            for (; i < n - k - 1; i++)
            {
                nnmatirx[i][j] = count;
                count++;
            }
            for (; j > k; j--)
            {
                nnmatirx[i][j] = count;
                count++;
            }
            for (; i > k; i--)
            {
                nnmatirx[i][j] = count;
                count++;
            }
            k++;
        }

        //奇数个，单独处理矩阵中心
        if (n % 2 == 1)
        {
            nnmatirx[n / 2][n / 2] = count;
        }
        return nnmatirx;
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入正整数 n" << std::endl;
    cin >> n;

    Solution solution;
    vector<vector<int>> nnmatirx = solution.generateMatrix(n);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << nnmatirx[i][j] << " ";
        }
        cout << endl;
    }
    std::cout << std::endl;

    cout << "-----结束-----" << endl;
    return 0;
}