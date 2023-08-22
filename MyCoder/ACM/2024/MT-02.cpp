#include <bits/stdc++.h>
using namespace std;

// 通过0

int main()
{
    int n;
    cin >> n;
    int sum = 0;
    vector<int> nums(n);

    std::unordered_map<int, int> count;
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
        sum += nums[i];
        ++count[nums[i]];
    }

    int yushu = sum % n;
    int mean = sum / n;

    int result = 0;
    if (yushu == 0)
    {
        for (int i = 0; i < n; i++)
        {
            int xx = nums[i] - mean;
            xx = xx > 0 ? xx : -xx;
            result += xx;
        }

        result = result / 2;
        cout << result << endl;
        return 0;
    }
    else
    {
        // 按照出现次数降序排序
        std::sort(nums.begin(), nums.end(), [&count](int a, int b)
                  { return count[a] > count[b]; });

        int best = INT_MAX;

        for (int i = 0; i < n; ++i)
        {
            mean = nums[i];
            yushu = sum - nums[i] * (n - 1);
            int delta_yushu = INT_MAX;
            int zz = 0;
            if (yushu >= 1)
            {
                for (int j = 0; j < n; j++)
                {
                    if (nums[j] == mean)
                        continue;

                    int yy = nums[j] - yushu;
                    yy = yy > 0 ? yy : -yy;
                    if (yy <= delta_yushu)
                    {
                        delta_yushu = yy;
                        zz = nums[j];
                    }

                    int xx = nums[j] - mean;
                    xx = xx > 0 ? xx : -xx;
                    result += xx;
                }
                int p1 = zz - yushu;
                p1 = p1 > 0 ? p1 : -p1;
                int p2 = zz - mean;
                p2 = p2 > 0 ? p2 : -p2;
                int shaode = p2 - p1;
                result -= shaode;

                result = result / 2;

                if (result < best)
                    best = result;
                // cout << result << endl;
                // return 0;
            }
        }

        cout << best << endl;
        return 0;
    }
    return 0;
}