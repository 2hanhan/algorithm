/**
 * @file balanced-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
 * https://leetcode.cn/problems/balanced-binary-tree
 * 平衡二叉树
 * 给定一个二叉树，判断它是否是高度平衡的二叉树。
 * 本题中，一棵高度平衡二叉树定义为：一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。
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

class Solution
{
public:
    vector<int> getBalancedAndDepth(TreeNode *node)
    {
        vector<int> result{1, 0}; // 数组第一个存储是否是balanced 第二个存储当前层深度
        if (node == NULL)
            return result;

        vector<int> resultLeft = getBalancedAndDepth(node->left);
        vector<int> resultRight = getBalancedAndDepth(node->right);

        // 如果子树不是平衡二叉树，或者深度相差大于1，则不是平衡二叉树
        if (resultLeft[0] == 0 || resultRight[0] == 0 ||
            abs(resultLeft[1] - resultRight[1]) > 1)
            result[0] = 0;

        // 深度值子树中最大的+1
        result[1] = max(resultLeft[1], resultRight[1]) + 1;

        return result;
    }

    bool isBalanced(TreeNode *root)
    {
        return getBalancedAndDepth(root)[0];
    }
};