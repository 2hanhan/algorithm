/**
 * @file binary-tree-postorder-traversal.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-29
 * https://leetcode.cn/problems/binary-tree-postorder-traversal/
 * 二叉树后序遍历
 * @copyright Copyright (c) 2022
 *
 */

#include <vector>
#include <stack>
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

// 递归序
class Solution0
{
public:
    void traversal(TreeNode *cur, vector<int> &result)
    {
        if (cur == NULL)
        {
            return;
        }
        traversal(cur->left, result);
        traversal(cur->right, result);
        result.push_back(cur->val);
    }
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};

// 压栈
class Solution1
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        if (root == NULL)
        {
            return result;
        }
        st.push(root);
        while (!st.empty())
        {
            TreeNode *node = st.top();
            st.pop();
            result.push_back(node->val); // 中
            if (node->left)
            {
                st.push(node->left); // 左
            }
            if (node->right)
            {
                st.push(node->right); // 右
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

// 双指针压栈
class Solution2
{
public:
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        TreeNode *cur = NULL;
        TreeNode *help = root; // 记录上一个打印存储的节点，出栈的节点

        if (root == NULL)
        {
            return result;
        }
        st.push(help);
        while (!st.empty())
        {
            cur = st.top(); // 栈顶部的节点，上一个进栈的节点
            // 上一个进栈节点的左节点没处理完，有左节点，并且左节点没处理(上一次打印过左，则左处理了，上一次打印过右，则左右都处理了)
            if (cur->left != NULL && help != cur->left && help != cur->right)
            {
                st.push(cur->left);
            }
            // 上一个进栈节点的右节点没处理完，有右节点，并且右节点没处理(上一次打印过右，则处理了)
            else if (cur->right != NULL && help != cur->right) 
            {
                st.push(cur->right);
            }
            // 上一个进栈节点的无子节点，或者子节点以及全部出栈(右节点以及出栈)，就该出栈了
            else
            {
                cur = st.top();
                st.pop();
                result.push_back(cur->val);
                help = cur; // 上一次弹出的节点
            }
        }

        return result;
    }
};