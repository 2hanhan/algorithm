/**
 * @file search-in-a-binary-search-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-06
 * 700. 二叉搜索树中的搜索
 * https://leetcode.cn/problems/search-in-a-binary-search-tree/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
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

// 暴力递归
class Solution
{
public:
    TreeNode *searchBST(TreeNode *root, int val)
    {
        // base case
        if (root == nullptr)
            return nullptr;

        if (root->val == val)
            return root;

        if (root->val < val)
            return searchBST(root->right, val);
        else
            return searchBST(root->left, val);
    }
};

// 迭代
class Solution
{
public:
    TreeNode *searchBST(TreeNode *root, int val)
    {

        while (root != nullptr)
        {
            if (root->val == val)
                return root;
            if (root->val < val)
                root = root->right;
            else
                root = root->left;
        }
        return root;
    }
};