#include <iostream>
using namespace std;

class Scanner
{
	public:
		void scan() 
		{
			cout << "词法分析" << endl;
		}
};

class Parser
{
	public:
		void parse()
		{
			cout << "语法分析" << endl;
		}
};

class GenMidCode
{
	public:
		void gen_midcode()
		{
			cout << "产生中间代码" << endl;
		}
};

class GenMachineCode
{
	public:
		void gen_machinecode()
		{
			cout << "产生机器代码" << endl;
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


