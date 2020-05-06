#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void dealing(int r,int c,int m)
{
	if(m>0 &&((r==1 || c==1) && 2+m > r*c) ||( r>1 && c>1 && 4+m > r*c))
	{
		cout<<"Impossible"<<endl;
		return;
	}
	
	vector<string> result(r,string(c,'.'));
	result[0][0] ='c';
	int len = 0;
	for(int i=r-1;i>=0 && m>0;i--)
	{
		if(i>1)
		{
			len = min(c,m);
			result[i].replace(max(0,c-m),len,string(len,'*'));
			m -= len;
		}
		else
		{
			len = min(c-2,m);
			result[i].replace(max(2,c-m),len,string(len,'*'));
			m -= len;
		}
		
	}
	for(int i=0;i<r;i++)
	{
		cout<<result[i]<<endl;
	}
	
}
int main()
{
	int t,r,c,m;
	cin>>t;
	for(int i=1;i<=t;i++)
	{
		cin>>r>>c>>m;
		cout<<"Case #"<<i<<":"<<endl;
		dealing(r,c,m);
	}
	return 0;
}
