#include <iostream>
using namespace std;

class OS
{
	public:
		virtual void install_os_impl() {}
};

class WindowOS : public OS
{
	public:
		virtual void install_os_impl()
		{
			cout << "install Windows OS" << endl;
		}
};

class LinuxOS : public OS
{
	public:
		virtual void install_os_impl()
		{
			cout << "install Linux OS" << endl;
		}
};

class MaxOS : public OS
{
	public:
		virtual void install_os_impl()
		{
			cout << "install Mac OS" << endl;
		}
};

class Computer
{
	public:
		virtual void install_os(OS* os) {}
};

class AppleComputer : public Computer
{
	public:
		virtual void install_os(OS* os)
		{
			os->install_os_impl();
		}
};

class DellComputer : public Computer
{
	public:
		virtual void install_os(OS* os)
		{
			os->install_os_impl();
		}
};

class HPComputer : public Computer
{
	public:
		virtual void install_os(OS* os)
		{
			os->install_os_impl();
		}
};

int main()
{
	OS* os1 = new LinuxOS();
	OS* os2 = new MaxOS();

	Computer* computer = new AppleComputer();
	computer->install_os(os1);
	computer->install_os(os2);

	return 0;
}
