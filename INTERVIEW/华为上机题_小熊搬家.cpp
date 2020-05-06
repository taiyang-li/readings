#include<iostream>
#include<queue>
using namespace std;

struct Point
{
	int x;
	int y;
};

// 判断是否超界
inline bool cheakPoint(Point p, int X, int Y)
{
	if(p.x>=X || p.x<0 || p.y>=Y || p.y<0)
		return false;
	return true;
}

int main()
{
	bool FIND = false;
	Point shift[4] = {{1,0},{-1,0},{0,1},{0,-1}};
	int i,j;
	char** map;    // 注意这种写法
	int ** map_flag;
	int R,C;
	queue<Point> que;
	Point b,temp,p;

	cin>>R>>C;

	map = new char *[R];
	map_flag = new int *[R];
	for(i=0; i<R; i++)
	{
		map[i] = new char[C];
		map_flag[i] = new int[C];
	}
	for(i=0;i<R;i++)
	{
		for(j=0;j<C;j++)
		{
			cin>>map[i][j];
			map_flag[i][j]=0;

			if(map[i][j] == 'B')
			{
				b.x=j;
				b.y=i;
			}
		}
	}

	que.push(b);
	map_flag[b.y][b.x] = 1;

	while(!que.empty())
	{
		temp = que.front();
		que.pop();
	
		if(map[temp.y][temp.x]=='H')
		{
			cout<<"Y"<<endl;
			FIND = true;
			break;
		}

		for(i=0;i<4;i++)
		{
			p.x = temp.x + shift[i].x;
			p.y = temp.y + shift[i].y;
			if( cheakPoint(p, C, R) && map_flag[p.y][p.x]==0 && (map[p.y][p.x]=='-' || map[p.y][p.x]=='H'))
			{
				map_flag[p.y][p.x]=1;
				que.push(p);
			}
		}
	}

	if(!FIND)
		cout<<"N"<<endl;

	for(i=0; i<R; i++)
	{
		delete [] map[i];
		delete [] map_flag[i];
	}
	delete [] map;
	delete [] map_flag;
	return 0;
}
