/**
 * @file reverse-linked-list.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-07
 * - 3.4 反转链表
 * - 方法1：双指针法
 * - 思路依次调转cur->next指向前一个节点pre
 * - 注意需要首先保存cur->next的指针然后调转
 * @copyright Copyright (c) 2022
 *
 */

#include <stdlib.h>
#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 方法1：
// class Solution
// {
// public:
//     ListNode *reverseList(ListNode *head)
//     {
//         ListNode *temp; // 保存cur的下一个节点
//         ListNode *cur = head;
//         ListNode *pre = NULL;

//         while (cur != NULL)
//         {
//             temp = cur->next;
//             cur->next = pre;
//             pre = cur;
//             cur = temp;
//         }
//         return pre;
//     }
// };

// 方法2：
class Solution
{
public:
    ListNode *reverse(ListNode *pre, ListNode *cur)
    {
        if (cur == NULL)
            return pre;

        ListNode *temp = cur->next;
        cur->next = pre;
        return reverse(cur, temp);
    }
    ListNode *reverseList(ListNode *head)
    {
        return reverse(NULL, head);
    }
};

// 方法3：
// class Solution
// {
// public:
//     ListNode *reverseList(ListNode *head)
//     {
//         if (head == NULL)
//             return NULL;
//         if (head->next == NULL)
//             return head;

//         ListNode *last = reverseList(head->next);
//         head->next->next = head;
//         head->next = NULL;

//         return last;
//     }
// };

int main(int argc, char **argv)
{

    int n;
    cout << "输入链表大小 n" << std::endl;
    cin >> n;

    ListNode *head = NULL;
    ListNode *last = NULL, *cur = NULL;

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

    std::cout << "原链表:" << std::endl;
    cur = head;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;

    Solution solution;
    head = solution.reverseList(head);

    std::cout << "翻转后链表:" << std::endl;
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