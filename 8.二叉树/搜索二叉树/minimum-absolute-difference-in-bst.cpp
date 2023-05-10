/**
 * @file minimum-absolute-difference-in-bst.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 530. 二叉搜索树的最小绝对差
 * https://leetcode.cn/problems/minimum-absolute-difference-in-bst/
 * @copyright Copyright (c) 2023
 *
 */

#include <stack>
#include <limits.h>
using namespace std;

// 二叉树的定义
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 中序遍历迭代法
class Solution
{
public:
    int getMinimumDifference(TreeNode *root)
    {
        if (root == nullptr)
            return 0;

        int result = INT_MAX;
        stack<TreeNode *> mySt;
        TreeNode *pre = nullptr;
        TreeNode *cur = root;

        // 中序遍历
        while (cur != nullptr || !mySt.empty())
        {
            if (cur != nullptr)
            {
                mySt.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = mySt.top();
                mySt.pop();
                if (pre != nullptr && cur->val - pre->val < result)
                {
                    result = cur->val - pre->val;
                }
                pre = cur;
                cur = cur->right;
            }
        }

        return result;
    }
};