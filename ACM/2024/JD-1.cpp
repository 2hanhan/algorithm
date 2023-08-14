#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    if (n == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            cout << 0 << " ";
        }
        return 0;
    }

    vector<long long> dp(10, 0);
    dp[nums[n - 1]] = 1;
    for (int i = n - 1; i > 0; i--)
    {
        vector<long long> temp(10, 0);
        for (int j = 0; j <= 9; j++)
        {
            int x, y;
            if (dp[j] == 0)
            {
                continue;
            }
            else
            {
                x = j;
                y = nums[i - 1];
                temp[(x * y) % 10] += dp[j];
                temp[(x + y) % 10] += dp[j];
            }
        }
        dp = temp;
    }

    // 输出方案数
    for (int i = 0; i < 10; i++)
    {
        cout << dp[i] << " ";
    }
    cout << endl;

    return 0;
}