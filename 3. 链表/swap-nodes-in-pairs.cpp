/**
 * @file swap-nodes-in-pairs.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-11
 * - 3.5 相邻两两交换，使用更改指针的方式。
 * - 注意：
 * - 终止条件 cur->next != NULL &&cur->next->next!= NULL
 * - 先后顺序不能换，因为后一个的next可能为空不能再取next
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

class Solution0
{
public:
    ListNode *swapPairs(ListNode *head)
    {

        ListNode *dummyhead = new ListNode();
        dummyhead->next = head;

        ListNode *cur = dummyhead;
        while (cur->next != NULL && cur->next->next != NULL)
        {
            ListNode *temp = cur->next->next->next;
            ListNode *temp1 = cur->next->next;

            cur->next->next->next = cur->next; // 2->1 交换
            cur->next->next = temp;            // 1->3 指向下一个
            cur->next = temp1;                 // dummyhead->2 类似头结点

            cur = cur->next->next;
        }
        return dummyhead->next;
    }
};

class Solution1
{
public:
    ListNode *swapPairs(ListNode *head)
    {
        ListNode *dummyHead = new ListNode(0); // 设置一个虚拟头结点
        dummyHead->next = head;                // 将虚拟头结点指向head，这样方面后面做删除操作
        ListNode *cur = dummyHead;
        while (cur->next != nullptr && cur->next->next != nullptr)
        {
            ListNode *tmp = cur->next;              // 记录临时节点
            ListNode *tmp1 = cur->next->next->next; // 记录临时节点

            cur->next = cur->next->next;  // dummyhead->2
            cur->next->next = tmp;        // 2->1
            cur->next->next->next = tmp1; // 1->3

            cur = cur->next->next; // cur移动两位，准备下一轮交换
        }
        return dummyHead->next;
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

    Solution0 solution;

    std::cout << "原链表:" << std::endl;
    cur = head;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;

    cur = solution.swapPairs(head);

    std::cout << "相邻两两交换后链表:" << std::endl;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
    cout << "-----结束-----" << endl;
    return 0;
}