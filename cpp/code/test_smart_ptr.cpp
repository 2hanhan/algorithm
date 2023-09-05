#include <bits/stdc++.h>

using namespace std;

// 测试unique_ptr
void test01()
{
    unique_ptr<string> p1(new string("test01"));
    unique_ptr<string> p2;
    // p2 = p1; //! 报错
}

// 测试 weak_ptr 和 shared_ptr
class A
{
public:
    A() : a(3) { cout << "A Constructor..." << endl; }
    ~A() { cout << "A Destructor..." << endl; }

    int a;
};

void test02()
{
    weak_ptr<A> wp;

    {
        shared_ptr<A> sp(new A());
        cout << "初始化sp后 sp.use_count():" << sp.use_count() << endl;

        wp = sp;
        cout << "弱wp = sp后 sp.use_count():" << sp.use_count() << endl;
        cout << "弱wp = sp后 wp.use_count():" << wp.use_count() << endl;

        if (shared_ptr<A> pa = wp.lock())
        {
            cout << "wp指向对象非空,pa->a " << pa->a << endl;
        }
        else
        {
            cout << "wp指向对象为空" << endl;
        }
        shared_ptr<A> sp1 = sp;
        cout << "新的sp1 = sp后 sp.use_count():" << sp.use_count() << endl;
    }

    if (!wp.expired())
    {
        cout << "wp指向对象未被释放" << endl;
    }
    else
    {
        cout << "wp指向对象已经释放" << endl;
    }
}

// 测试 weak_ptr的解除循环引用
class W_B;
class W_A
{
public:
    W_A()
    {
        cout << "W_A()" << endl;
    }
    ~W_A()
    {
        cout << "~W_A()" << endl;
    }
    shared_ptr<W_B> B_ptr;
};
class W_B
{
public:
    W_B()
    {
        cout << "W_B()" << endl;
    }
    ~W_B()
    {
        cout << "~W_B()" << endl;
    }
    weak_ptr<W_A> A_ptr;
};

shared_ptr<W_B> build_A_and_B()
{
    shared_ptr<W_A> s_a(new W_A());
    shared_ptr<W_B> s_b(new W_B());
    s_a->B_ptr = s_b;
    s_b->A_ptr = s_a;
    return s_b;
}

void test03()
{
    cout << "test03()开始" << endl;
    shared_ptr<W_B> B_ptr = build_A_and_B(); // 这个样子A不就直接被释放了吗？
    cout << "test03()结束" << endl;
}

int main()
{
    // test01();
    test02();
    // test03();
    return 0;
}