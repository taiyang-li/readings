#include <iostream>

using namespace std;

class Vehicle
{
	public:
		Vehicle(int weight) : _weight(weight) {}
		virtual ~Vehicle() {}
		virtual int weight() const
		{
			return _weight;
		}

		virtual void start() {}
		virtual Vehicle* copy() const {};
	protected:
		int _weight;
};

class RoadVehicle : public Vehicle
{
	public:
		 RoadVehicle(int weight) : Vehicle(weight) {}
		 virtual ~RoadVehicle() {}

		 virtual void start()
		 {
			 cout << "start RoadVehicle" << endl;
		 }

		 virtual Vehicle* copy() const 
		 {
			 return new RoadVehicle(*this);
		 }
};

class AutoVehicle : public RoadVehicle 
{
	public:
		AutoVehicle(int weight) : RoadVehicle(weight) {}
		virtual ~AutoVehicle() {}

		virtual void start()
		{
			cout << "start AutoVehicle" << endl;
		}

		virtual Vehicle* copy() const
		{
			return new AutoVehicle(*this);
		}
};

class Aircraft : public Vehicle
{
	public: 
		Aircraft(int weight) : Vehicle(weight) {}
		virtual ~Aircraft() {}

		virtual void start()
		{
			cout << "start Aircraft" << endl;
		}

		virtual Vehicle* copy() const
		{
			return new Aircraft(*this);
		}
};

class Helicopter : public Aircraft 
{
	public:
		Helicopter(int weight) : Aircraft(weight) {}
		virtual ~Helicopter() {}

		virtual void start()
		{
			cout << "start Helicopter" << endl;
		}

		virtual Vehicle* copy() const
		{
			return new Helicopter(*this);
		}
};

class VehicleSurrogate
{
	public:
		VehicleSurrogate() : _vp(NULL) {}

		VehicleSurrogate(const Vehicle& v)
			: _vp(v.copy()) {}

		VehicleSurrogate(const VehicleSurrogate& vs)
		{
			if (vs._vp != NULL)
			{
				_vp = vs._vp->copy();
			}
			else
			{
				_vp = NULL;
			}
		}

		~VehicleSurrogate()
		{
			delete _vp;
		}

		VehicleSurrogate& operator =(const VehicleSurrogate& vs)
		{
			if (this != &vs)
			{
				delete _vp;
				_vp = (vs._vp != NULL ?  vs._vp->copy() : NULL);
			}
			return *this;
		}

		int weight()
		{
			if (_vp == NULL)
				return 0;

			return _vp->weight();
		}

		void start()
		{
			if (_vp == NULL)
			{
				cout << "invalid Vehicle Surrogate" << endl;
				return;
			}

			_vp->start();
		}

private:
		Vehicle* _vp;
};

int main()
{
	VehicleSurrogate parking_lot[1000];
	
	for (size_t i=0; i<1000; i++)
	{
		int flag = i%4;
		int weight = i;
		Vehicle* p = NULL;
		switch(flag)
		{
			case 0:
				p = new RoadVehicle(weight);  
				break;
			case 1:
				p = new AutoVehicle(weight);
				break;
			case 2:
				p = new Aircraft(weight); 
				break;
			case 3:
				p = new Helicopter(weight);
				break;
			default:
				cout << "impossible" << endl;
		}
		parking_lot[i] = VehicleSurrogate(*p);
		delete p;
	}

	for (size_t i=0; i<1000; i++)
	{
		parking_lot[i].start();
	}

	return 0;
}
