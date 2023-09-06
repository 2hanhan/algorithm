/**
 * @file insert-into-a-binary-search-tree.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-10
 * 701. 二叉搜索树中的插入操作
 * https://leetcode.cn/problems/insert-into-a-binary-search-tree/
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

//直接在叶子节点插入
class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) 
    {
        if(root == nullptr)
        {
             TreeNode * node = new TreeNode(val);
             return node;
        }

        TreeNode * pre = nullptr;
        TreeNode * cur = root;
        TreeNode * node = new TreeNode(val);
        while(cur != nullptr)
        {
            pre = cur;
            if(val<cur->val)
                cur = cur->left;
            else
                cur =cur->right;
        }
        if(val < pre->val)
            pre->left = node;
        else
            pre->right = node;

        return root;

    }
};