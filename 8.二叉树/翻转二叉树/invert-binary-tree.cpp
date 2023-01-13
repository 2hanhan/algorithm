/**
 * @file invert-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-11
 * https://leetcode.cn/problems/invert-binary-tree/
 * 翻转二叉树
 * 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
 * @copyright Copyright (c) 2023
 *
 */

#include <stack>
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

// 递归法
class Solution0
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        // 递归终止条件
        if (root == NULL)
            return root;
        // 调用递归
        swap(root->left, root->right); // 左右交换
        invertTree(root->left);
        invertTree(root->right);
        // 返回结果
        return root;
    }
};

// 使用前序遍历算法实现
class Solution1
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        stack<TreeNode *> st;
        if (root != NULL)
            st.push(root);
        while (!st.empty())
        {
            TreeNode *node = st.top();
            if (node != NULL)
            {
                st.pop();
                if (node->right)
                    st.push(node->right);
                if (node->left)
                    st.push(node->left);
                st.push(node);
                st.push(NULL);
            }
            else
            {
                st.pop();
                node = st.top();
                st.pop();
                swap(node->left, node->right);
            }
        }
        return root;
    }
};

//层序遍历
class Solution2
{
public:
    TreeNode *invertTree(TreeNode *root)
    {
        queue<TreeNode *> que;
        if (root != NULL)
            que.push(root);
        while (!que.empty())
        {
            int size = que.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = que.front();
                que.pop();
                swap(node->left, node->right);
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
        }
        return root;
    }
};