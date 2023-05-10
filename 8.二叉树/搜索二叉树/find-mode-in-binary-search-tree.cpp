/**
 * @file find-mode-in-binary-search-tree.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-10
 * 501. 二叉搜索树中的众数
 * https://leetcode.cn/problems/find-mode-in-binary-search-tree/
 * @copyright Copyright (c) 2023
 *
 */
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
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

// 中序遍历统计个数
class Solution
{
public:
    vector<int> findMode(TreeNode *root)
    {
        vector<int> result;
        if (root == nullptr)
            return result;

        int countmax = 0;
        int count = 0;
        TreeNode *pre = nullptr;

        // 中序遍历
        TreeNode *cur = root;
        stack<TreeNode *> st;
        while (cur != nullptr || !st.empty())
        {
            if (cur != nullptr)
            {
                st.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = st.top();
                st.pop();
                if (pre != nullptr && pre->val == cur->val)
                {
                    count++;
                }
                else
                {
                    count = 0;
                }

                // if (pre == nullptr)
                // {
                //     count = 0;
                // }
                // else if (pre->val == cur->val)
                // {
                //     count++;
                // }
                // else
                // {
                //     count = 0;
                // }

                cout<<"[val:"<<cur->val<<"cout:"<<count<<"]"<<endl;

                if (count == countmax)
                {
                    result.push_back(cur->val);
                }
                else if (count > countmax)
                {
                    result.clear();
                    result.push_back(cur->val);
                    countmax = count;
                }

                pre = cur;
                cur = cur->right;
            }
        }
        return result;
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
int main(int argc, char **argv)
{
    cout << endl;

    TreeNode *root;
    int x[] = {1,0,1,0,0,1,1,0};
    

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

    vector<int> result;
    Solution solution;
    result = solution.findMode(root);
    cout << "soulution:";
    printall(result);

    cout << endl;

    return 0;
}