/**
 * @file restore-ip-addresses.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-12
 * 93. 复原 IP 地址
 * https://leetcode.cn/problems/restore-ip-addresses/
 * @copyright Copyright (c) 2023
 *
 */
#include <string>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<string> result;
    int pointSum;
    // [left,right]
    bool isValid(string &s, int left, int right)
    {
        if (left > right)
            return false;
        // 首个数字为0的多位数
        if (s[left] == '0' && left != right)
            return false;

        int num = 0;
        for (int i = left; i <= right; i++)
        {
            if (s[i] > '9' || s[i] < '0')
                return false;
            num = num * 10 + (s[i] - '0');
            if (num > 255)
                return false;
        }

        return true;
    }

    void backTracking(string &s, int startIndex)
    {
        if (pointSum == 3)
        {
            if (isValid(s, startIndex, s.size() - 1))
            {
                result.push_back(s);
            }
        }

        for (int i = startIndex; i < s.size() - 1; i++)
        {
            if (!isValid(s, startIndex, i))
                return;
            s.insert(s.begin() + i + 1, '.');
            pointSum++;
            backTracking(s, i + 2);
            s.erase(s.begin() + i + 1);
            pointSum--;
        }
    }

    vector<string> restoreIpAddresses(string s)
    {
        result.clear();
        pointSum = 0;
        backTracking(s, 0);
        return result;
    }
};