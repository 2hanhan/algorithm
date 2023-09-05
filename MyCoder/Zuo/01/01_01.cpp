/**
 * @file 01_01.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-14
 * 一根长度为K的绳子，最多能盖住几个点
给定一个有序数组arr，从左到右依次表示X轴上从左往右点的位置
给定一个正整数K，返回如果有一根长度为K的绳子，最多能盖住几个点
绳子的边缘点碰到X轴上的点，也算盖住
 * @copyright Copyright (c) 2023
 *
 */
#include <bits/stdc++.h>
using namespace std;

// 滑窗
int solution(vector<int> nums, int length)
{
    int left = 0, right = 0;
    int n = nums.size();
    int max_length = 0;
    while (left < n)
    {
        while (right < n && nums[right] - nums[left] <= length)
        {
            right++;
        }
        max_length = max<int>(max_length, (right - left++));
    }
    return max_length;
}

int main()
{

    string s;
    vector<int> nums;
    int num;
    getline(cin, s);
    stringstream ss(s);
    while (ss >> num)
    {
        nums.push_back(num);
    }

    int length;
    cin >> length;


    cout << "数组:";
    for (int i = 0; i < nums.size(); i++)
    {
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << "绳子长度:" << length << endl;

    cout << "覆盖数目:" << solution(nums, length);

    return 0;
}