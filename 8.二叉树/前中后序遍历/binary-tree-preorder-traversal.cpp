/**
 * @file binary-tree-preorder-traversal.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-29
 * https://leetcode.cn/problems/binary-tree-preorder-traversal/
 * 二叉树的前序遍历
 *
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

// 递归序遍历
class Solution0
{
public:
    void traversal(TreeNode *cur, vector<int> &result)
    {
        if (cur == NULL)
        {
            return;
        }
        result.push_back(cur->val);    // 头
        traversal(cur->left, result);  // 左
        traversal(cur->right, result); // 右
    }
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        traversal(root, result);
        return result;
    }
};

// 压栈遍历
class Solution1
{
public:
    vector<int> preorderTraversal(TreeNode *root)
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
            // 弹出
            TreeNode *node = st.top(); // 中
            st.pop();
            // 打印保存
            result.push_back(node->val);

            // 压栈先右后左
            if (node->right)
            {
                st.push(node->right); // 右
            }
            if (node->left)
            {
                st.push(node->left); // 左
            }
        }

        return result;
    }
};

// 标记法
class Solution2
{
public:
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<int> result;
        stack<TreeNode *> st;
        if (root != NULL)
        {
            st.push(root);
        }
        while (!st.empty())
        {
            TreeNode *node = st.top(); // 上一次压栈的节点
            if (node != NULL)
            {
                st.pop();
                if (node->right) // 右
                {
                    st.push(node->right);
                }
                if (node->left) // 左
                {
                    st.push(node->left);
                }
                st.push(node); // 中
                st.push(NULL);
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