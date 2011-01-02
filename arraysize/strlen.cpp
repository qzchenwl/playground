#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int main()
{
    char str1[] = "c:\\user\\1\\1.txt";
    string str2 = "c:\\user\\1\\1.txt";
    cout << "strlen(str1) = " << strlen(str1) << endl;
    cout << "str2.length() = " << str2.length() << endl;
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
    cout << " ==================================== " << endl;

    char a[20] = "c:\\user\\1\\1.txt";
    for(int i = strlen(a) - 1; i >= 0; --i) {
        cout << "a[" << i << "] = " << a[i] << endl;
        if(a[i] == '\\') {
            a[i+1] = '\0';
            break;
        }
        cout << "a[" << i << "] = " << a[i] << endl;
    }
    cout << "strlen: " << a << endl;

    string aa = "c:\\user\\1\\1.txt";
    for(int i = aa.length() - 1; i >= 0; --i) {
        cout << "aa[" << i << "] = " << aa[i] << endl;
        if(aa[i] == '\\') {
            aa[i+1] = '\0';
            break;
        }
        cout << "aa[" << i << "] = " << aa[i] << endl;
    }
    cout << "string.length(): " << aa << endl;

    cout << " =================================== " << endl;
    string str = "abcdefghijk";
    cout << "str = " << str << endl;
    str[2] = 'x';
    str[3] = '\0';
    cout << "str = " << str << endl;

    return 0;
}
