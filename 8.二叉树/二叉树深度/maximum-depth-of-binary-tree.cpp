/**
 * @file maximum-depth-of-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
 * https://leetcode.cn/problems/maximum-depth-of-binary-tree/
 * 二叉树最大深度
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

// 递归的方式
class Solution0
{
public:
    int getDepth(TreeNode *node)
    {
        if (node == NULL)
            return 0;
        int depth = 1 + max(getDepth(node->left), getDepth(node->right));
        return depth;
    }
    int maxDepth(TreeNode *root)
    {
        return getDepth(root);
    }
};

// 迭代层序遍历
class Solution1
{
public:
    int maxDepth(TreeNode *root)
    {
        int depth = 0;
        queue<TreeNode *> que;
        if (root != NULL)
            que.push(root);

        while (!que.empty())
        {
            int size = que.size();
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = que.front();
                que.pop();
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
            depth++;
        }
        return depth;
    }
};
