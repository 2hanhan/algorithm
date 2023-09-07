#include <iostream>

using namespace std;
int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;
    return 0;
}

std::vector<int> memo;

int sumGoodsPrice(std::vector<int> goods)
{
    memo.resize(goods.size(), -1);
    return dp(goods, 0);
}
//
int dp(std::vector<int> &nums, int start)
{
    if (start >= static_cast<int>(nums.size()))
    {
        return 0;
    }

    if (memo[start] != -1)
        return memo[start];
        
    int res = std::max(dp(nums, start + 1),
                       nums[start] + dp(nums, start + 2));
    // record to memo
    memo[start] = res;
    return res;
}