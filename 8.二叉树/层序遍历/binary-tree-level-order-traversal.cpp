/**
 * @file binary-tree-level-order-traversal.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-04
 * https://leetcode.cn/problems/binary-tree-level-order-traversal/
 * 二叉树层序遍历
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
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> que;
        vector<vector<int>> result;
        if (root != NULL)
            que.push(root);

        while (!que.empty())
        {
            int size = que.size(); // 当前层的的size
            vector<int> vec;       // 当前层的节点
            for (int i = 0; i < size; i++)
            {
                //取出当前层的所有节
                TreeNode *node = que.front();
                que.pop();
                vec.push_back(node->val);
                //保存下一层的所有节点
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
            result.push_back(vec);
        }
        return result;
    }
};