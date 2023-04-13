/**
 * @file construct-binary-tree-from-inorder-and-postorder-traversal.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-16
 * https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
 * 从中序与后序遍历序列构造二叉树
 * 给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历，
 * postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。
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
    // 通过后序遍历（左右中）寻找中间节点，去切分中序遍历（左中右）
    // 完后对后序遍历进行切分，再次寻找中间节点
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
    {
        if (postorder.size() == 0)
            return NULL;

        // 中间节点
        int value = postorder[postorder.size() - 1];
        TreeNode *root = new TreeNode(value);

        // 切分中序遍历
        int inorderID;
        for (int i = 0; i < inorder.size(); i++)
        {
            // 计算中间节点在中序遍历中的位置
            if (inorder[i] == value)
            {
                inorderID = i;
                break;
            }
        }
        vector<int> leftIorder(inorder.begin(), inorder.begin() + inorderID);
        vector<int> rightIorder(inorder.begin() + inorderID + 1, inorder.end());

        // 切分后序遍历
        int postorderID = leftIorder.size(); // size应该是相等的
        vector<int> leftPostorder(postorder.begin(), postorder.begin() + postorderID);
        vector<int> rightPostorder(postorder.begin() + postorderID, postorder.end() - 1);

        // 连接左右节点
        root->left = buildTree(leftIorder, leftPostorder);
        root->right = buildTree(rightIorder, rightPostorder);

        return root;
    }
};