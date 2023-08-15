/**
 * @file lowest-common-ancestor-of-a-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-10
 * 236. 二叉树的最近公共祖先
 * https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 * @copyright Copyright (c) 2023
 * 
 */
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

class Solution {
public:
    // 前提是 p，q 一定都是树中的节点
    // 函数返回值为是p,q的其中之一的最近的根节点，更接近根节点的会把不接近的顶替掉
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        //base case
        if(root == p ||root ==q ||root == nullptr)
        {
            return root;
        }

        TreeNode *left = lowestCommonAncestor(root->left,p,q);
        TreeNode *right = lowestCommonAncestor(root->right,p,q);
        if(left != nullptr && right != nullptr)
            return root;
        if(left == nullptr) 
            return right;
        return left;

    }
};