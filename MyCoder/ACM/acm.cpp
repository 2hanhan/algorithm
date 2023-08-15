#include <bits/stdc++.h>

using namespace std;

// int main()
// {
//     string s;
//     vector<vector<int>> nums_map;
//     while (getline(cin, s))
//     {
//         if (s == "")
//             break;
//         cout << "s:" << s << endl;
//         stringstream ss(s);
//         int num;
//         vector<int> nums;
//         while (ss >> num)
//         {
//             nums.push_back(num);
//         }
//         nums_map.push_back(nums);
//     }
//     cout << "结束输入" << endl;
//     return 0;
// }

int main()
{
    vector<vector<int>> nums_map;
    int length;
    while (cin >> length)
    {
        if (length == 0)
            break;
        vector<int> nums(length);
        for (int i = 0; i < length; i++)
        {
            cin >> nums[i];
        }
        nums_map.push_back(nums);
    }
    cout << "结束输入" << endl;
    return 0;
}