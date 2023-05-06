/**
 * @file maximum-binary-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-06
 * 654. 最大二叉树
 * https://leetcode.cn/problems/maximum-binary-tree/
 * 给定一个不重复的整数数组 nums 。 最大二叉树 可以用下面的算法从 nums 递归地构建:
 *   创建一个根节点，其值为 nums 中的最大值。
 *   递归地在最大值 左边 的 子数组前缀上 构建左子树。
 *   递归地在最大值 右边 的 子数组后缀上 构建右子树。
 * 返回 nums 构建的 最大二叉树 。
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
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

//暴力递归
class Solution
{
public:
    TreeNode *constructMaximumBinaryTreeRe(vector<int> &nums, int left, int right)
    {
        // base case
        TreeNode *root;
        if (left + 1 >= right)
        {
            root = new TreeNode(nums[left]);
            return root;
        }

        //[left, right）
        int mid = left;
        for (int i = left + 1; i < right; i++)
        {
            if (nums[mid] < nums[i])
                mid = i;
        }
        root = new TreeNode(nums[mid]);
        if (left < mid)
            root->left = constructMaximumBinaryTreeRe(nums, left, mid);
        if (mid + 1 < right)
            root->right = constructMaximumBinaryTreeRe(nums, mid + 1, right);
        return root;
    }

    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        int right = nums.size();
        if (right == 0)
            return nullptr;
        return constructMaximumBinaryTreeRe(nums, 0, right);
    }
};

//暴力递归
class Solution
{
public:
    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        // 根节点
        TreeNode *root = new TreeNode();
        if (nums.size() == 1)
        {
            root->val = nums[0];
            return root;
        }
        // 当前数组的最大值
        int maxID = 0;
        int maxValue = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > maxValue)
            {
                maxValue = nums[i];
                maxID = i;
            }
        }
        root->val = maxValue;
        if (maxID > 0) // leftsize > 1
        {
            vector<int> leftNums(nums.begin(), nums.begin() + maxID);
            root->left = constructMaximumBinaryTree(leftNums);
        }
        if (maxID < nums.size() - 1) // rightsize > 1
        {
            vector<int> rightNums(nums.begin() + maxID + 1, nums.end());
            root->right = constructMaximumBinaryTree(rightNums);
        }
        return root;
    }
};