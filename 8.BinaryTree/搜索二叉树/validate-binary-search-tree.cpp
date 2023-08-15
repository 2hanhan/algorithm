/**
 * @file validate-binary-search-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-06
 * 98. 验证二叉搜索树
 * https://leetcode.cn/problems/validate-binary-search-tree/
 * @copyright Copyright (c) 2023
 *
 */

#include <vector>
#include <algorithm>
#include <limits.h>
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
    bool isValidBSTRe(TreeNode *root, long long &min, long long &max)
    {
        // base case
        if (root == nullptr)
        {
            min = LONG_LONG_MAX;
            max = LONG_LONG_MIN;
            return true;
        }

        long long leftmin = LONG_LONG_MAX;
        long long leftmax = LONG_LONG_MIN;
        long long rightmin = LONG_LONG_MAX;
        long long rightmax = LONG_LONG_MIN;

        bool left = isValidBSTRe(root->left, leftmin, leftmax);
        bool right = isValidBSTRe(root->right, rightmin, rightmax);

        if (!left || !right)
            return false;
        if (leftmax >= root->val)
            return false;
        if (rightmin <= root->val)
            return false;

        // 更新最大最小
        min = root->val < leftmin ? root->val : leftmin;
        min = min < rightmin ? min : rightmin;
        max = root->val > leftmax ? root->val : leftmax;
        max = max > rightmax ? max : rightmax;

        return true;
    }

    bool isValidBST(TreeNode *root)
    {
        long long min = LONG_LONG_MAX;
        long long max = LONG_LONG_MIN;
        return isValidBSTRe(root, min, max);
    }
};

// 中序遍历，从大到小，即为搜索二叉树
class Solution
{
public:
    TreeNode *pre;
    bool isValidBST(TreeNode *root)
    {
        if (root == nullptr)
            return true;

        if (!isValidBST(root->left))
            return false;

        if (pre != nullptr && pre->val >= root->val)
            return false;
        pre = root;
        if (!isValidBST(root->right))
            return false;

        return true;
    }
};
