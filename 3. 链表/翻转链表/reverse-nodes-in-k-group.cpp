/**
 * @file reverse-nodes-in-k-group.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-19
 * K 个一组翻转链表
 * https://leetcode.cn/problems/reverse-nodes-in-k-group/
 * 讲解视频
 * https://www.bilibili.com/video/BV1UB4y1S7dF?p=37
 * @copyright Copyright (c) 2023
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

void showlist(ListNode *head)
{
    ListNode *cur = head;
    while (cur != nullptr)
    {
        cout << cur->val << " ";
        cur = cur->next;
    }
    cout << endl;
}

class Solution
{
public:
    void reverse(ListNode *start, ListNode *end)
    {
        ListNode *current = start;
        ListNode *pre = end->next;//第一个节点指向下一组的开始
        ListNode *next = nullptr;
        while (pre != end)
        {
            next = current->next;
            current->next = pre;

            pre = current;
            current = next;
        }
    }
    ListNode *reverseKGroup(ListNode *head, int k)
    {
        ListNode *prestart = new ListNode(0);
        ListNode *start = head;
        ListNode *next = nullptr;
        ListNode *current = head;

        bool gethead = true;
        int x = 0;
        while (current != nullptr)
        {
            x++;
            if (x == k)
            {
                next = current->next;
                //只在第一组时更新head
                if (gethead)
                {
                    head = current;
                    gethead = false;
                }
                reverse(start, current); // 翻转当前组
                prestart->next = current; // 上一组的start连接到当前组的end

                //当前组结束
                prestart = start; // 上一组的start
                start = next;     // 下一个start

                x = 0;
                current = next;//下一个
            }
            else
            {
                current = current->next;//下一个
            }
        }

        prestart->next = start;//最后当前组不足k时，上一组的连接到当前start
        return head;
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

    int k;
    cout << "每k个一组翻转，输入 k " << std::endl;
    cin >> k;

    Solution solution;

    std::cout << "原链表:" << std::endl;

    showlist(head);

    head = solution.reverseKGroup(head, k);

    std::cout << "相邻两两交换后链表:" << std::endl;
    showlist(head);

    cout << "-----结束-----" << endl;
    return 0;
}