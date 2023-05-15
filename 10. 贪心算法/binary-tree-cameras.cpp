/**
 * @file binary-tree-cameras.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <queue>
#include <iostream>
using namespace std;
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
    int result;
    /**
     * @brief
     * 更加子节点的信息判断当前节点是否需要放置camera;
     * @param root
     * @return int 0：没有监控到 1：有摄像头 2：有监控到
     */
    int minCameraCoverRe(TreeNode *root)
    {
        // base case
        if (root == nullptr)
            return 2;
        cout << "[" << root->val << "]";

        int left = minCameraCoverRe(root->left);
        int right = minCameraCoverRe(root->right);

        if (left == 2 && right == 2)
        {
            // 两个子节点都有被监控到，则当前没有被监控到
            return 0;
        }
        if (left == 0 || right == 0)
        {
            // 两个子节点都没有被监控到，则当前一定要放摄像头
            result++;
            return 1;
        }
        if (left == 1 || right == 1)
        {
            // 如果有一个子节点有摄像头，则当前节点有被监控到
            return 2;
        }
    }
    int minCameraCover(TreeNode *root)
    {
        result = 0;
        return minCameraCoverRe(root) == 0 ? (result + 1) : result;
    }
};

int main(int argc, char **argv)
{
    TreeNode *root;
    int x[] = {0, 0, -1, 0, 0};

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

    int result =0;
    Solution solution;
    result = solution.minCameraCover(root);
    cout << "soulution:" << result << endl;

    cout << endl;

    return 0;
}