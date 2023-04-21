/**
 * @file average-of-levels-in-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-04
 * https://leetcode.cn/problems/average-of-levels-in-binary-tree/
 * 二叉树的层平均值
 * @copyright Copyright (c) 2023
 * 给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10e-5 以内的答案可以被接受。
 */

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
    vector<double> averageOfLevels(TreeNode *root)
    {
        queue<TreeNode *> que;
        vector<double> result;
        if (root != NULL)
            que.push(root);
        while (!que.empty())
        {
            int size = que.size();
            double sum = 0; // 统计每一层的和
            for (int i = 0; i < size; i++)
            {
                TreeNode *node = que.front();
                que.pop();
                sum += node->val; // 求和
                if (node->left)
                    que.push(node->left);
                if (node->right)
                    que.push(node->right);
            }
            result.push_back(sum / size); // 求均值
        }
        return result;
    }
};