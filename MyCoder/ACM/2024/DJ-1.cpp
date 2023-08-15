/**
 * @file Leetcode1187.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-08-14
 * 1187.使数组严格递增
 * https://leetcode.cn/problems/make-array-strictly-increasing/
 * @copyright Copyright (c) 2023
 * 
 */

/*

输入
socre1=[1,5,3,6,5]
socre2=[1,3,2,4]
输出
 */
#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 0x3f3f3f3f;

    int makeArrayIncreasing(vector<int>& arr1, vector<int>& arr2) {
        sort(arr2.begin(), arr2.end());
        arr2.erase(unique(arr2.begin(), arr2.end()), arr2.end());
        int n = arr1.size();
        int m = arr2.size();
        vector<vector<int>> dp(n + 1, vector<int>(min(m, n) + 1, INF));
        dp[0][0] = -1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= min(i, m); j++) {
                /* 如果当前元素大于序列的最后一个元素 */
                if (arr1[i - 1] > dp[i - 1][j]) {
                    dp[i][j] = arr1[i - 1];
                }
                if (j > 0 && dp[i - 1][j - 1] != INF) {
                    /* 查找严格大于 dp[i - 1][j - 1] 的最小元素 */
                    auto it = upper_bound(arr2.begin() + j - 1, arr2.end(), dp[i - 1][j - 1]);
                    if (it != arr2.end()) {
                        dp[i][j] = min(dp[i][j], *it);
                    }
                }
                if (i == n && dp[i][j] != INF) {
                    return j;
                }
            }
        }
        return -1;
    }

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    s1 = s1.substr(8, s1.size() - 9);
    s2 = s2.substr(8, s2.size() - 9);

    stringstream ss1(s1);
    stringstream ss2(s2);

    vector<int> arr1;
    vector<int> arr2;

    std::string token;

    while (getline(ss1, token, ','))
    {
        int num = std::stoi(token);
        arr1.push_back(num);
    }


    while (getline(ss2, token, ','))
    {
        int num = std::stoi(token);
        arr2.push_back(num);
    }

    int result = makeArrayIncreasing(arr1,arr2);
    cout<<result<<endl;
    return 0;
}
