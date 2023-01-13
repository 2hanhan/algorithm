/**
 * @file binary-tree-inorder-traversal.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-29
 * https://leetcode.cn/problems/binary-tree-inorder-traversal/
 * 二叉树中序遍历
 * 递归法
 * 压栈法
 * 标记法
 * @copyright Copyright (c) 2022
 *
 */
#include <vector>
#include <stack>
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
            return;
        traversal(cur->left, result);  // 左
        result.push_back(cur->val);    // 中
        traversal(cur->right, result); // 右
    }
    vector<int> inorderTraversal(TreeNode *root)
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
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        if (root == NULL)
        {
            return result;
        }
        TreeNode *cur = root;

        // 条件 cur != NULL 是为了把root通过循环放入栈
        // 条件 !st.empty() 是正常的入栈操作
        while (cur != NULL || !st.empty())
        {
            if (cur != NULL) // 向把所有的left取完
            {
                st.push(cur);
                cur = cur->left; // 左
            }
            else
            {
                cur = st.top(); // 弹出
                st.pop();
                result.push_back(cur->val); // 中
                cur = cur->right;           // 右
            }
        }

        return result;
    }
};

// 标记法
class Solution1
{
public:
    vector<int> inorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        if (root != NULL)
        {
            st.push(root);
        }
        while (!st.empty())
        {
            TreeNode *node = st.top();
            if (node != NULL)
            {
                st.pop();

                if (node->right) // 右
                {
                    st.push(node->right);
                }
                st.push(node); // 中
                st.push(NULL);
                if (node->left)
                {
                    st.push(node->left); // 左
                }
            }
            else
            {
                st.pop();
                node = st.top();
                st.pop();
                result.push_back(node->val);
            }
        }
        return result;
    }
};
