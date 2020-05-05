#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
using namespace std;
#define MAX 99999999

class Headquarter;
class Sumurai;     //������

int M = 0;      //M��ʼ����Ԫ
int gametime;   //��Ϸʱ��

int key0,key1;  //���������־��0Ϊ�죬1Ϊ��

int Num[2];     //��˾���ʿ������0Ϊ�죬1Ϊ��
int Next[2];    //��¼��һ��Ҫ�������ʿ��order�е�λ�ã�0Ϊ�죬1Ϊ��

int order[2][5]={{2,3,4,1,0},{3,0,1,2,4}}; //dragon��ninja��iceman��lion��wolf�ֱ���0~4����

int original_elem[5]={0,0,0,0,0}; //��¼ÿ����ʿ������Ԫ

char name[5][7] = {"dragon","ninja","iceman","lion","wolf"}; //��ʿ����

char headname[2][5]={"red","blue"}; //��Ӫ����

Headquarter* head[2];    //ָ����˾���0Ϊ�죬1Ϊ��
Sumurai* sumu[2][1000];  //��ʿ�ļ�¼��0Ϊ�죬1Ϊ��

class Headquarter{
	public:
		int elem; //ʣ������Ԫ
		int color; //�����ĸ���Ӫ����Ϊ0����Ϊ1
		int count[5]; //ÿ����ʿ������

		Headquarter(int a){
			elem = M;
			color = a;
			memset(count,0,sizeof(count));
		}//���캯����ʼ��

		bool GiveBirth() //������ʿ
		{

			int sort = order[color][Next[color]%5]; //��ǰӦ�������ʿ����
			if(elem - original_elem[sort] >= 0 )
			{
				elem -= original_elem[sort]; //�۳�����Ԫ������ʿ
				count[sort]++;

				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);

				Num[color]++;
				Next[color]++;
				return true;
			}

			else if(elem >= original_elem[order[color][(Next[color]+1) % 5]]){
				sort = order[color][(Next[color]+1)%5];
				elem -= original_elem[sort]; //�۳�����Ԫ������ʿ
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 2;
				return true;
			}
			else if(elem >= original_elem[order[color][(Next[color]+2)%5]]){
				sort = order[color][(Next[color]+2)%5];
				elem -= original_elem[sort]; //�۳�����Ԫ������ʿ
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 3;
				return true;
			}
			else if(elem >= original_elem[order[color][(Next[color]+3)%5]]){
				sort = order[color][(Next[color]+3)%5];
				elem -= original_elem[sort]; //�۳�����Ԫ������ʿ
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 4;
				return true;
			}
			else if(elem >= original_elem[order[color][(Next[color]+4)%5]]){
				sort = order[color][(Next[color]+4)%5];
				elem -= original_elem[sort]; //�۳�����Ԫ������ʿ
				count[sort]++;
				printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n",
						gametime/60,headname[color],name[sort],Num[color],original_elem[sort], count[sort],name[sort],headname[color]);
				Num[color]++;
				Next[color] += 5;
				return true;
			}

			else return false;
		}

};//˾���

class Sumurai
{

};//��ʿ��


int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("myout.txt","w",stdout);

	int test,i_test;
	cin>>test;
	for(i_test=1; i_test<=test; i_test++)
	{
		Num[0] = Num[1] = 1;   //��˾���ʿ��������
		key0 = key1 = 0;       //������־����
		Next[0] = Next[1] = 0; //Ҫ�������ʿ��order�е�λ������

		cin>>M;//�����ʼ����Ԫ

		for(int i=0;i<5;i++)
			cin>>original_elem[i]; //����ÿ����ʿ������Ԫ

		head[0] = new Headquarter(0); //������˾�
		head[1] = new Headquarter(1); //������˾�

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
