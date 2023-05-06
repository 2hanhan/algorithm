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
#include <iostream>
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


int main(int argc, char **argv)
{
    TreeNode *root;
    int x[] = {1, 2, 3, 4, NULL, NULL, 5};

    int i = 0;
    int size = sizeof(x) / 4;
    cout << size;
    if (size > 0)
        root = new TreeNode(x[i]);

    queue<TreeNode *> mySt;
    mySt.push(root);
    while (!mySt.empty())
    {
        TreeNode *node = mySt.front();
        mySt.pop();
        if (i < size - 1 && x[++i] != NULL)
        {

            TreeNode *left = new TreeNode(x[i]);
            node->left = left;
            mySt.push(left);
        }
        if (i < size - 1 && x[++i] != NULL)
        {

            TreeNode *right = new TreeNode(x[i]);
            node->right = right;
            mySt.push(right);
        }
    }

    int result;
    Solution1 solution1;
    result = solution1.maxDepth(root);
    cout << "soulution:" << result << endl;

    cout << endl;

    return 0;
}
