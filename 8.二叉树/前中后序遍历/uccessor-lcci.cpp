/**
 * @file uccessor-lcci.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 后继节点
 * https://leetcode.cn/problems/successor-lcci/
 * @copyright Copyright (c) 2023
 * 
 */

#include <vector>
#include <queue>
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

// 直接把后序遍历求出来，然后取寻找,没注意题目说的是二叉搜索树算了
class Solution {
public:
    void inorder(TreeNode* root, vector<TreeNode*> &result)
    {
        if(root->left!=nullptr)
            inorder(root->left,result);
        result.push_back(root);
        if(root->right!=nullptr)
            inorder(root->right,result);

    }

    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) 
    {
        vector<TreeNode*> result;
        inorder(root,result);
        for(int i = 0;i<result.size()-1;i++)
        {
            if(result[i]==p)
                return result[i+1];
        }
        return nullptr;
    }
};