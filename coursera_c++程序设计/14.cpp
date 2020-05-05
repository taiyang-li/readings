#include<iostream>
#include<cstring>
#include<iomanip>
using namespace std;
int lifetomake[5] = {0};
const char* equip[3] = {"sword", "bomb","arrow"};
int t = 0;
const char* monname[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};

class monster
{
	public:
		int id, life;
		char* belong;
		monster(int x, int y, const char* s)
		{
			id = x;
			life = y;
			if( s)
			{
				belong = new char[strlen(s) + 1];
				strcpy(belong,s);
			}
			else
				belong = NULL;
			return;
		}
};

class dragon:public monster
{
	int equipment;
	double courage;
	public:
	dragon(int &m_, int id_, int life_,int num_, const char* s): monster(id_, life_, s)
	{
		equipment = id % 3;
		courage = double(m_)/double(lifetomake[0]);
		cout  << setw(3) << setfill('0') <<t<<" " <<belong <<" " << monname[0]<<" " << id<<" born with strength " << life <<",";
		cout << num_ <<" " << monname[0] << " in " << belong <<" headquarter" << endl;
		cout << "It has a " << equip[equipment] <<",and it's morale is " <<fixed<<setprecision(2)<< courage <<endl;
	}
};
class ninjia:public monster
{
	int equipment1, equipment2;
	public:
	ninjia(int &m_, int id_, int life_,int num_,  const char* s):monster(id_,life_,s)
	{
		equipment1 = id % 3;
		equipment2 = (id + 1) % 3;
		cout  << setw(3) << setfill('0') <<  t<<" " <<belong <<" " << monname[1] << " " << id<<" born with strength " << life <<",";
		cout << num_ <<" " << monname[1] << " in " << belong <<" headquarter" << endl;
		cout << "It has a " << equip[equipment1] <<" and a " << equip[equipment2]<<endl;
	}
};

class iceman:public monster
{
	int equipment;
	public:
	iceman(int &m_, int id_, int life_, int num_, const char*s):monster(id_,life_,s)
	{
		equipment = id % 3;
		cout  << setw(3) << setfill('0') <<  t<<" " <<belong <<" " << monname[2] <<" " << id<<" born with strength " << life <<",";
		cout << num_<<" "  << monname[2] << " in " << belong <<" headquarter" << endl;
		cout << "It has a " << equip[equipment]<<endl;
	}
};
class lion:public monster
{
	int loyalty;
	public:
	lion(int &m_,int id_,int life_, int num_, const char*s):monster(id_, life_, s)
	{
		loyalty = m_;
		cout  << setw(3) << setfill('0') <<  t<<" " <<belong <<" " << monname[3] << " " << id<<" born with strength " << life <<",";
		cout << num_<<" "  << monname[3] << " in " << belong <<" headquarter" << endl;
		cout << "It's loyalty is " << loyalty <<endl;
	}
};
class wolf:public monster
{
	public:
		wolf(int& m_, int id_, int life_, int num_, const char*s):monster(id_,life_,s)
	{
		cout  << setw(3) << setfill('0') << t<<" " <<belong <<" " << monname[4]<<" "<< id<<" born with strength " << life <<",";
		cout << num_<<" " << monname[4] << " in " << belong <<" headquarter" << endl;
	}
};

class base
{
	private:
		int m, productable[5], end, ord[5], step, num[5],sum;
		char* name;
		monster* p[100];
		friend class monster;
	public:
		base(int, int, int, int, int, int, const char*);
		void product();
		static void grow(base, base);
		void setname();
		void mon_product(int , int);
};

base::base(int a, int b, int c, int d, int e, int f, const char* g )
{
	m = f;
	sum = 0;
	step = 0;
	name = new char[strlen(g) + 1];
	strcpy(name,g);
	for(int i = 0; i < 5; i++) num[i] = 0;
	ord[0] = a;
	ord[1] = b;
	ord[2] = c;
	ord[3] = d;
	ord[4] = e;
	memset(productable, 0, sizeof(productable));
	end = 0;
	return;
}

void base::mon_product(int x, int y)
{
	switch(x)
	{
		case 0:
			p[y] = new dragon(m, sum, lifetomake[0],num[0], name);
			break;
		case 1:
			p[y] = new ninjia(m,sum,lifetomake[1],num[1], name);
			break;
		case 2:
			p[y] = new iceman(m,sum,lifetomake[2],num[2],name);
			break;
		case 3:
			p[y] = new lion(m,sum,lifetomake[3],num[3],name);
			break;
		case 4:
			p[y] = new wolf(m,sum,lifetomake[4],num[4],name);
			break;
		default:
			break;
	}
	return;
}

void base::product()
{
	if(end) return;
	if(productable[0] + productable[1] + productable[2] + productable[3] + productable[4] == 5)
	{
		cout << setw(3) << setfill('0') << t <<" " << name << " headquarter stops making warriors" << endl;
		end = 1;
		return;
	}
	if(!productable[ord[step]] && m >= lifetomake[ord[step]])
	{
		num[ord[step]]++;
		m -= lifetomake[ord[step]];
		sum++;
		mon_product(ord[step], sum);
		return;
	}
	else
	{
		productable[ord[step]] = 1;
		step = (step + 1) % 5;
		product();
		return;
	}
}

void base::grow(base a, base b)
{
	while(true)
	{
		a.product();
		a.step = (a.step + 1) % 5;
		b.product();
		b.step = (b.step + 1) % 5;
		t++;
		if(a.end + b.end == 2) break;
	}
	return;
}

int main()
{
	int n = 0;
	cin >> n;
	for(int i = 1; i <= n; i++)
	{
		t = 0;
		cout << "Case:" << i << endl;
		int tep = 0;
		cin >> tep;
		for(int j = 0; j < 5; j++)
			cin >> lifetomake[j];
		base red(2, 3, 4, 1, 0, tep, "red"), blue(3, 0, 1, 2, 4, tep, "blue");
		base::grow(red, blue);
	}
	return 0;
}
