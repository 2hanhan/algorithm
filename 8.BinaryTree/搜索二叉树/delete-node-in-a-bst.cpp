/**
 * @file delete-node-in-a-bst.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 450. 删除二叉搜索树中的节点
 * https://leetcode.cn/problems/delete-node-in-a-bst/
 * @copyright Copyright (c) 2023
 *
 */

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
    // 在把删除之后的左子节点放在右子节点最左侧的叶子节点位置
    TreeNode *deleteOneNode(TreeNode *node)
    {
        if (node == nullptr)
            return node;
        if (node->right == nullptr)
            return node->left;
        // 把左边的都连接到右边的适当位置
        TreeNode *cur = node->right;
        while (cur->left != nullptr)
        {
            cur = cur->left;
        }
        cur->left = node->left;
        return node->right;
    }

    TreeNode *deleteNode(TreeNode *root, int key)
    {
        // step 1 搜索key的位置
        TreeNode *node = root;
        TreeNode *pre = nullptr;
        while (node != nullptr)
        {
            if (node->val == key)
                break;
            pre = node;
            if (node->val > key)
                node = node->left;
            else
                node = node->right;
        }

        // step 2 删除
        // 只有头节点
        if (pre == nullptr)
        {
            root = deleteOneNode(node);
            if (node != nullptr)
                delete node;
            return root;
        }

        if (pre->left != nullptr && pre->left->val == key)
        {
            pre->left = deleteOneNode(node);
            if (node != nullptr)
                delete node;
        }
        if (pre->right != nullptr && pre->right->val == key)
        {
            pre->right = deleteOneNode(node);
            if (node != nullptr)
                delete node;
        }
        return root;
    }
};