#include <stdint.h>
#include <iostream>

using namespace std;

void setN(uint32_t& n, int p)
{
    n |= 1<<p;
}

void clrN(uint32_t& n, int p)
{
    n &= ~(1<<p);
}

void set_bit(uint32_t& n, int p, int value)
{
    if (value == 1)
    {
        setN(n, p);
    }
    else
    {
        clrN(n, p);
    }
}

int get_bit(const uint32_t& n, int p)
{
    if (n & (1<<p))
        return 1;
    else 
        return 0;
}

void process(const uint32_t& n, uint32_t& k, int i, int j)
{
    // 左边
    for (int p=31; p>j; p--)
        set_bit(k, p, 0);

    // 右边
    for (int p=0; p<i; p++)
        set_bit(k, p, 0);

    // i, j
    set_bit(k, i, get_bit(n, i));
    set_bit(k, j, 1-get_bit(n, j));

    // 中间
    for (int p=i+1; p<j; p++)
        set_bit(k, p, 1);
}

int main()
{
    int times;
    cin >> times;
    uint32_t n;
    int i, j;
    uint32_t k;
    while (times--)
    {
        cin >> n;
        cin >> i >> j;
        process(n, k, i, j);
        cout << k << endl;
    }
    return 0;
}
