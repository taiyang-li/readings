#include <map>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <string>
#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <stack>
#include <numeric>
using namespace std;

class Solution {
public:
   void solveSudoku(vector<vector<char>> &board)
	{
		vector<vector<string>> tb;

		init_tb(tb, board);
		solve_sudo_core(tb, board, -1, -1);
	}

	// 用递归的方法来做
    bool del_char(string &s, char c)
    {
        if(s.size() == 0)
            return false;

        int i;
		int len = s.size();
        for(i=0; i<len; i++)
        {
            if (s[i] == c)
                break;
        }
        if (i==s.size())      //0   i-1   i    i+1
            return false;

		string t = s;
		s= "";
		if  (i!=0)            // s[i]为第一个元素时
			s += t.substr(0, i);

		if  (i!=t.size()-1)   // s[i]为最后一个元素时
			s += t.substr(i+1, t.size()-1-i);

		return true;
    }

    void init_tb(vector<vector<string>>  &tb,  vector<vector<char>> &board)
    {
        vector<string> t;
        string  tt = "123456789";
        // 首先给vector<string> 初始化
        for(int i=0; i<9; i++)
        {
            t.push_back(tt);
        }

        // 其次给vector<vector<int>> 初始化
        for(int i=0; i<9; i++)
        {
            tb.push_back(t);
        }

        for(int i=0; i<9; i++)
        {
            for(int j=0; j<9; j++)
            {
                if(board[i][j] != '.')
                {
                    tb[i][j] = board[i][j];
                }
            }
        }

        // 对所有的'.'元素进行更新 划定可能的值
        for(int i=0; i<9; i++)
        {
            for(int j=0; j<9; j++)
            {
                if (board[i][j] != '.')
                {
                    update_tb(tb, board, i, j);
                }
            }
        }


    }



    void update_tb(vector<vector<string>>  &tb,  vector<vector<char>> &board, int i, int j)  // board[i][j] 限定同行同列同宫格的取值
    {
        // 根据行法则对tb[i][j]进行更新
        for(int m=0; m<9; m++)
        {
            if (board[i][m] == '.')
            {
				del_char(tb[i][m], board[i][j]);
            }
        }
        // 根据列法则对tb[i][j]进行更新
        for (int m=0; m<9; m++)
        {
            if (board[m][j] == '.' )
            {
                del_char(tb[m][j], board[i][j]);
            }
        }

        // 根据九宫格法则对tb[i][j]进行更新
        int rr = i/3;   // 九宫格的行
        int cc = j/3;   // 九宫格的列
        for(int m=3*rr; m<3*rr+3; m++)
        {
            for(int n=3*cc; n<3*cc+3; n++)
            {
                if (board[m][n] == '.')
                {
                    del_char(tb[m][n], board[i][j]);
                }
            }
        }
    }

    //  扫描tb矩阵的第i行，得到新发现的数字
    vector<int> get_value_from_row(vector<vector<string>>  &tb, vector<vector<char>> &board, int i, bool &flag)  // 在board[i][j]位置的领域查找
    {
        vector<int>  res;  //
        // traverse the i row
        map<char, int> char_num;
		// 初始化哈希表
		/*
		for (char c='1'; c<='9'; c++)
			char_num[c] = 0;
		*/
		flag = true;

        for(int m=0; m<9; m++)
        {
            if(board[i][m] == '.')       // 限定在没有确定数字的矩阵范围内
            {
                if (tb[i][m].empty())   // the board is not right
				{

 					flag = false;
                    return res;
				}
                if (tb[i][m].size() == 1)   // find the only choice
                {
                    board[i][m] = tb[i][m][0];
                    res.push_back(i);
                    res.push_back(m);
                    res.push_back(board[i][m]-'0');
                    return res;
                }
				int n;
				int len = tb[i][m].size();
                for(n=0; n<len; n++)
                    char_num[tb[i][m][n]]++;
            }
        }
        // traverse the map and find the only candidate
        char c;
        for(c='1'; c<='9'; c++)
        {
            if(char_num[c] == 1)
            {
                break;
            }
        }
        if (c == '9'+1)  // can not find the value
            return res;
        // find which string is c come from
        for(int m=0; m<9; m++)
        {
            if (tb[i][m].find(c) != string::npos)
            {
				board[i][m] = c;
				tb[i][m] = c;
                res.push_back(i);
                res.push_back(m);
                res.push_back(c-'0');
            }
        }
        return res;
    }


 // 根据tb得到某一位置的值
    vector<int> get_value_from_col(vector<vector<string>>  &tb, vector<vector<char>> &board, int j, bool &flag)  // 在board[i][j]位置的领域查找
    {
        vector<int>  res;  //
		flag = true;          // 初始值是真
        // traverse the j col
        map<char, int> char_num;
        for(int m=0; m<9; m++)
        {
            if(board[m][j] == '.')
            {
                if (tb[m][j].size() == 0)   // the board is not right
				{
					flag = false;
                    return res;
				}
                if (tb[m][j].size() == 1)   // find the only choice
                {
                    board[m][j] = tb[m][j][0];
                    res.push_back(m);
                    res.push_back(j);
                    res.push_back(board[m][j]-'0');
                    return res;
                }
				int n;
				int len = tb[m][j].size();
                for(n=0; n<len; n++)
                    char_num[tb[m][j][n]]++;
            }
        }
        // traverse the map and find the only candidate
        char c;
        for(c='1'; c<='9'; c++)
        {
            if(char_num[c] == 1)
            {
                break;
            }
        }
        if (c == '9'+1)  // can not find the value
            return res;
        // find which string is c come from
        for(int m=0; m<9; m++)
        {
            if (tb[m][j].find(c) != string::npos)
            {
				board[m][j] = c;
				tb[m][j] = c;
                res.push_back(m);
                res.push_back(j);
                res.push_back(c-'0');
            }
        }
        return res;
    }

	// 根据tb得到某一位置的值
    vector<int> get_value_from_mat(vector<vector<string>>  &tb, vector<vector<char>> &board, int i, int j, bool &flag)  // 在board[i][j]位置的领域查找
    {
        vector<int>  res;  //
		flag = true;
		int rr = i;
		int cc = j;
        // traverse the j col
        map<char, int> char_num;
        for(int m=3*rr; m<3*(rr+1); m++)
		{
			for(int n=3*cc; n<3*(cc+1); n++)
			{
				if(board[m][n] == '.')
				{
					if (tb[m][n].size() == 0)   // the board is not right
					{
						flag = false;
						return res;
					}
					if (tb[m][n].size() == 1)   // find the only choice
					{
						board[m][n] = tb[m][n][0];
						res.push_back(m);
						res.push_back(n);
						res.push_back(board[m][n]-'0');
						return res;
					}
					int k;
					int len = tb[m][n].size();
					for(k=0; k<len; k++)
						char_num[tb[m][n][k]]++;
				}
			}
		}
        // traverse the map and find the only candidate
        char c;
        for(c='1'; c<='9'; c++)
        {
            if(char_num[c] == 1)
            {
                break;
            }
        }
        if (c == '9'+1)  // can not find the value
            return res;
        // find which string is c come from
        for(int m=3*rr; m<3*(rr+1); m++)
        {
			for(int n=3*cc; n<3*(cc+1); n++)
			{
				if (tb[m][n].find(c) != string::npos)
				{
					board[m][n] = c;
					tb[m][n] = c;
					res.push_back(m);
					res.push_back(n);
					res.push_back(c-'0');
				}
			}
        }
        return res;
    }


	vector<int>  scan_board_full(vector<vector<string>>  &tb, vector<vector<char>> &board, bool &flag)
	{
		vector<int> res;
		flag = true;
		// 一行行扫描
		for(int m=0; m<9; m++)
		{
			res = get_value_from_row(tb, board, m, flag);
			if (!res.empty() || flag == false)      // 如果找到了或者发现错误
			{

				return res;
			}
		}

		// 一列列扫描
		for(int m=0; m<9; m++)
		{
			res = get_value_from_col(tb, board, m, flag);
			if (!res.empty() || flag == false)
			{

				return res;
			}
		}

		// 一个个九宫格扫描
		for(int m=0; m<3; m++)
		{
			for(int n=0; n<3; n++)
			{
				res = get_value_from_mat(tb, board, m, n, flag);
				if (!res.empty() || flag == false)
				{

					return res;
				}
			}
		}

		return res;
	}


	vector<int>  scan_board_custom(vector<vector<string>>  &tb, vector<vector<char>> &board, int i, int j, bool &flag)
	{
		vector<int> res = get_value_from_row(tb, board, i, flag);

		if(!res.empty()  || flag == false)
		{

			return res;
		}

		res = get_value_from_col(tb, board, j, flag);

		if(!res.empty() || flag == false)
		{

			return res;
		}

		res = get_value_from_mat(tb, board, i/3, j/3, flag);

		return res;

	}

	bool  solve_sudo_core(vector<vector<string>> &tb, vector<vector<char>> &board, int r, int c)
	{

		// 输出true表示能够解决
		// 输出false表示不能解决

		// 如果board已经被填满，则返回
		if (is_finish(board) == true)   return  true;




		bool ctn_flag = true;
		vector<int> res;

		if (!(r==-1 && c==-1))
		{
			res = scan_board_custom(tb, board, r, c, ctn_flag);
		}

		if ( !res.empty() && ctn_flag == true)           // 输出不为空, 且可以继续
		{

			update_tb(tb, board, res[0], res[1]);
			return  solve_sudo_core(tb, board, res[0], res[1]);   // 递归函数
		}
		else if(ctn_flag == false)
		{

			return false;
		}
		else
		{
			res = scan_board_full(tb, board, ctn_flag);
			if (!res.empty() && ctn_flag)
			{

				update_tb(tb, board, res[0], res[1]);
				return  solve_sudo_core(tb, board, res[0], res[1]);
			}
			else if (ctn_flag == false)
			{

				return false;
			}
			else         // 试错法
			{

				bool fd_flag = false;
				int  fd_len = 1;
				int  ii;       // 横坐标
				int  jj;       // 纵坐标
				string t;      // 字符串位置
				while(fd_flag == false)
				{
					fd_len++;
					for(int i=0; i<9; i++)
					{
						for(int j=0; j<9; j++)
						{
							if (board[i][j] == '.')
							{
								if (tb[i][j].size() == fd_len)
								{
									ii = i;
									jj = j;
									t = tb[i][j];

									fd_flag = true;
									break;
								}
							}
						}
						if (fd_flag == true)
							break;
					}
				}


				// 从tt中找到一系列元素来试错
				int len = t.size();
				vector<vector<string>>  t_tb = tb;
				vector<vector<char>> t_board = board;
				for(int i=0; i<len; i++)
				{

					tb = t_tb;
					board = t_board;
					tb[ii][jj] = t[i];
					board[ii][jj] = t[i];
					update_tb(tb, board, ii, jj);
					if (solve_sudo_core(tb, board, ii, jj) == true)
					{
						return true;
					}
				}
				return false;
			}
		}
	}


	bool is_finish(vector<vector<char>> &board)
	{
		// 检测边界条件
		bool full_flag = true;
		for(int i=0; i<9; i++)
		{
			int j;
			for(j=0; j<9; j++)
			{
				if (board[i][j] == '.')
				{
					full_flag = false;
					break;
				}
			}
			if (j != 9)   // 如果上一个循环是跳出的，那么这个循环也会跳出
				break;
		}
		return full_flag;
	}

	bool is_invalid(vector<vector<string>> &tb, vector<vector<char>> &board)
	{
		for(int i=0; i<9; i++)
		{
			for(int j=0; j<9; j++)
			{
				if (board[i][j] == '.')
				{
					if(tb[i][j].empty())
					{
						return true;
					}
				}
			}
			return false;
		}
	}

};

int main() {
    return 0;
}

