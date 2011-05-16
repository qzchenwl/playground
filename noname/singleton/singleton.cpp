#include <iostream>
using namespace std;
class Single
{
    public:
        static Single *getInstance();
    private:
        static Single *p;
        Single(){}
};

Single *Single::p = 0;
Single *Single::getInstance()
{
    if (p == 0)
        p = new Single;
    return p;
}

int main()
{
    Single *p = Single::getInstance();
    cout << p << endl;
    Single *p2 = Single::getInstance();
    cout << p2 << endl;
    Single *p3 = Single::getInstance();
    cout << p3 << endl;
    return 0;
}
