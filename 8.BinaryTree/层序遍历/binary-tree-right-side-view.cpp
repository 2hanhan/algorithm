/**
 * @file binary-tree-right-side-view.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-04
 * https://leetcode.cn/problems/binary-tree-right-side-view/
 * 二叉树的右视图
 * 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
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

class Solution
{
public:
    vector<int> rightSideView(TreeNode *root)
    {
        queue<TreeNode *> que;
        vector<int> result;
        if (root != NULL)
            que.push(root);

        while (!que.empty())
        {
            int size = que.size(); // 当前层的的size
            for (int i = 0; i < size; i++)
            {
                // 取出当前层的所有节
                TreeNode *node = que.front();
                que.pop();
                if (i == size - 1) // 当前从的最后一个节点就是最右侧的节点
                    result.push_back(node->val);
                // 保存下一层的所有节点
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
        }
        return result;
    }
};