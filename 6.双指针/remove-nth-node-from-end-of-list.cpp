/**
 * @file remove-nth-node-from-end-of-list.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-19
 * 删除链表中倒数第N个节点
 * - 使用双指针的方式求解
 * 首先使得两个指针相差N个位置
 * 然后同时移动
 * 当快指针为空的，时候慢指针指向要删除的位置
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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        ListNode *dummyhead = new ListNode(0, head);
        ListNode *fast = dummyhead;
        ListNode *slow = dummyhead;
        // 移动快指针，使得快慢指针相差n
        while (n-- && fast->next != NULL)
        {
            fast = fast->next;
        }

        // 同时移动快慢指针，当快指针为空的，时候慢指针指向要删除的位置
        while (fast->next != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }

        ListNode *temp = slow->next;
        slow->next = slow->next->next;
        delete temp;

        // delete dummyhead的内存
        // temp = dummyhead->next;
        // delete dummyhead;
        // return temp;

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

    Solution solution;

    std::cout << "原链表:" << std::endl;
    cur = head;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;

    cout << "输入要删除的倒数第N个节点 N" << std::endl;
    int N;
    cin >> N;
    cur = solution.removeNthFromEnd(head, N);

    std::cout << "删除第N个节点后" << N << "后链表:" << std::endl;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
    cout << "-----结束-----" << endl;
    return 0;
}