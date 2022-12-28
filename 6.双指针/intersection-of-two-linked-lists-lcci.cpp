/**
 * @file intersection-of-two-linked-lists-lcci.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-19
 * 链表相交
 * - 统计两个链表的长度
 * - 跳过前面一定不重叠的区域
 * - 变量可能重叠的部分，根据指针是否一致判断是否重叠
 * - 时间复杂度：O(n + m) 空间复杂度：O(1)
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

class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *curA = headA;
        ListNode *curB = headB;
        int lenA = 0, lenB = 0;

        while (curA != NULL)
        {
            curA = curA->next;
            lenA++;
        }
        while (curB != NULL)
        {
            curB = curB->next;
            lenB++;
        }

        curA = headA;
        curB = headB;
        if (lenB > lenA)
        {
            swap(lenA, lenB);
            swap(curA, curB);
        }
        int gap = lenA - lenB;

        while (gap--)
        {
            curA = curA->next;
        }

        while (curA != NULL)
        {
            if (curA == curB)
            {
                return curA;
            }
            curA = curA->next;
            curB = curB->next;
        }
        return NULL;
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入链表大小 n" << std::endl;
    cin >> n;

    ListNode *head, *headA, *headB;
    ListNode *last, *cur;

    cout << "输入" << n << "个数字生成链表" << std::endl;
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

    cout << "输入链表A不一样的部分的大小 n" << std::endl;
    cin >> n;
    cout << "输入" << n << "个数字生成链表A" << std::endl;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cur = new ListNode(x);
        if (i == 0)
        {
            headA = cur;
            last = cur;
        }
        else
        {
            last->next = cur;
            last = cur;
        }
    }
    if (n == 0)
    {
        headA = head;
    }
    else
    {
        cur->next = head;
    }

    cout << "输入链表B不一样的部分的大小 n" << std::endl;
    cin >> n;
    cout << "输入" << n << "个数字生成链表B" << std::endl;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        cur = new ListNode(x);
        if (i == 0)
        {
            headB = cur;
            last = cur;
        }
        else
        {
            last->next = cur;
            last = cur;
        }
    }
    if (n == 0)
    {
        headB = head;
    }
    else
    {
        cur->next = head;
    }

    Solution solution;

    std::cout << "链表A:" << std::endl;
    cur = headA;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;

    std::cout << "链表B:" << std::endl;
    cur = headB;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
    cur = solution.getIntersectionNode(headA, headB);

    std::cout << "计算结果指针地址:" << cur << "值:" << cur->val << std::endl;
    std::cout << "共同部分指针地址:" << head << "值:" << head->val << std::endl;

    cout << endl;
    cout << "-----结束-----" << endl;
    return 0;
}