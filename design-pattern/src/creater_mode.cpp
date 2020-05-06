#include <iostream>
using namespace std;

class Builder
{
	public:
		virtual void build_head(){}
		virtual void build_body(){}
		virtual void build_left_arm(){}
		virtual void build_right_arm(){}
		virtual void build_left_leg(){}
		virtual void build_right_leg(){}

		void create()
		{
			build_head();
			build_body();
			build_left_arm();
			build_right_arm();
			build_left_leg();
			build_right_leg();
		}
};

class ThinBuilder : public Builder
{
	public:
		void build_head()
		{
			cout << "build thin head" << endl;
		}

		void build_body()
		{
			cout << "build thin body" << endl;
		}

		void build_left_arm()
		{
			cout << "build thin left arm" << endl;
		}

		void build_right_arm()
		{
			cout << "build thin right arm" << endl;
		}

		void build_left_leg()
		{
			cout << "build thin left leg" << endl;
		}

		void build_right_leg()
		{
			cout << "build thin right leg" << endl;
		}
};

class FatBuilder : public Builder
{
	public:
		void build_head()
		{
			cout << "build fat head" << endl;
		}

		void build_body()
		{
			cout << "build fat body" << endl;
		}

		void build_left_arm()
		{
			cout << "build fat left arm" << endl;
		}

		void build_right_arm()
		{
			cout << "build fat right arm" << endl;
		}

		void build_left_leg()
		{
			cout << "build fat left leg" << endl;
		}

		void build_right_leg()
		{
			cout << "build fat right leg" << endl;
		}
};

class Director
{
	private:
		Builder* _builder;
	public:
		Director(Builder* b) : _builder(b) {}
		void create()
		{
			_builder->create();
		}
};

int main()
{
	ThinBuilder thin_builder;
	Director director1(dynamic_cast<Builder*>(&thin_builder));
	director1.create();

	FatBuilder fat_builder;
	Director director2(dynamic_cast<Builder*>(&fat_builder));
	director2.create();

	return 0;
}
