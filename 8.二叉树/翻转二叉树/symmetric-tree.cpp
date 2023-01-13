/**
 * @file symmetric-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-11
 *
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

// 递归方式
class Solution0
{
public:
    bool compare(TreeNode *left, TreeNode *right)
    {
        if (left == NULL && right != NULL)
            return false;
        else if (left != NULL && right == NULL)
            return false;
        else if (left == NULL && right == NULL)
            return true;
        else if (left->val != right->val)
            return false;
        else
            return compare(left->left, right->right) && compare(left->right, right->left);
    }
    bool isSymmetric(TreeNode *root)
    {
        if (root == NULL)
            return true;
        return compare(root->right, root->left);
    }
};

// 迭代法，使用栈
class Solution1
{
public:
    bool isSymmetric(TreeNode *root)
    {
        stack<TreeNode *> st;
        if (root != NULL)
        {
            st.push(root->left);
            st.push(root->right);
        }

        while (!st.empty())
        {
            TreeNode *leftNode = st.top();
            st.pop();
            TreeNode *rightNode = st.top();
            st.pop();

            if (!leftNode && !rightNode)
            {
                continue;
            }

            if (!leftNode || !rightNode || leftNode->val != rightNode->val)
                return false;

            // 对称位置两个两个挨着就行
            st.push(leftNode->left);
            st.push(rightNode->right);
            st.push(leftNode->right);
            st.push(rightNode->left);
        }

        return true;
    }
};

// 迭代法，使用队列
class Solution2
{
public:
    bool isSymmetric(TreeNode *root)
    {
        queue<TreeNode *> que;
        if (root != NULL)
        {
            que.push(root->left);
            que.push(root->right);
        }

        while (!que.empty())
        {
            TreeNode *leftNode = que.front();
            que.pop();
            TreeNode *rightNode = que.front();
            que.pop();

            if (!leftNode && !rightNode)
            {
                continue;
            }

            if (!leftNode || !rightNode || leftNode->val != rightNode->val)
                return false;

            // 对称位置两个两个挨着就行
            que.push(leftNode->left);
            que.push(rightNode->right);
            que.push(leftNode->right);
            que.push(rightNode->left);
        }

        return true;
    }
};