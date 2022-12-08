/**
 * @file design-linked-list.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-07
 * - 3. 设计链表
 * - 增加或者删除链表的制定位置的节点时候
 * - 新增首先 newNode->next = cur->next ,然后在cur->next = newNode
 * - 删除节点 首先temp = cur->next,然后cur->next =cur->next->next并且delete temp;
 * @copyright Copyright (c) 2022
 *
 */
#include <stdlib.h>
#include <iostream>
using namespace std;

class MyLinkedList
{
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    MyLinkedList()
    {
        dummyhead = new ListNode();
        size = 0;
    }

    int get(int index)
    {
        if (index > size - 1)
            return -1;

        ListNode *cur = dummyhead->next;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val)
    {
        ListNode *newNode = new ListNode(val, dummyhead->next);
        dummyhead->next = newNode;
        size++;
    }

    void addAtTail(int val)
    {
        ListNode *cur = dummyhead;
        for (int i = 0; i < size; i++)
        {
            cur = cur->next;
        }
        ListNode *newNode = new ListNode(val);
        cur->next = newNode;
        size++;
    }

    void addAtIndex(int index, int val)
    {
        if (index < 0)
        {
            addAtHead(val);
            return;
        }

        if (index > size)
            return;

        ListNode *cur = dummyhead;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        ListNode *newNode = new ListNode(val, cur->next);
        cur->next = newNode;
        size++;
    }

    void deleteAtIndex(int index)
    {
        if (index < 0)
            return;
        if (index >= size)
            return;
        ListNode *cur = dummyhead;
        for (int i = 0; i < index; i++)
        {
            cur = cur->next;
        }
        ListNode *temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        size--;
    }

    void showAllNodeList()
    {
        ListNode *cur = dummyhead->next;
        cout << "[";
        while (cur != NULL)
        {
            cout << cur->val << " ";
            cur = cur->next;
        }
        cout << "]" << endl;
    }

private:
    int size;
    ListNode *dummyhead;
};

int main(int argc, char **argv)
{
    int val;
    int index;

    MyLinkedList *obj = new MyLinkedList();
    int param_1;

    int choice;
    while (true)
    {

        cout << "0. 退出相关程序" << endl;
        cout << "1. 获取链表index的值   get(index)" << endl;
        cout << "2. 在链表头添加值      addAtHead(val)" << endl;
        cout << "3. 在链表尾添加值      addAtTail(val)" << endl;
        cout << "4. 在链表Index处添加值 addAtIndex(index, val)" << endl;
        cout << "5. 删除链表头Index的值 deleteAtIndex(index)" << endl;
        cout << "x. 输入[数字]选择相关功能" << endl;

        cout << "原链表" << endl;
        obj->showAllNodeList();
        cin >> choice;
        switch (choice)
        {
        case 0:
            cout << "退出..." << endl;
            break;
        case 1:
            cout << "输入要获取的链表index" << std::endl;
            cin >> index;
            param_1 = obj->get(index);
            cout << index << "处值为" << param_1 << endl;
            break;
        case 2:
            cout << "输入在链表头添加值" << std::endl;
            cin >> val;
            obj->addAtHead(val);
            break;
        case 3:
            cout << "输入在链表尾添加值" << std::endl;
            cin >> val;
            obj->addAtTail(val);
            break;
        case 4:
            cout << "输入链表Index" << std::endl;
            cin >> index;
            cout << "输入添加值" << std::endl;
            cin >> val;
            obj->addAtIndex(index, val);
            break;
        case 5:
            cout << "输入要删除链表Index" << std::endl;
            cin >> index;
            obj->deleteAtIndex(index);
            break;
        default:
            break;
        }
        if (choice == 0)
            break;

        cout << "输入任意数字继续" << endl;
        cin >> choice;
        system("clear");
    }

    cout << "-----结束-----" << endl;
    return 0;
}