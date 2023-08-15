/**
 * @file merge-two-sorted-lists.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-19
 * 合并两个有序链表
 * https://leetcode.cn/problems/merge-two-sorted-lists/
 * 
 * https://www.bilibili.com/video/BV1UB4y1S7dF?p=39
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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) 
    {
        // 特殊情况有为空的直接返回
        if(list1==nullptr||list2==nullptr)
        {
            return list1==nullptr? list2:list1;
        }

        // 进行拼接，pre->next取小的那一个
        ListNode *head = list1->val>list2->val?list2:list1;
        ListNode *p1 = head->next;
        ListNode *p2 = head == list1?list2:list1;
        ListNode * pre = head;

        while(p1!=nullptr&&p2!=nullptr)
        {
            if(p1->val<p2->val)
            {
                pre->next = p1;
                p1=p1->next;
            }
            else
            {
                pre->next = p2;
                p2=p2->next;
            }
            pre = pre->next;
        }
        //有一个用完了，则nxet指向没用完的那一个
        pre->next = p1==nullptr? p2:p1;
        return head;
        
    }
};