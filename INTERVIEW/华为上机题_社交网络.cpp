#include<iostream>
#include<string>
#include<map>
using namespace std;

bool candidate(bool arr[][105],int m,int id1, int id2, int p)
{
	int i,count=0;
	for(i=0;i<m;i++)
	{
		if(arr[i][id1] && arr[i][id2])
			count++;
	}
	if(count > p) 
		return true;
	return false;
}

void updateFri(bool arr[][105],int m,int p)
{
	bool UPDATE = true;
	int i,j;
	while(UPDATE)
	{
		UPDATE = false;
		for(i=0;i<m;i++)
		{
			for(j=i+1;j<m;j++)
			{
				if(arr[i][j]) continue;
				if(candidate(arr,m,i,j,p))
				{
					arr[i][j]=true;
					arr[j][i]=true;
					UPDATE = true;
				}
			}
		}
	}
}

int getFirendNum(bool arr[][105],int m,int id)
{
	int i,count=0;
	for(i=0;i<m;i++)
	{
		if(arr[i][id] )
			count++;
	}
	return count;
}

int main()
{
	int i,j;
	int P,m,M,n,N;

	string name,name1;
	map<string ,int>::iterator it;
	map<string,int> ID;
	bool friendship[105][105];

	cin>>P>>m>>M>>n>>N;

	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
			friendship[i][j]=false;
	}

	for(i=0;i<m;i++)
	{
		cin>>name;
		ID[name] = i;
	}
	for(i=0;i<M;i++)
	{
		cin>>name>>name1;
		friendship[ID[name]][ID[name1]]=true;
		friendship[ID[name1]][ID[name]]=true;
	}

	updateFri(friendship,m,P);

	for(i=0;i<n;i++)
	{
		cin>>name;
		it = ID.find(name);
		if(it != ID.end())
			cout<<getFirendNum(friendship,m,ID[name])<<endl;
		else
			cout<<-1<<endl;
	}
	for(i=0;i<N;i++)
	{
		cin>>name>>name1;
		if(friendship[ID[name]][ID[name1]])
			cout<<0<<endl;
		else
			cout<<-1<<endl;
	}
	return 0;
}