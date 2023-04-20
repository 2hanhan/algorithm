/**
 * @file copy-list-with-random-pointer.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-20
 * 复制带随机指针的链表
 * https://leetcode.cn/problems/copy-list-with-random-pointer/
 *
 * https://www.bilibili.com/video/BV1UB4y1S7dF?p=45
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <unordered_map>
using namespace std;

// Definition for a Node.
class Node
{
public:
    int val;
    Node *next;
    Node *random;

    Node(int _val)
    {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

// 使用unordered_map查找新的老的对于关系，来连接next和random指针
class Solution1
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
            return nullptr;

        unordered_map<Node *, Node *> myMap;
        Node *cur = head;
        while (cur != nullptr)
        {
            Node *newCur = new Node(cur->val);
            myMap[cur] = newCur;
            cur = cur->next;
        }

        Node *newHead = myMap[head]; // 新head节点
        cur = head;
        while (cur != nullptr) // 拷贝next和random
        {
            Node *newCur = myMap[cur];
            newCur->next = myMap[cur->next];//即使next为空，这玩意会默认创建对应的<nullptr,nullptr>
            newCur->random = myMap[cur->random];//即使random为空，这玩意会默认创建对应的<nullptr,nullptr>
            cur = cur->next;
        }
        return newHead;
    }
};

//串在后面
class Solution2
{
public:
    Node *copyRandomList(Node *head)
    {
        if (head == nullptr)
            return nullptr;

        Node *cur = head;
        // 把copy的插入到原来的后一个
        while (cur != nullptr)
        {
            Node *newCur = new Node(cur->val);
            newCur->next = cur->next;
            cur->next = newCur;
            cur = newCur->next;
        }
        // 复制random
        cur = head;

        while (cur != nullptr)
        {
            Node *newCur = cur->next;
            if (cur->random != nullptr)
                newCur->random = cur->random->next; // random 指向copy
            cur = newCur->next;
        }
        // 分离原来的和copy的
        Node *newHead = head->next;
        cur = head;
        while (cur != nullptr)
        {
            Node *newCur = cur->next;
            cur->next = newCur->next;
            cur = cur->next;
            if (cur != nullptr)
                newCur->next = cur->next;
        }
        return newHead;
    }
};