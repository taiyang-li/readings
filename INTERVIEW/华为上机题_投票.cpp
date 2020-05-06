// 华为笔试题 投票并且统计结果


#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;




int main()
{
	string cmd,arg;
	vector<string> vec;
	vector<string>::iterator v_it;
	map<string,int> mymap;
	map<string ,int>::iterator it;

	int inv=0;

	while(1)
	{
		cin>>cmd;
		if(cmd == "addCandidate")
		{
			cin>>arg;
			mymap[arg]=0;
			vec.push_back(arg);
		}
		else if(cmd == "vote")
		{
			cin>>arg;
			it=mymap.find(arg);
			if(it==mymap.end())
				inv++;
			else
				mymap[arg]++;		
		}
		else if(cmd == "getVoteResult")
		{
			for ( v_it = vec.begin( ); v_it != vec.end( ); v_it++ )
				cout <<*v_it<<" "<<mymap[*v_it]<<endl;
			break;
		}
	}
	cout<<inv<<endl;
	return 0;
}
