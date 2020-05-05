#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;

string ss[20]; 
int str_num = 0;
bool iscontinue = true;
enum OP {copy_=0, add, find_, rfind_, insert, reset, print, printall, over, other};

OP transform(const string& cmd);
int process_int();
string process_string();
void process();

OP transform(const string& cmd)
{
    if (cmd == "copy")
        return copy_;
    else if (cmd == "add")
        return add;
    else if (cmd == "find")
        return find_;
    else if (cmd == "rfind")
        return rfind_;
    else if (cmd == "insert")
        return insert;
    else if (cmd == "reset")
        return reset;
    else if (cmd == "print")
        return print;
    else if (cmd == "printall")
        return printall;
    else if (cmd == "over")
        return over;
    else 
        return other;
}

int process_int()
{
    string cmd;
    cin >> cmd;
    string S;
    int N;
    switch(transform(cmd))
    {
        case find_:
            S = process_string();
            N = process_int() - 1;
            if (strstr(ss[N].c_str(), S.c_str()) != NULL)
            {
                return ss[N].find(S) + 1;
            }
            else 
                return S.size();
        case rfind_:
            S = process_string();
            N = process_int() - 1;
            if (strstr(ss[N].c_str(), S.c_str()) != NULL)
                return ss[N].rfind(S) + 1;
            else
                return S.size();
        default:
            return atoi(cmd.c_str());
    }
}

bool isint(const string& input)
{
    if (input.length() > 5)
        return false;
    
    for (int i=0; i<input.length(); i++)
    {
        if (!isdigit(input[i]))
            return false;
    }
    return true;
}

string process_string()
{
    string cmd;
    cin >> cmd;
    string S;
    string S1;
    string S2;
    int N;
    int L;
    int X;
    ostringstream oss;
    switch(transform(cmd))
    {
        case copy_:
            N = process_int() - 1;
            X = process_int() - 1;
            L = process_int();
            return ss[N].substr(X, L);
        case add:
            S1 = process_string();
            S2 = process_string();
            if (isint(S1) && isint(S2))
            {
                N = atoi(S1.c_str()) + atoi(S2.c_str());
                oss << N;
                return oss.str();
            }
            else
                return S1 + S2; 
        default:
            return cmd;
    }
}

void process()
{   
    string cmd;
    cin >> cmd;
    string S;
    int N;
    int X;
    switch(transform(cmd))
    {
        case insert:
            S = process_string();
            N = process_int() - 1;
            X = process_int();
            ss[N] = ss[N].substr(0, X) + S + ss[N].substr(X);
            break;
        case reset:
            S = process_string();
            N = process_int() - 1;
            ss[N] = S;
            break;
        case print:
            N = process_int() - 1;
            cout << ss[N] << endl;
            break;
        case printall:
            for (int i=0; i<str_num; i++)
                cout << ss[i] << endl;
            break;
        case over:
            iscontinue = false;
            break;
    }
}
int main()
{
	cin >> str_num;
	for (int i=0; i<str_num; i++)
        cin >> ss[i];
    
    while (iscontinue)
        process();
    return 0;
}



