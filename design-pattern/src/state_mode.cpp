#include <iostream>
using namespace std;

class War;
class State
{
	public:
		virtual void first_state(War* war) {}
		virtual void second_state(War* war) {}
		virtual void third_state(War* war) {}
		virtual void forth_state(War* war) {}
		virtual void current_state(War* war) {}
};

class War
{
	private:
		int _days;
		State* _state;

	public:
		War(State* state) : _state(state), _days(0) {}
		~War() {delete _state;}

		int get_days()
		{
			return _days;
		}

		void set_days(int days)
		{
			_days = days;
		}

		void set_state(State* state)
		{
			delete _state;
			_state = state;
		}

		void get_state()
		{
			return _state->current_state(this);
		}
};

class ForthState : public State
{
	public:
		void current_state(War* war)
		{
			forth_state(war);
		}

		void forth_state(War* war)
		{
			cout << "end." << endl;
		}
};

class ThirdState : public State
{
	public:
		void current_state(War* war)
		{
			third_state(war);
		}

		void third_state(War* war)
		{
			int cur_days = war->get_days();
			if (cur_days < 30)
			{
				cout << "this is the " << cur_days << "-th day, during third state" << endl;
			}
			else
			{
				war->set_state(new ForthState());
			}
		}
};

class SecondState : public State
{
	public:
		void current_state(War* war)
		{
			second_state(war);
		}

		void second_state(War* war)
		{
			int cur_days = war->get_days();
			if (cur_days < 20)
			{
				cout << "this is the " << cur_days << "-th day, during second state" << endl;
			}
			else
			{
				war->set_state(new ThirdState());
			}
		}
};

class FirstState : public State
{
	public:
		void current_state(War* war)
		{
			first_state(war);
		}

		void first_state(War* war)
		{
			int cur_days = war->get_days();
			if (cur_days < 10)
			{
				cout << "this is the " << cur_days << "-th day, during first state" << endl;
			}
			else
			{
				war->set_state(new SecondState());
			}
		}
};

int main()
{
	War* war = new War(new FirstState());
	
	for (size_t i=0; i<40; i++)
	{
		war->set_days(i);
		war->get_state();
	}

	return 0;
}


