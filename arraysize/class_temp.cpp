#include <iostream>

using namespace std;

template <typename T>
class Base
{
    public:
        virtual void print() { cout << "Base::print()" << endl; }
};

template <typename T>
class Derived: public Base<T>
{
    public:
        virtual void print() { cout << "Base::print()" << endl; }
};

template <typename T>
void func(const Base<T> &b) { b.print(); }

int main()
{
    Derived<int> d;
    func(d);
    return 0;
}
