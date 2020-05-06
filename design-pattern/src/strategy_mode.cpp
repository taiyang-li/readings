#include <iostream>
using namespace std;

class ReplaceAlgorithm
{
public:
	virtual void Replace() = 0;
};

class LRU_ReplaceAlgorithm : public ReplaceAlgorithm
{
	public: 
		void Replace() 
		{
			cout << "LRU Replace Algorithm" << endl;
		}
};

class FIFO_ReplaceAlgorithm : public ReplaceAlgorithm
{
	public:
		void Replace()
		{
			cout << "FIFO Replace Algorithm" << endl;
		}
};

class Random_ReplaceAlgorithm : public ReplaceAlgorithm
{
	public: 
		void Replace()
		{
			cout << "Random Replace Algorithm" << endl;
		}
};

class Cache1
{
	private:
		ReplaceAlgorithm* _ra;
	public:
		Cache1(ReplaceAlgorithm* ra) 
		{
			_ra = ra;
		}

		~Cache1() {}

		void Replace() {
			_ra->Replace();
		}
		
};

enum RA {LRU, FIFO, RANDOM};
class Cache2
{
	private:
		ReplaceAlgorithm* _ra;
	public:
		Cache2(RA ra)
		{
			if (ra == LRU)
			{
				_ra = new LRU_ReplaceAlgorithm();
			}
			else if (ra == FIFO)
			{
				_ra = new FIFO_ReplaceAlgorithm();;
			}
			else if (ra == RANDOM)
			{
				_ra = new Random_ReplaceAlgorithm();
			}
			else
			{
				_ra = NULL;
			}
		}

		~Cache2()
		{
			if (_ra != NULL)
				delete _ra;
		}

		void Replace()
		{
			_ra->Replace();
		}
};

template <typename RA>
class Cache3
{
	private:
		RA _ra;
	public:
		Cache3() {}
		~Cache3() {}
		void Replace() {
			_ra.Replace();
		}
};


int main()
{
	Cache1 c1(new FIFO_ReplaceAlgorithm());
	c1.Replace();

	Cache2 c2(FIFO);
	c2.Replace();

	Cache3<FIFO_ReplaceAlgorithm> c3;
	c3.Replace();
	return 0;
}
