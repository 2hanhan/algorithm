# 模板
linux 下统计内存耗时
```c++
#include <bits/stdc++.h> 
using namespace std;

class Solution
{
    public:
    int getresult(vector<int> &nums)
    {
        return 0;
    }
};

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    // 代码
    Solution solution;
    vector<int> nums = {3, 2, 4, 1};
    auto result = solution.getresult(nums);
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

```

# LeetCode中C++一些Bug
1. 定义有返回值的函数，if情况及时穷举了所有情况并且return，只要没写else就会给你报错没有返回值。
比如即使调用时候x只给了1，2，3的数值
```c++
int fun(int x)
{
    if(x == 1)
    {
        return 1;
    }
    if(x == 2)
    {
        return 1;
    }
    if( x== 3)
    {
        return 1;
    }
}
```
2. delete释放内存，只有delete为root根节点就会出错。



# ACM
## 输入
第一行：数组长度 第二行: 数组中元素 
```bash
6
1 2 3 4 5 6
```
```c++
int length;
vector<int> nums(length);
for(int i = 0; i < length; i++)
{
    cin>>length[i];
}
```

每一行第一元素是数组长度length，之后输入数组中每一个元素，遇到length == 0 停止
```bash
4 1 2 3 4
2 1 1
0 
```

```c++
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
```

每一行都是一个数组，输入为``的时候停止
```bash
1 2 3 4 5 6
2 4 6 8
```
```cpp
vector<vector<int>> nums_map;
string s;
while (getline(cin, s))
{
    if (s == "")
        break;
    stringstream ss(s);
    int num;
    vector<int> nums;
    while (ss >> num)
    {
        nums.push_back(num);
    }
    nums_map.push_back(nums);
}
```

输入一个数组，以`,`进行分割数组中元素
```bash
1,2,3,4,6
```
```c++
string s;
cin>>s;
stringstream ss(s);
string s;
vector<int> nums;
while(getline(ss, token, ','))
{
    int num = std::stoi(token);
    nums.push_back(num);
}
```
