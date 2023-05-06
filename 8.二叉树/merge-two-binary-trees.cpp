/**
 * @file merge-two-binary-trees.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-06
 * 617. 合并二叉树
 * https://leetcode.cn/problems/merge-two-binary-trees/
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

//暴力递归
class Solution
{
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
    {
        // base case
        if (root1 == nullptr && root2 == nullptr)
            return nullptr;

        TreeNode *root;
        if (root1 == nullptr)
        {
            root = root2;
            root->left = mergeTrees(nullptr, root2->left);
            root->right = mergeTrees(nullptr, root2->right);
            return root;
        }
        if (root2 == nullptr)
        {
            root = root1;
            root->left = mergeTrees(root1->left, nullptr);
            root->right = mergeTrees(root1->right, nullptr);
            return root;
        }

        root = root1;
        root->val = root1->val + root2->val;
        root->left = mergeTrees(root1->left, root2->left);
        root->right = mergeTrees(root1->right, root2->right);
        delete root2;

        return root;
    }
};
