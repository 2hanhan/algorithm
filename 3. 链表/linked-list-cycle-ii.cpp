/**
 * @file linked-list-cycle-ii.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-20
 * - 3.8 环形链表II
 * - |---X---|---Y---|---Z---| 循环入口 X ；链表循环为一圈为 Y + Z；  相遇节点位置为 X + Y；
 * - 使用双指针的方式求解
 * step 1 求fast slow相遇节点 X + Y
 *  fast 每次移动2节点 快慢指针相遇时总移动距离 X + n * (Y + Z) 快指针循环圈数n； n >= 1；
 *  slow 每次移动1节点 快慢指针相遇时总移动距离 X + Y  慢指针走不满一圈必定被快指针追上
 * 根据移动速度可得 2 * (X + Y) = X + n * (Y + Z) 【公式一】fast在slow进入一圈之内与slow相遇
 * 根据【公式一】可以获得fast slow 相遇节点【X + Y】
 * step 2 新的两个指针同时移动求入口节点 X
 * 化简得的循环入口 X = (n - 1) * (Y + Z) + Z【公式二】在循环入口【X】节点处相遇
 * 【公式二】左边：从head开始移动到相遇循环开始位置【X】
 * 【公式二】右边：从fast、slow相遇位置【X + Y】开始移动一定圈数 + Z
 *  根据【公式二】可以获得相遇节点【X】为循环入口节点
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
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast = head;
        ListNode *slow = head;

        // step 1 求fast slow相遇节点 X + Y
        while (fast != NULL && fast->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow)
            {
                // step 2 新的两个指针同时移动求入口节点 X
                slow = head;
                // slow 从head开始
                // fast 从【X+Y】开始
                while (fast != slow)
                {
                    fast = fast->next;
                    slow = slow->next;
                }
                return fast;
            }
        }
        return NULL; // 没有循环
    }
};

int main(int argc, char **argv)
{
    int n;
    cout << "输入链表大小 n" << std::endl;
    cin >> n;

    ListNode *head;
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

    cout << "输入链表循环入口 n(编号从0开始)" << std::endl;
    cin >> n;
    cur = head;
    for (int i = 0; i < n; i++)
    {
        cur = cur->next;
    }
    last->next = cur;

    Solution solution;

    std::cout << "链表:" << std::endl;
    cur = head;
    int maxlen = 20;
    int it = 0;
    while (cur != NULL)
    {
        cout << cur->val << " ";
        cur = cur->next;
        if (it++ > maxlen)
            break;
    }
    cout << endl;

    cur = solution.detectCycle(head);
    std::cout << "计算结果指针地址:" << cur << "值:" << cur->val << std::endl;

    cout << endl;
    cout << "-----结束-----" << endl;
    return 0;
}