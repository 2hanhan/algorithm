/**
 * @file implement-queue-using-stacks.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-12-28
 * 用栈实现队列
 * @copyright Copyright (c) 2022
 *
 */
#include <stack>
using namespace std;

class MyQueue
{
public:
    stack<int> stIn;
    stack<int> stOut;

    MyQueue()
    {
    }

    // 从队列尾部加入元素
    void push(int x)
    {
        stIn.push(x);
    }

    // 从队列首移除元素
    int pop()
    {
        // 从stIn倒出来放入stOut
        if (stOut.empty())
        {
            while (!stIn.empty())
            {
                stOut.push(stIn.top());
                stIn.pop();
            }
        }

        int result = stOut.top();
        stOut.pop();
        return result;
    }

    // 返回队列首部的元素
    int peek()
    {
        int res = this->pop(); // 弹出stOut的第一个
        stOut.push(res);       // 完事在放回stOut
        return res;
    }

    // 返回队列是否为空
    bool empty()
    {
        // stIn和stOut都为空则队列为空
        return stIn.empty() && stOut.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */