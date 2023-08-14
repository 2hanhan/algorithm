# LeetCode中C++一些Bug
1. 定义有返回值的函数，if情况及时穷举了所有情况并且return，只要没写else就会给你报错没有返回值。
比如即使调用时候x只给了1，2，3的数值
```c++
int fun(int x)
{
    if(x == 1)
    {
        return 1;
    }
    if(x == 2)
    {
        return 1;
    }
    if( x== 3)
    {
        return 1;
    }
}
```
2. delete释放内存，只有delete为root根节点就会出错。