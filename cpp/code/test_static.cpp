#include <bits/stdc++.h>

using namespace std;

class A
{
    static int value_a;
    int value_b;
    static int get_value()
    {
        // value_b = 1; //! 报错
        return value_a;
    }
};

int A::value_a = 0;

int main()
{
    return 0;
}