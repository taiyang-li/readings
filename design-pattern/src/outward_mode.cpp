#include <iostream>
using namespace std;

class Scanner
{
	public:
		void scan() 
		{
			cout << "�ʷ�����" << endl;
		}
};

class Parser
{
	public:
		void parse()
		{
			cout << "�﷨����" << endl;
		}
};

class GenMidCode
{
	public:
		void gen_midcode()
		{
			cout << "�����м����" << endl;
		}
};

class GenMachineCode
{
	public:
		void gen_machinecode()
		{
			cout << "������������" << endl;
		}
};

class Compiler 
{
	public:
		void run()
		{
			Scanner scanner;
			scanner.scan();

			Parser parser;
			parser.parse();

			GenMidCode midcode_gener;
			midcode_gener.gen_midcode();

			GenMachineCode machinecode_gener;
			machinecode_gener.gen_machinecode();
		}
};

int main()
{
	Compiler compiler;
	compiler.run();
	return 0;
}


