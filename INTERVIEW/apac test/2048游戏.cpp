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
#include <set>
#include <windows.h>
#include <ctime>
#include <fstream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stack>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <exception>
#include <map>
#include <list>
#include <algorithm>
#include <time.h>

using namespace std;

typedef  unsigned char  uchar;                       // 用一个8位二进制数的低7位表示数码管对应的数字编码
enum INC_DEC {INC=0, DEC};								 // 表示递增还是递减
enum ROW_COL {ROW=0, COL};                                  // 表示行还是列
const string IN_FILE = "A-small-practice.in";        // 输入文件
const string OUT_FILE = "A-small-practice.out";       // 输出文件 

//////////////////////////
void move_board(vector<vector<int>> &board, string op);

void move_line(vector<int> &line, INC_DEC ort); 

vector<int> get_line(vector<vector<int>> &board, ROW_COL row_col, int i);
void set_line(vector<vector<int>> &board, vector<int> &line, ROW_COL row_col, int i);
int get_element(vector<vector<int>> &board, ROW_COL row_col, int i, int j);
void set_element(vector<vector<int>> &board, ROW_COL row_col, int i, int j, int v);
void print_board(vector<vector<int>> &board);
void print_line(vector<int> &line);



int main()
{
	// 打开文件
	ifstream ifile(IN_FILE);
	ofstream ofile(OUT_FILE);

	
	// 读取测试样粒个数
	int case_num = 0;
	ifile >> case_num;
	
	// 遍历每一个测试用例
	for (int case_count = 1; case_count <= case_num && !ifile.eof(); ++case_count)
	{
		// 读取长度
		int len = 0;
		string op;
		
		ifile >> len;
		ifile >> op;
		
		// 读取矩阵
		vector<vector<int>> board;
		for (int i=0; i<len; i++)
		{
			vector<int> v_t;
			for (int j=0; j<len; j++)
			{
				int i_t = 0;
				ifile >> i_t;
				v_t.push_back(i_t);
			}
			board.push_back(v_t);
		}

		cout << "----------------------------------" << endl;
		cout << case_count << endl;
		// 打印输入矩阵
		print_board(board);

		// 进行处理
		move_board(board, op);

		// 输出矩阵
		print_board(board);

		// 打印输出到文件
		ofile << "Case #" << case_count << ":" << endl;
		for (int i=0; i<len; ++i)
		{
			for (int j=0; j<len; ++j)
			{
				ofile << board[i][j] << "\t";
			}
			ofile << endl;
		}
	}
	
	ifile.close();
	ofile.close();
	
	getchar();
	return 0;
}



void move_board(vector<vector<int>> &board, string op)
{
	INC_DEC inc_dec = (op == "left" || op == "up") ? INC : DEC;
	ROW_COL row_col = (op == "left" || op == "right") ? ROW : COL;

	const int len = board.size();

	for (int i=0; i<len; ++i)
	{
		vector<int> line = get_line(board,  row_col, i);
		move_line(line, inc_dec);
		set_line(board, line, row_col, i);
	}	
}


void move_line(vector<int> &line, INC_DEC ort)
{
	const int len = line.size();
	if (ort == INC)        // left  up 
	{
		int wr_pos = 0;
		int rd_pos = 0;
		while(rd_pos < len)
		{
			// 当前元素是0
			if (line[rd_pos] == 0)
			{
				rd_pos++;
				continue;
			}

			// 当前元素不为0 
			if (rd_pos == len-1)  // 边界元素
			{
				line[wr_pos++] = line[rd_pos++];
			}
			else
			{
				if (line[rd_pos] == line[rd_pos+1]) // 相邻元素相等
				{
					line[wr_pos++] = line[rd_pos] * 2;
					rd_pos += 2;
				}
				else
					line[wr_pos++] = line[rd_pos++];
			}
		}
		
		// 空出部分填0
		while (wr_pos < len)
			line[wr_pos++] = 0;
	}
	else
	{
		int wr_pos = len-1;
		int rd_pos = len-1;
		while (rd_pos >= 0)
		{
			if (line[rd_pos] == 0)
			{
				rd_pos--;
				continue;
			}

			if (rd_pos == 0)
				line[wr_pos--] = line[rd_pos--];
			else
			{
				if(line[rd_pos] == line[rd_pos-1])
				{
					line[wr_pos--] = line[rd_pos] * 2;
					rd_pos -= 2;
				}
				else
					line[wr_pos--] = line[rd_pos--];
			}
		}
		// 空出部分填0
		while (wr_pos >= 0)
			line[wr_pos--] = 0;
	}
}

vector<int> get_line(vector<vector<int>> &board, ROW_COL row_col, int i)
{
	const int len = board.size();
	vector<int> res(len, 0);

	for (int j=0; j<len; j++)
		res[j] = get_element(board, row_col, i, j);

	return res;
}


void set_line(vector<vector<int>> &board, vector<int> &line, ROW_COL row_col, int i)
{	
	const int len = board.size();
	for (int j=0; j<len; j++)
		set_element(board, row_col, i, j, line[j]);
}


int get_element(vector<vector<int>> &board, ROW_COL row_col, int i, int j)
{	
	return (row_col == ROW) ? board[i][j] : board[j][i];
}


void set_element(vector<vector<int>> &board, ROW_COL row_col, int i, int j, int v)
{	
	if (row_col == ROW) 
		board[i][j] = v;
	else
		board[j][i] = v;
}


void print_board(vector<vector<int>> &board)
{
	const int len = board.size();
	for (int i=0; i<len; i++)
		print_line(board[i]);
	cout << endl;
}

void print_line(vector<int> &line)
{
	const int len = line.size();
	for (int i=0; i<len; i++)
		cout << line[i] << "\t";
	cout << endl;
}





















