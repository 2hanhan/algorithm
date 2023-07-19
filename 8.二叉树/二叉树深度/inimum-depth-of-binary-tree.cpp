/**
 * @file inimum-depth-of-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
 * https://leetcode.cn/problems/minimum-depth-of-binary-tree/
 * 二叉树的最小深度
 * @copyright Copyright (c) 2023
 * 给定一个二叉树，找出其最小深度。
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 * 说明：叶子节点是指没有子节点的节点。
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

// 递归方式
class Solution0
{
public:
    int getMinDepth(TreeNode *node)
    {
        if (node == NULL)
            return 0;

        int minDepthLeft = getMinDepth(node->left);
        int minDepthRight = getMinDepth(node->right);

        // 只有一个为空并不是叶子节点
        if (node->left == NULL && node->right != NULL)
            return minDepthRight + 1;

        if (node->right == NULL && node->left != NULL)
            return minDepthLeft + 1;

        // 两个为空的情况是叶子节点，或者两个都不为空
        return min(minDepthLeft, minDepthRight) + 1;
    }
    int minDepth(TreeNode *root)
    {
        return getMinDepth(root);
    }
};

// 层序遍历迭代
class Solution1
{
public:
    int minDepth(TreeNode *root)
    {
        int depth = 0;
        queue<TreeNode *> que;
        if (root != NULL)
            que.push(root);
        while (!que.empty())
        {
            int size = que.size();
            depth++;
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = que.front();
                que.pop();
                // 左右节点均为空，到叶子节点返回
                if (!node->left && !node->right)
                    return depth;
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
        }
        return depth;
    }
};