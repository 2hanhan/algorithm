/**
 * @file count-complete-tree-nodes.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
 * https://leetcode.cn/problems/count-complete-tree-nodes
 * 完全二叉树的节点个数
 * 给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。
 * 完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2h 个节点。
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

// 递归遍历全部节点
// 时间复杂度：O(n)
// 空间复杂度：O(n)
class Solution0
{
public:
    int countNodes(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

// 利用完全二叉树性质递归
// 时间复杂度：O(log n × log n)
// 空间复杂度：O(log n)

class Solution0
{
public:
    int countNodes(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        
        //如果左右侧节点的深度相等，则当前节点的子树是一个满二叉树
        TreeNode *left = root->left;
        TreeNode *right = root->right;
        int leftDepth = 0;
        int rightDepth = 0;
        while (left)
        {
            left = left->left;
            leftDepth++;
        }
        while (right)
        {
            right = right->right;
            rightDepth++;
        }
        if (leftDepth == rightDepth)
        {
            // 左移一位相当于*2
            return (2 << leftDepth) - 1;//左右的深度相等，说明是满树，个数为 2^n - 1

        }

        // 不是满二叉树的，则分块计算
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};