#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Mememto
{
	friend class GameRole;
	public:
		Mememto(int life, int attack, int defense) : 
			_life(life), _attack(attack), _defense(defense) {}
		
		Mememto& operator=(const Mememto& mem)
		{
			_life = mem._life;
			_attack = mem._attack;
			_defense = mem._defense;
		}

		void show()
		{
			cout << "life: " << _life << ", attack: " << 
				_attack << ", defense: " << _defense << endl;
		}

	private:
		int _life;
		int _attack;
		int _defense;
};

class GameRole
{
	private:
		int _life;
		int _attack;
		int _defense;

	public:
		GameRole() : _life(100), _attack(100), _defense(100) {}

		void show() 
		{
			cout << "life: " << _life << ", attack: " << 
				_attack << ", defense: " << _defense << endl;
		}

		void attack()
		{
			_life -= 10;
			_attack -= 10;
			_defense -= 10;
		}

		Mememto save()
		{
			Mememto mem(_life, _attack, _defense);
			return mem;
		}

		void load(const Mememto& mem)
		{
			_life = mem._life;
			_attack = mem._attack;
			_defense = mem._defense;
		}
};

class CareTake
{
	private:
		vector<Mememto> _vec_mememto;

	public:
		CareTake() {}

		void save(const Mememto& mem)
		{
			_vec_mememto.push_back(mem);
		}

		Mememto load(size_t state)
		{
			if (state < 0 || state >= _vec_mememto.size())
				return Mememto(0, 0, 0);

			return _vec_mememto[state];
		}

};

int main()
{
	// GameRole contruscor
	GameRole gr;
	gr.show();

	// test attack 
	gr.attack();
	gr.show();

	// test save
	Mememto mem1 = gr.save();
	mem1.show();

	// test load 
	Mememto mem2(10, 20, 30);
	mem2.show();
	gr.load(mem2);

	// test CareTake
	CareTake ct;
	ct.save(mem1);
	ct.save(mem2);

	gr.load(ct.load(0));
	gr.show();

	gr.load(ct.load(1));
	gr.show();
	return 0;
}


