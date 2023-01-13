/**
 * @file maximum-depth-of-n-ary-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
 * N 叉树的最大深度
 * 最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。
 * N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔（请参见示例）。
 * @copyright Copyright (c) 2023
 *
 */

#include <stack>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// N叉树的定义
class Node
{
public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val)
    {
        val = _val;
    }

    Node(int _val, vector<Node *> _children)
    {
        val = _val;
        children = _children;
    }
};

// 递归方式
class Solution0
{
public:
    int getDepth(Node *node)
    {
        if (node == NULL)
            return 0;
        int depth = 0;
        for (int i = 0; i < node->children.size(); i++)
        {
            depth = max(depth, getDepth(node->children[i]));
        }
        return depth + 1;
    }
    int maxDepth(Node *root)
    {
        return getDepth(root);
    }
};

// 层序遍历迭代
class Solution0
{
public:
    int maxDepth(Node *root)
    {
        int depth = 0;
        queue<Node *> que;
        if (root != NULL)
            que.push(root);
        while (!que.empty())
        {
            int size = que.size();
            depth++;
            for (int i = 0; i < size; i++)
            {
                Node *node = que.front();
                que.pop();
                for (int j = 0; j < node->children.size(); j++)
                {
                    que.push(node->children[j]);
                }
            }
        }
        return depth;
    }
};