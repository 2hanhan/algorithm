/**
 * @file house-robber-iii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-18
 * 337. 打家劫舍 III
 * https://leetcode.cn/problems/house-robber-iii/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>

using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    vector<int> dp(TreeNode *root)
    {
        if (root == nullptr)
            return {0, 0};

        vector<int> dpleft = dp(root->left);
        vector<int> dpright = dp(root->right);
        int dp0 = max(dpleft[0], dpleft[1]) + max(dpright[0], dpright[1]);
        int dp1 = root->val + dpleft[0] + dpright[0];
        return {dp0, dp1};
    }
    int rob(TreeNode *root)
    {
        vector<int> dproot = dp(root);
        return max(dproot[0], dproot[1]);
    }
};