/**
 * @file 27_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-10-16
 * 781. 森林中的兔子
 * https://leetcode.cn/problems/rabbits-in-forest/description/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int numRabbits(vector<int> &answers)
    {
        unordered_map<int, int> rabits_count;
        for (int i = 0; i < answers.size(); i++)
        {
            rabits_count[answers[i]]++; // 统计回答每个次数有多少个
        }

        int sum = 0;
        for (auto rabit : rabits_count)
        {
            int count = rabit.first + 1;                             // 该颜色个数应该是回答数量+1
            int group = rabit.second / count;                        // 回答相同的凑成一组
            group = rabit.second % count == 0 ? group : (group + 1); // 凑组后有剩余的单独成组
            sum += group * count;
        }
        return sum;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<int> answers = {1, 1, 2};
    auto result = solution.numRabbits(answers);
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
