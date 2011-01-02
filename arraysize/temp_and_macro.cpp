#include <iostream>
#include <vector>
using namespace std;

class A
{
    public:
        int x;
        double y;
        vector<int> z;
};

// using c++ template
template<class T, int N>
char( &len_byte( T(&)[N] ) )[N];
#define arr_len_1(_array) (sizeof(len_byte(_array))/sizeof(char))

// using c macro
#define arr_len_2(_array) (sizeof(_array)/sizeof(_array[0]))

void comp_length(int (&arr) [10])
{
    cout << "arr_len_1(arr) = " << arr_len_1(arr) << endl;
    cout << "arr_len_2(arr) = " << arr_len_2(arr) << endl;
}

int main()
{
    A a[20];
    int b[10];
    cout<<"arr_len_1(a)="<<arr_len_1(a)<<endl;
    cout<<"arr_len_2(a)="<<arr_len_2(a)<<endl;
    cout<<"arr_len_1(b)="<<arr_len_1(b)<<endl;
    cout<<"arr_len_2(b)="<<arr_len_2(b)<<endl;

    //compute array length in function comp_length
    comp_length(b);
    return 0;
}
