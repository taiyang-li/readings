#include <iostream>
#include <stdio.h>
using namespace std;
#define FIND(struc,e) (size_t)&(((struc*)0)-> e)
struct student
{
    int a;
    char b[20];
    double ccc;
};
int main()
{
    cout<<"struct size:"<<sizeof(student)<<endl;
    size_t num1 = FIND(student, a);
    size_t num2 = FIND(student, b);
    size_t num3 = FIND(student, ccc);
    cout<<num1<<"  "<<num2<<"  "<<num3<<endl;
    return 0;
}
