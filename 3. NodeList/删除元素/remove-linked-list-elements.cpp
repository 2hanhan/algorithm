/**
 * @file remove-linked-list-elements.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-07
 * - 3.2 移除链表中元素
 * - 方法1：
 * - 首先单独处理head,cur = head
 * - 然后处理依次处理当前节点cur的的next->val==val，
 * - 在这之前要判断cur和next不为空NULL，判断cur是为了防止head处理完链表已经为空，判断next就是不能取cur->next(NULL)->val
 * - 如果成立则经cur->next = cur->next->next,否则cur = cur->next
 *  - 方法2:
 * - 设置一个虚拟的头节点节点dummyhead，dummyhead->next = head,cur = dummyhead
 * - 然后处理依次处理当前节点cur的的next->val==val，
 * - 在这之前要判断cur和next不为空NULL，判断cur是为了防止head处理完链表已经为空，判断next就是不能取cur->next(NULL)->val
 * - 如果成立则经cur->next = cur->next->next,否则cur = cur->next
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
using namespace std;

/**
 * @brief 链表节点的定义
 *
 */
struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 方法1
// class Solution
// {
// public:
//     ListNode *removeElements(ListNode *head, int val)
//     {
//         // 单独处理head节点
//         while (head != NULL && head->val == val)
//         {
//             ListNode *temp = head;
//             head = head->next;
//             delete temp;
//         }
//         // 处理非head节点
//         ListNode *cur = head;
//         while (cur != NULL && cur->next != NULL)
//         {
//             if (cur->next->val == val)
//             {
//                 ListNode *temp = cur->next;
//                 cur->next = cur->next->next;
//                 delete temp;
//             }
//             else
//             {
//                 cur = cur->next;
//             }
//         }
//         return head;
//     }
// };

// 方法2
class Solution
{
public:
    ListNode *removeElements(ListNode *head, int val)
    {
        ListNode *dummyhead = new ListNode(0, head);
        ListNode *cur = dummyhead;
        while (cur != NULL && cur->next != NULL)
        {
            if (cur->next->val == val)
            {
                ListNode *temp = cur->next;
                cur->next = cur->next->next;
                delete temp;
            }
            else
            {
                cur = cur->next;
            }
        }
        return dummyhead->next;
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入链表大小 n" << std::endl;
    cin >> n;

    ListNode *head;
    ListNode *last, *cur;

    cout << "输入n个数字生成链表" << std::endl;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cur = new ListNode(x);
        if (i == 0)
        {
            head = cur;
            last = cur;
        }
        else
        {
            last->next = cur;
            last = cur;
        }
    }
    int val;
    cout << "输入待删除数字" << std::endl;
    cin >> val;

    Solution solution;

    std::cout << "原链表:" << std::endl;
    cur = head;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;

    solution.removeElements(head, val);

    std::cout << "删除 " << val << " 后链表:" << std::endl;
    cur = head;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
    cout << "-----结束-----" << endl;
    return 0;
}