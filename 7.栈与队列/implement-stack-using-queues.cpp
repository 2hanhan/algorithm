/**
 * @file implement-stack-using-queues.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 * 使用队列实现栈
 * https://leetcode.cn/problems/implement-stack-using-queues/
 * @copyright Copyright (c) 2022
 *
 */
#include <queue>
using namespace std;
class MyStack
{
public:
    queue<int> que1; // 用来存储元素
    queue<int> que2; // 辅助用来取到que1剩下一个

    MyStack()
    {
    }

    void push(int x)
    {
        que1.push(x);
    }

    int pop()
    {
        // que1:a b c que2:null
        // que1:c     que2:a b
        // que1和que2来回倒一下
        int size = que1.size() - 1;
        while (size--)
        {
            que2.push(que1.front());
            que1.pop();
        }

        // 取出que1剩下的那一个
        int result = que1.front();
        que1.pop();

        // 再把que2放入que1
        // que1：a b que2：null
        que1 = que2;
        while (!que2.empty())
        {
            que2.pop();
        }

        // 返回结果
        return result;
    }

    int top()
    {
        // 队列的最后一个就是栈的顶部第一个
        return que1.back();
    }

    bool empty()
    {
        return que1.empty();
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */