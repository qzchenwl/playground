#include <iostream>
using namespace std;
int main()
{
    char *p = new char[500*500*1000];
    p[500*500*1000 - 1] = '\0';
    p[500*500*1000 - 2] = 'h';
    for(int i = 0; i < 500*500*1000 - 2; ++i) {
        p[i] = '0';
    }
    cout << "hi" << endl;
    cout << p << endl;
    return 0;
}
