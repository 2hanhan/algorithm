/**
 * @file path-sum.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-04
 * 112.路径总和
 * https://leetcode.cn/problems/path-sum/
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

// 暴力递归
class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) 
    {
        if(root == nullptr)
            return false;

        // base case
        targetSum = targetSum - root->val;
        if(root->left == nullptr && root->right == nullptr && targetSum == 0)
            return true;

        
        if(hasPathSum(root->left,targetSum))
            return true;
        
        
        if(hasPathSum(root->right,targetSum))
            return true;

        return false;
    }
};