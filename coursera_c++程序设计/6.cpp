#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define MAX 99999999

class Headquarter;
class Sumurai;     //声明类

int M = 0;      //M初始生命元
int gametime;   //游戏时间

int key0,key1;  //制造结束标志，0为红，1为蓝

int Num[2];     //各司令部武士数量，0为红，1为蓝
int Next[2];    //记录下一个要建造的武士在order中的位置，0为红，1为蓝

int order[2][5]={{2,3,4,1,0},{3,0,1,2,4}}; //dragon、ninja、iceman、lion、wolf分别用0~4代替

int original_elem[5]={0,0,0,0,0}; //记录每种武士的生命元

char name[5][7] = {"dragon","ninja","iceman","lion","wolf"}; //武士名称

char headname[2][5]={"red","blue"}; //阵营名称

Headquarter* head[2];    //指向两司令部，0为红，1为蓝
Sumurai* sumu[2][1000];  //武士的记录，0为红，1为蓝

class Headquarter{
	public:
		int elem; //剩余生命元
		int color; //属于哪个阵营，红为0，蓝为1
		int count[5]; //每种武士的数量

		Headquarter(int a){
			elem = M;
			color = a;
			memset(count,0,sizeof(count));
		}//构造函数初始化

		bool GiveBirth() //制造武士
		{

			int sort = order[color][Next[color]%5]; //当前应制造的武士类型
			if(elem - original_elem[sort] >= 0 )
			{
				elem -= original_elem[sort]; //扣除生命元制造武士
				count[sort]++;

				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);

				Num[color]++;
				Next[color]++;
				return true;
			}

			else if(elem >= original_elem[order[color][(Next[color]+1) % 5]]){
				sort = order[color][(Next[color]+1)%5];
				elem -= original_elem[sort]; //扣除生命元制造武士
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 2;
				return true;
			}
			else if(elem >= original_elem[order[color][(Next[color]+2)%5]]){
				sort = order[color][(Next[color]+2)%5];
				elem -= original_elem[sort]; //扣除生命元制造武士
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 3;
				return true;
			}
			else if(elem >= original_elem[order[color][(Next[color]+3)%5]]){
				sort = order[color][(Next[color]+3)%5];
				elem -= original_elem[sort]; //扣除生命元制造武士
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 4;
				return true;
			}
			else if(elem >= original_elem[order[color][(Next[color]+4)%5]]){
				sort = order[color][(Next[color]+4)%5];
				elem -= original_elem[sort]; //扣除生命元制造武士
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 5;
				return true;
			}

			else return false;
		}

};//司令部类

class Sumurai
{

};//武士类


int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("myout.txt","w",stdout);

	int test,i_test;
	cin>>test;
	for(i_test=1; i_test<=test; i_test++)
	{
		Num[0] = Num[1] = 1;   //各司令部武士数量置零
		key0 = key1 = 0;       //结束标志置零
		Next[0] = Next[1] = 0; //要建造的武士在order中的位置置零

		cin>>M;//读入初始生命元

		for(int i=0;i<5;i++)
			cin>>original_elem[i]; //读入每种武士的生命元

		head[0] = new Headquarter(0); //产生红司令部
		head[1] = new Headquarter(1); //产生蓝司令部

		printf("Case:%d\n",i_test);

		for(gametime = 0; key0==0 || key1==0; gametime++)
		{
			if(gametime % 60 == 0)
			{
				if(head[0]->GiveBirth() == false){
					if(key0 == 0)
						printf("%03d red headquarter stops making warriors\n",gametime/60);
					key0 = 1;
				}

				if(head[1]->GiveBirth() == false){
					if(key1 == 0)
						printf("%03d blue headquarter stops making warriors\n",gametime/60);
					key1 = 1;
				}
			}
		}
	}
	//system("pause");
	return 0;
}
