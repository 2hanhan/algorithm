/**
 * @file binary-tree-paths.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-01-13
 * https://leetcode.cn/problems/binary-tree-paths/
 * 二叉树的所有路径
 * 给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。
 * 叶子节点 是指没有子节点的节点。
 * @copyright Copyright (c) 2023
 *
 */
#include <stack>
#include <string>
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

// 经典写法
class Solution0
{
public:
    void traversal(TreeNode *node, string path, vector<string> &result)
    {
        path += to_string(node->val); // int 转换为字符串
        if (node->left == NULL && node->right == NULL)
        {
            result.push_back(path);
            return;
        }

        if (node->left)
            traversal(node->left, path + "->", result);
        if (node->right)
            traversal(node->right, path + "->", result);
    }
    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> result;
        string path;
        if (root == NULL)
            return result;
        traversal(root, path, result);
        return result;
    }
};

// 回溯写法
class Solution1
{
public:
    void traversal(TreeNode *node, string &path, vector<string> &result)
    {
        path += to_string(node->val); // int 转换为字符串
        if (node->left == NULL && node->right == NULL)
        {
            result.push_back(path);
            return;
        }

        if (node->left)
        {
            path += "->";                                                     // 2个size
            traversal(node->left, path, result);                              // 添加新的节点
            path.resize(path.size() - to_string(node->left->val).size() - 2); // 回溯到上一个节点
        }

        if (node->right)
        {
            path += "->";                                                      // 2个size
            traversal(node->right, path, result);                              // 添加新的节点
            path.resize(path.size() - to_string(node->right->val).size() - 2); // 回溯到上一个节点
        }
    }
    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> result;
        string path;
        if (root == NULL)
            return result;
        traversal(root, path, result);
        return result;
    }
};