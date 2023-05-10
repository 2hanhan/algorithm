/**
 * @file lowest-common-ancestor-of-a-binary-search-tree.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-10
 * 235. 二叉搜索树的最近公共祖先
 * https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/
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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        while(root != nullptr)
        {
            //分裂了直接返回
            if(p->val > root->val && q->val > root->val)
                root = root->right;
            else if(p->val < root->val && q->val < root->val)
                root = root->left;
            else
                return root;
        }
        return root;
        
    }
};