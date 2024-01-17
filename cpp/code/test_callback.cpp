#include <iostream>
using namespace std;

void fun1(int x, int y)
{
    cout << "fun1: x:" << x << " y:" << y << endl;
}

void fun2(int x, int y)
{
    cout << "fun2: x:" << x << " y:" << y << endl;
}

void funx(int x, int y, void(*fun_ptr)(int,int))
{
    fun_ptr(x, y); // 调用回调函数
}

int main()
{
    funx(9, 9, fun1);
    funx(9, 9, fun2);

    return 0;
}