#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

vector<int> arr;

bool isPrime(int n)
{
    for (int i=2; i<=sqrt(n); i++)
    {
        if (n%i == 0)
            return false;
    } 
    return true;
}

int pri(int n)
{
    int c = 0;
    for (int i=2; i<n; i++)
    {
        if (n%i==0 && isPrime(i))
            c++;
    }
    return c;
}

bool compare(int i, int j)
{
    int pri_i = pri(i);
    int pri_j = pri(j);

    if (pri_i == pri_j)
        return i < j;
    else
        return pri_i < pri_j;
}

void process()
{
    for (int i=0; i<10; i++)
    {
        int tmp;
        cin >> tmp;
        arr.push_back(tmp);    
    }
    
    sort(arr.begin(), arr.end(), compare);
    cout << arr[arr.size()-1] << " " << arr[0] << endl;

    vector<int>::iterator it = arr.begin();
    arr.erase(it);
    it = arr.end() - 1;
    arr.erase(it);
}

int main()
{
    int n;
    cin >> n;

    for (int i=0; i<n; i++)
        process();

    return 0;
}
