/**
 * @file sum-of-left-leaves.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
 * https://leetcode.cn/problems/sum-of-left-leaves/
 * 左叶子之和
 * 给定二叉树的根节点 root ，返回所有左叶子之和。
 * @copyright Copyright (c) 2023
 *
 */

#include <stack>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

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

class Solution0
{
public:
    int sumOfLeftLeaves(TreeNode *root)
    {
        // 终止条件
        if (root == NULL)
            return 0;
        // 叶子节点返回0，后续在对左叶子节点左单独处理
        if (root->left == NULL && root->right == NULL)
            return 0;

        // 左节点,继承之前的节点的左节点和
        int leftValue = sumOfLeftLeaves(root->left);
        // 对于叶子节点的左节点需要单独处理
        if (root->left && !root->left->left && !root->left->right)
            leftValue = root->left->val;

        int rightValue = sumOfLeftLeaves(root->right);

        return leftValue + rightValue;
    }
};

// 经典写法
class Solution1
{
public:
    int sumOfLeftLeaves(TreeNode *root)
    {
        // 终止条件
        if (root == NULL)
            return 0;

        // 对于叶子节点的左节点需要单独处理
        int leftValue = 0;
        if (root->left && !root->left->left && !root->left->right)
            leftValue = root->left->val;

        return leftValue + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    }
};

// 迭代写法
class Solution
{
public:
    int sumOfLeftLeaves(TreeNode *root)
    {
        int result = 0;
        // 遍历所有节点找出左叶子节点
        stack<TreeNode *> st;
        if (root != NULL)
            st.push(root);
        while (!st.empty())
        {
            TreeNode *node = st.top();
            st.pop();
            // 左叶子节点
            if (node->left && !node->left->left && !node->left->right)
                result += node->left->val;

            if (node->left)
                st.push(node->left);
            if (node->right)
                st.push(node->right);
        }
        return result;
    }
};
