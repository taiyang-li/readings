#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <stdlib.h>
#include <stdio.h>

// 参考文献： 编程之美  p101

using namespace std;

typedef unsigned char uchar;  
typedef pair<string, pair>  OP_RES         // 记录数值的类型 
typedef set<pair<string, pair>> OP_RES_SET  // 数值集合 

enum OP {ADD=0, SUB, MUL, DIV};


const int N = 4;				// 卡牌张数 
const int MAX_IDX = (int)pow(float(2), float(N))-1;   // 对应卡牌组合 {a0 a1 a2 a3}
vector<OP_RES_SET> S(MAX_IDX+1);    // 所有卡牌组合内部进行+ - * /运算的结果及其相应的运算过程


// 计算四张卡牌内部进行+ - * / 运算得到的所有结果, 即 S[MAX_ID]
void game24(int card[]);              

// 函数功能：输出该卡牌组合内部+ - * /得到的结果
// 例如：
// 输入：i=3;  对应卡牌组合为{a0, a1}  假设a0=10; a1=5; 
// 则输出为： {('(10+5)', 15), ('(10-5)', 5), ('(10*5)', 50), ('(10/5)', 2)}
OP_RES_SET f(int i);     

// 函数功能：输入集合A 和 集合B, 输出A B 之间加减乘除的所有结果
// 例如: 
// 输入： A = {('10', 10)}   
//        B = {('(3+1)', 4), ('3-1', 2)}
// 输出： C = {('(10+(3+1))', 14), ('(10-(3+1))', 6), ..., ('(10/(3-1))', 5)}
OP_RES_SET Fork(OP_RES_SET &s1, OP_RES_SET &s2); 

// 函数功能：计算一对数值进行加减乘除运算得到的结果，并记录运算过程 
// op=0: 加法  op=1: 减法
// op=2: 乘法  op=3: 除法
// 例如:
// 输入： e1 = ('(3-1)', 2)  e2 = ('3*3', 9)  op = 1
// 输出： ('(3-1)+(3*3)', 11) 
OP_RES Fork2(OP_RES &e1, OP_RES &e2, OP op); 

int main()
{	
	int card[N];  // 记录四张卡牌的数值

	while (1)
	{
        // 用户输入四张卡牌对应的数值
		for (int i=0; i<N; i++)
		{
			printf("input the %d-th card number: ", i+1);
			scanf("%d", &card[i]);
		}
		
        // 解24点问题
		game24(card);

		// 打印四张卡牌组合成24的所有算式
		OP_RES_SET::iterator it;
		for (it=S[MAX_IDX].begin(); it!=S[MAX_IDX].end(); it++)
		{
			if (it->second == 24)  
				cout << it->first << endl;
		}
		
		// 清空运算结果, 便于下一次计算
		for (int i=0; i<=MAX_IDX; i++)
			S[i].clear();
		
	}

	getchar();
	return 0;
}

void game24(int card[])  
{
	// 初始化单张卡牌组合对应的运算结果 即S[0001]  S[0010] S[0100] S[1000]， 分别对应{a0} {a1} {a2} {a3}
	for (int i=0; i<N; i++)
	{
		OP_RES pt;
		char ct[20];

		_itoa(card[i], ct, 10);
        
		pt.first = string(ct);
		pt.second = card[i];
        
		S[(int)pow((float)2,(float)i)].insert(pt);
	}

	// 计算所有卡牌组合的运算结果，并记录运算过程
	for (int i=1; i<=MAX_IDX; i++)
		S[i] = f(i);
}

OP_RES_SET f(int i)
{
	if (!S[i].empty()) // 该卡牌组合内部的+-*/运算结果已经得到
		return S[i];
	
	OP_RES_SET res;  
	for (int j=1; j<i; j++)    
	{
		if ((j & i) == j)  // i属于j的真子集
		{
			OP_RES_SET vt = Fork(f(j), f(i-j));  // 卡牌组合j + 卡牌组合i-j = 卡牌组合i  如二进制：0001(a0) + 0110(a2 a3) = 0111(a0 a1 a2) 
			OP_RES_SET::iterator it;
			for (it = vt.begin(); it!=vt.end(); it++)
				res.insert(*it);
		}
	}
	return res;
}


OP_RES_SET Fork(OP_RES_SET &s1, OP_RES_SET &s2)
{
	OP_RES_SET res;

	if (s1.empty() || s2.empty())
		return res;
	
	OP_RES_SET::iterator it1;  
	OP_RES_SET::iterator it2;
    
    // 遍历来自s1和s2中的每一对元素，计算+-*/结果
	for (it1=s1.begin(); it1!=s1.end(); it1++)
	{
		for (it2=s2.begin(); it2!=s2.end(); it2++)
		{
			OP_RES e1 = *it1;
			OP_RES e2 = *it2;
			OP_RES pt;
			
			// 加
			pt = Fork2(e1, e2, ADD);
			res.insert(pt);

			// 减
			if (e1.second >= e2.second)
			{
				pt = Fork2(e1, e2, SUB);
				res.insert(pt);
			}

			// 乘
			pt = Fork2(e1, e2, MUL);
			res.insert(pt);

			// 除
			if (e2.second != 0  && e1.second % e2.second == 0)
            {
                pt = Fork2(e1, e2, DIV);
			    res.insert(pt);
            }
		}
	}
	return res;
}

OP_RES Fork2(OP_RES &e1, OP_RES &e2, OP op)
{	
	OP_RES res;
	switch (op)
	{
	case ADD:  // +
		res.first = '(' + e1.first + '+' + e2.first + ')';  // e1和e2相加的结果 
		res.second = e1.second + e2.second;                 // e1和e2相加的算式，保存于字符串中
		break;
	case SUB: // -
		res.first = '(' + e1.first + '-' + e2.first + ')';
		res.second = e1.second - e2.second;
		break;
	case MUL:  // *
		res.first = '(' + e1.first + '*' + e2.first + ')';
		res.second = e1.second * e2.second;
		break;
	case DIV: // /
		res.first = '(' + e1.first + '/' + e2.first + ')';
		res.second = e1.second / e2.second;
		break;
	default:
		res.first = "";
		res.second = -1;
	}
	return res;
}

