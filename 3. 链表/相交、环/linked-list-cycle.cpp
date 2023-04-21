/**
 * @file linked-list-cycle.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * https://leetcode.cn/problems/linked-list-cycle/submissions/
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


class Solution {
public:
    bool hasCycle(ListNode *head) {
        if(head==nullptr||head->next==nullptr)
            return false;
        ListNode *p1 = head->next;
        ListNode *p2 = head->next->next;
        while(p2!=nullptr&&p2->next!=nullptr)
        {
            if(p1==p2)
                return true;
            p1 = p1->next;
            p2 = p2->next->next;

        }
        return false;
        
    }
};

