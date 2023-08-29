#include <iostream>
using namespace std;

class Base
{
public:
    int base_public = 0;
    void BaseShow_public()
    {
        std::cout << "BaseShow_public()" << std::endl;
    }

protected:
    int base_protect = 1;
    void BaseShow_protected()
    {
        std::cout << "BaseShow_protected()" << std::endl;
    }

private:
    int private_public = 2;
    void BaseShow_private()
    {
        std::cout << "BaseShow_private()" << std::endl;
    }
};

class Derived_public : public Base
{
public:
    void DerivedShow()
    {
        cout << "Derived_public" << endl;
        cout << "base_public: " << base_public << endl;
        cout << "base_protect: " << base_protect << endl;
        // cout << "private_public: " << private_public << endl;

        BaseShow_public();
        BaseShow_protected();
        // BaseShow_private(); // error
    }
};

class Derived_protected : protected Base
{
public:
    void DerivedShow()
    {
        cout << "Derived_protected" << endl;
        cout << "base_public: " << base_public << endl;
        cout << "base_protect: " << base_protect << endl;
        // cout << "private_public: " << private_public << endl;

        BaseShow_public();
        BaseShow_protected();
        // BaseShow_private(); // error
    }
};

class Derived_private : private Base
{
public:
    void DerivedShow()
    {
        cout << "Derived_private" << endl;
        cout << "base_public: " << base_public << endl;
        cout << "base_protect: " << base_protect << endl;
        // cout << "private_public: " << private_public << endl;

        BaseShow_public();
        BaseShow_protected();
        // BaseShow_private(); // error
    }
};

// 测试public、protect、private继承
void test01()
{
    Derived_public d_public;
    d_public.DerivedShow();
    d_public.BaseShow_public();

    Base b;
    // b.BaseShow_protected(); //! 报错

    cout << endl;
    cout << endl;

    Derived_protected d_proctected;
    d_proctected.DerivedShow();
    // d_proctected.BaseShow_public();

    cout << endl;
    cout << endl;

    Derived_private d_private;
    d_private.DerivedShow();
}

class A
{
public:
    A()
    {
        cout << "A()构造函数" << endl;
    }

    ~A()
    {
        cout << "~A()析构函数" << endl;
    }
};

class B
{
public:
    B()
    {
        cout << "B()构造函数" << endl;
    }

    ~B()
    {
        cout << "~B()析构函数" << endl;
    }
};

class C
{
public:
    C()
    {
        cout << "C()构造函数" << endl;
    }

    ~C()
    {
        cout << "~C()析构函数" << endl;
    }
};

class D
{
public:
    D()
    {
        cout << "D()构造函数" << endl;
    }

    ~D()
    {
        cout << "~D()析构函数" << endl;
    }
};

class E : public A, public B
{
public:
    E()
    {
        cout << "E()构造函数" << endl;
    }

    ~E()
    {
        cout << "~E()析构函数" << endl;
    }
    C c;
    D d;
};

// 测试构造和析构顺序
void test02()
{
    E e;
}

int main()
{
    test02();
    return 0;
}