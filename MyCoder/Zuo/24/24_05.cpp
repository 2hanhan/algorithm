/**
 * @file 24_05.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-20
 * 76. 最小覆盖子串
 * https://leetcode.cn/problems/minimum-window-substring/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
using namespace std;

// 滑动窗口 贪心 欠债模型
class Solution
{
public:
    string minWindow(string s, string t)
    {
        // step 1 统计 t 中各个字符数量
        int count = 0; // 还需要几个字符才能覆盖target
        vector<int> char_count(256, 0);
        for (; count < t.size(); count++)
        {
            char_count[t[count]]++;
        }

        // step 2 通过滑窗统计
        int min_size = INT_MAX;
        int best_l = 0, best_r = s.size();
        int l = 0, r = 0;
        while (r < s.size())
        {

            if (char_count[s[r]] > 0)
                count--;
            char_count[s[r]]--; // 需要该字符的数量 -1

            // 移动左边界
            while (count == 0)
            {
                if (min_size > r - l) // 更新最小的
                {
                    best_l = l;
                    best_r = r;
                    // cout << " " << best_l << " " << best_r << endl;

                    min_size = r - l;
                }

                char_count[s[l]]++;       // 需要该字符的数量 +1
                if (char_count[s[l]] > 0) // 还需要该字符
                {
                    count++;
                }
                l++;
            }

            r++;
        }

        if (best_r == s.size())
        {
            return "";
        }
        else
        {
            return s.substr(best_l, min_size + 1);
        }
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    string s = "a";
    string t = "a";

    auto result = solution.minWindow(s, t);
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
