/**
 * @file 19_02.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-04
 * 146. LRU 缓存
 * https://leetcode.cn/problems/lru-cache/
 * @copyright Copyright (c) 2023
 *
 */

#include <bits/stdc++.h>
#include <sstream>
using namespace std;

class NodeList
{
public:
    NodeList(int _key, int _value)
    {
        key = _key;
        value = _value;
        pre = nullptr;
        next = nullptr;
    }
    int key;
    int value;
    NodeList *pre;
    NodeList *next;
};

class LRUCache
{
public:
    int capacity;
    int size;
    unordered_map<int, NodeList *> LRU;
    NodeList *head;
    NodeList *tail;

    LRUCache(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    int get(int key)
    {
        if (LRU.find(key) != LRU.end())
        {
            if (head == LRU[key])
            {
                // 当前是head，删除head结点
                head = head->next;
            }
            else
            {
                if (LRU[key]->next == nullptr)
                {
                    // 当前的是tail,删除tail
                    tail = tail->pre;
                }
                else
                {
                    // 当前的不是tail，删除当前节点
                    LRU[key]->pre->next = LRU[key]->next;
                    LRU[key]->next->pre = LRU[key]->pre;
                }
            }

            if (head == nullptr)
            {
                // 如果第一个node设置head和tail
                head = LRU[key];
                tail = LRU[key];
            }
            else
            {
                // 否则直接串在tail后面，并更新tail
                LRU[key]->next = nullptr;
                LRU[key]->pre = tail;
                tail->next = LRU[key];
                tail = LRU[key];
            }
            return LRU[key]->value;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        if (LRU.find(key) != LRU.end())
        {
            LRU[key]->value = value;

            if (head == LRU[key])
            {
                // 当前是head，删除head结点
                head = head->next;
            }
            else
            {
                if (LRU[key]->next == nullptr)
                {
                    // 当前的是tail,删除tail
                    tail = tail->pre;
                }
                else
                {
                    // 当前的不是tail，删除当前节点
                    LRU[key]->pre->next = LRU[key]->next;
                    LRU[key]->next->pre = LRU[key]->pre;
                }
            }

            if (head == nullptr)
            {
                // 如果第一个node设置head和tail
                head = LRU[key];
                tail = LRU[key];
            }
            else
            {
                // 否则直接串在tail后面，并更新tail
                LRU[key]->next = nullptr;
                LRU[key]->pre = tail;
                tail->next = LRU[key];
                tail = LRU[key];
            }
        }
        else
        {
            size++;
            NodeList *cur = new NodeList(key, value);
            if (head == nullptr)
            {
                // 如果第一个node设置head和tail
                head = cur;
                tail = cur;
            }
            else
            {
                // 否则直接串在tail后面，并更新tail
                cur->next = nullptr;
                cur->pre = tail;
                tail->next = cur;
                tail = cur;
            }

            LRU[key] = cur;

            if (size > capacity)
            {
                NodeList *delete_node = head;
                head = head->next;

                LRU.erase(delete_node->key);
                delete delete_node;
                size--;
            }
        }
    }
};

class LRUCache
{
public:
    int capacity;
    int size;
    unordered_map<int, NodeList *> LRU;
    NodeList *head;
    NodeList *tail;

    LRUCache(int capacity)
    {
        this->capacity = capacity;
        size = 0;
        head = nullptr;
        tail = nullptr;
    }

    int get(int key)
    {
        if (LRU.find(key) != LRU.end())
        {
            if (head == LRU[key])
            {
                // 当前是head，删除head结点
                head = head->next;
            }
            else
            {
                if (LRU[key]->next == nullptr)
                {
                    // 当前的是tail,删除tail
                    tail = tail->pre;
                }
                else
                {
                    // 当前的不是tail，删除当前节点
                    LRU[key]->pre->next = LRU[key]->next;
                    LRU[key]->next->pre = LRU[key]->pre;
                }
            }

            if (head == nullptr)
            {
                // 如果第一个node设置head和tail
                head = LRU[key];
                tail = LRU[key];
            }
            else
            {
                // 否则直接串在tail后面，并更新tail
                LRU[key]->next = nullptr;
                LRU[key]->pre = tail;
                
                tail->next = LRU[key];
                tail = LRU[key];
            }
            return LRU[key]->value;
        }
        else
        {
            return -1;
        }
    }

    void put(int key, int value)
    {
        if (LRU.find(key) != LRU.end())
        {
            LRU[key]->value = value;
            get(key);
        }
        else
        {
            size++;
            NodeList *cur = new NodeList(key, value);
            LRU[key] = cur;

            if (head == nullptr)
            {
                // 如果第一个node设置head和tail
                head = cur;
                tail = cur;
            }
            else
            {
                // 否则直接串在tail后面，并更新tail
                cur->next = nullptr;
                cur->pre = tail;
                tail->next = cur;
                tail = cur;
            }

            if (size > capacity)
            {
                NodeList *delete_node = head;
                head = head->next;

                LRU.erase(delete_node->key);
                delete delete_node;
                size--;
            }
        }
    }
};

int main()
{
    // 10
    // LRUCache lRUCache(2);
    // lRUCache.get(2);
    // lRUCache.put(2, 6);
    // lRUCache.get(1);
    // lRUCache.put(1, 5);
    // lRUCache.put(1, 2);
    // lRUCache.get(1);
    // lRUCache.get(2);

    // 11
    // LRUCache lRUCache(2);
    // lRUCache.put(2, 1);
    // lRUCache.put(3, 2);
    // lRUCache.get(3);
    // lRUCache.get(2);
    // lRUCache.put(4, 3);
    // lRUCache.get(2);
    // lRUCache.get(3);
    // lRUCache.get(4);

    return 0;
}