/**
 * @file find-bottom-left-tree-value.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include  <utility>
using namespace std;

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
    pair<int,int> findBottomLeftValueRe(TreeNode *node)
    {
        //base case
        if(node->left == nullptr && node->right == nullptr)
            return make_pair(1,node->val);

        pair<int,int> left ,right;
        if(node->left != nullptr)
        {
            left = findBottomLeftValueRe(node->left);
        }
        if(node->right != nullptr)
        {
            right = findBottomLeftValueRe(node->right);
        }
        if(left.first>=right.first)
            return make_pair(left.first+1,left.second);
        else
            return make_pair(right.first+1,right.second);
        
    }

    int findBottomLeftValue(TreeNode* root) {
        return findBottomLeftValueRe(root).second;

    }
};