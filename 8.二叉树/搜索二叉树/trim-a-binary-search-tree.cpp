/**
 * @file trim-a-binary-search-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 669. 修剪二叉搜索树
 * https://leetcode.cn/problems/trim-a-binary-search-tree/
 * @copyright Copyright (c) 2023
 *
 */
#include <iostream>
#include <queue>
#include <stack>
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

// 暴力递归，leetcode中加上释放内存就无法通过
class Solution
{
public:
    // 释放内存
    // void deleteformroot(TreeNode *root)
    // {
    //     if (root == nullptr)
    //         return;

    //     deleteformroot(root->left);
    //     deleteformroot(root->right);
    //     delete root;
    // }
    TreeNode *trimBST(TreeNode *root, int low, int high)
    {
        // base case
        if (root == nullptr)
            return root;
        if (root->val < low)
        {
            // deleteformroot(root->left);
            TreeNode *right = trimBST(root->right, low, high);
            // delete root;
            return right;
        }
        if (root->val > high)
        {
            // deleteformroot(root->right);
            TreeNode *left = trimBST(root->left, low, high);
            // delete root;
            return left;
        }

        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);

        return root;
    }
};

template <class T>
void printall(T &mySTL)
{
    cout << endl
         << typeid(mySTL).name() << ":";
    for (auto iter = mySTL.begin(); iter != mySTL.end(); iter++)
    {
        cout << *iter << " ";
    }
}

void levelOrder(TreeNode *root)
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
            // 取出当前层的所有节
            TreeNode *node = que.front();
            que.pop();
            cout<<node->val<<" ";
            // 保存下一层的所有节点
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        cout<<endl;
    }
}


int main(int argc, char **argv)
{
    cout << endl;

    TreeNode *root;
    int x[] = {1, -1, 2};

    int i = 0;
    int size = sizeof(x) / 4;
    if (size > 0)
        root = new TreeNode(x[i]);

    queue<TreeNode *> mySt;
    mySt.push(root);
    while (!mySt.empty())
    {
        TreeNode *node = mySt.front();
        mySt.pop();
        if (i < size - 1 && x[++i] != -1)
        {

            TreeNode *left = new TreeNode(x[i]);
            node->left = left;
            mySt.push(left);
        }
        if (i < size - 1 && x[++i] != -1)
        {

            TreeNode *right = new TreeNode(x[i]);
            node->right = right;
            mySt.push(right);
        }
    }

    Solution solution;
    levelOrder(root);
    root = solution.trimBST(root, 2, 4);
    cout << "soulution:"<<endl;
    levelOrder(root);
    cout << endl;

    return 0;
}