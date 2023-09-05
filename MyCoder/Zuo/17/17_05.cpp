/**
 * @file 17_04.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-30
 * 940. 不同的子序列 II
 * https://leetcode.cn/problems/distinct-subsequences-ii/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 没取模会报错
class Solution
{
public:
    int distinctSubseqII(string s)
    {
        int m = s.size();

        unordered_map<char, unsigned long long> last_count; // 不考虑去重上一次以s[i]字母结尾的新增的数量

        unsigned long long result = 1; // 包含空集
        for (int i = 0; i < m; i++)
        {
            unsigned long long add_count = result - last_count[s[i]]; // 去重
            last_count[s[i]] = result;                                // 不考虑去重以s[i]字母结尾的新增的数量
            result += add_count;
        }

        return result - 1;
    }
};

// 取模
int mm = 1000000007;
class Solution
{
public:
    int distinctSubseqII(string s)
    {
        int m = s.size();

        unordered_map<char, unsigned long long> last_count; // 不包含空集

        unsigned long long result = 1; // 包含空集
        for (int i = 0; i < m; i++)
        {
            unsigned long long add_count = (result - last_count[s[i]] + mm) % mm; // 由于取模操作不确定相减前的大小，所以多加一份mm
            last_count[s[i]] = result;
            result = (result + add_count) % mm;
        }

        return result == 0 ? 1000000006 : result - 1;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    string s;
    auto result = solution.distinctSubseqII(s);
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