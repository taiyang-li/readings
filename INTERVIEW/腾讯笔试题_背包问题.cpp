#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <sstream>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <iostream>
#include <sstream>


using namespace std;

const int maxsize=100;
int n,S;
bool visit[maxsize];
int w[maxsize];
int q[maxsize];
int beibao()
{
    int top=-1,begin=0,sum=0;
    int i;
    while(top!=-2)
    {
        for(i=begin;i<n;i++)
        {
            if(!visit[i] && w[i]+sum<=S)
            {
                sum+=w[i];
                q[++top]=i;
                begin=0;
                visit[i]=1;
                if(sum==S) return top;
                break;
            }
        }
        if(i==n)
        {
            visit[q[top]]=0;
            sum-=w[q[top]];
            begin=q[top]+1;
            top--;
        }
    }
}
int main()
{
    cin>>n>>S;
    for(int i=0;i<n;i++)
    {
        cin>>w[i];
        visit[i]=0;
    }
    int t=beibao();
    if(t!=-1)
    {
        for(int i=0;i<=t;i++)
            cout<<w[q[i]]<<" ";
        cout<<endl;
    }
    else cout<<-1<<endl;
	system("pause");
}

