/**
 * @file sum-lists-lcci.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-19
 * 链表求和
 * https://leetcode.cn/problems/sum-lists-lcci/
 * 
 * https://www.bilibili.com/video/BV1UB4y1S7dF?p=38
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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode *dummyhead = new ListNode(0);
        ListNode *pre = dummyhead;
        int carry = 0;
        
        while(l1!=nullptr||l2!=nullptr)
        {
            ListNode *current = new ListNode(0);
            int num = carry;
            if(l1!=nullptr)
            {
                num += l1->val;
                l1=l1->next;
            }
            if(l2!=nullptr)
            {
                num += l2->val;
                l2 = l2->next;
            }
            
            int value = num%10;
            current->val = value;
            carry = num/10;

            pre->next = current;
            pre = pre->next;
        }
        if(carry)
        {
            ListNode *current = new ListNode(carry);
            pre->next =current;
        }
        return dummyhead->next;
    }
};