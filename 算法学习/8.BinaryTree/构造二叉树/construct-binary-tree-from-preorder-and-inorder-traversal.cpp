/**
 * @file construct-binary-tree-from-preorder-and-inorder-traversal.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 * https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 * 从前序与中序遍历序列构造二叉树
 * 给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
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
class Solution
{
public:
    // preorder 中左右
    // inorder 左中右
    // 根据preorder获取中间节点切分inorder
    // 根据inorder切分长度同步切分preorder
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.size() == 0)
            return NULL;

        int value = preorder[0];
        TreeNode *root = new TreeNode(value);

        int inorderID;
        for (int i = 0; i < inorder.size(); i++)
        {
            if (inorder[i] == value)
            {
                inorderID = i;
            }
        }
        vector<int> leftInorder(inorder.begin(), inorder.begin() + inorderID);
        vector<int> rightInorder(inorder.begin() + inorderID + 1, inorder.end());

        int preorderID = leftInorder.size() + 1;
        vector<int> leftPreorder(preorder.begin() + 1, preorder.begin() + preorderID);
        vector<int> rightPreorder(preorder.begin() + preorderID, preorder.end());

        root->left = buildTree(leftPreorder, leftInorder);
        root->right = buildTree(rightPreorder, rightInorder);

        return root;
    }
};