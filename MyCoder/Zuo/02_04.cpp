/**
 * @file 02_04.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-14
 * 司机最高总收入
现有司机N人，调度中心会将所有司机平分给A、B两个区域第 i 个司机去A可得收入为income[i][0]，
第 i 个司机去B可得收入为income[i][1]，
返回所有调度方案中能使所有司机总收入最高的方案，是多少钱
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief 递归
 *
 * @param income
 * @param index 分配完第几个司机
 * @param rest A区域剩余的名额
 * @return int 最大收入
 */
int process(const vector<vector<int>> &income, const int &N, int index, int rest)
{
    // base case
    if (index == N)
        return 0;

    if (N - index == rest)
    {
        return income[index][0] + process(income, N, index + 1, rest - 1);
    }
    if (rest == 0)
    {
        return income[index][1] + process(income, N, index + 1, rest);
    }

    int result1 = income[index][0] + process(income, N, index + 1, rest - 1);
    int result2 = income[index][1] + process(income, N, index + 1, rest);

    return max<int>(result1, result2);
}

int solution(const vector<vector<int>> &income, int N)
{
    if (N % 2 != 0)
        return 0;

    return process(income, N, 0, N / 2);
}

int main()
{
    int N;
    cin >> N;

    vector<vector<int>> income(N, vector<int>(2));
    for (int i; i < N; i++)
    {
        cin >> income[i][0] >> income[i][1];
    }

    cout << "result:" << solution(income, N) << endl;
    return 0;
}