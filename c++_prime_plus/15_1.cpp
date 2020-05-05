#include <iostream>
#include <cstdio>
#include <cstdlib>


using namespace std;


class Tv 
{
public: 
	friend class Remote;
	enum {Off, On};
	enum {MinVal, MaxVal = 20};
	enum {Antenna, Cable};
	enum {TV, DVD};
	Tv(int s = Off, int mc = 125) : state(s), volume(5), maxchannel(mc), 
		channel(2), mode(Cable), input(TV) {} 
	void onoff() {state = (state == Off ? On : Off);}
	bool ison() const {return state == On;}
	bool volup();
	bool voldown();
	void chanup();
	void chandown();
	void set_mode() {mode = (mode == Antenna ? Cable : Antenna);}
	void set_input() {input = (input == TV ? DVD : TV);}
	void settings() const; // display all setting
private:
	int state; // on or off
	int volume;  
	int maxchannel;  // max number of channels
	int channel;  // current channel settting
	int mode;  // broadcast or cable
	int input;  // TV or DVD 
};

class Remote
{	
private:
	int mode;         // TV OR DVD
public: 
	Remote(int m = Tv::TV) : mode(m) {}
	bool volup(Tv &t) {return t.volup();}
	bool voldown(Tv &t) {return t.voldown();}
	void onoff(Tv &t) {t.onoff();}
	void chanup(Tv &t) {t.chanup();}
	void chandown(Tv &t) {t.chandown();}
	void set_chan(Tv &t, int c) {t.channel = c;}
	void set_mode(Tv &t) {t.set_mode();}
	void set_input(Tv &t) {t.set_input();}
};



bool Tv::volup() 
{
	if (volume < MaxVal)
	{
		volume++;
		return true;
	}
	else
		return false;
}


bool Tv::voldown()
{
	if (volume > MinVal)
	{
		volume--;
		return true;
	}
	else
		return false;
}

void  Tv::chanup()
{
	if (channel < maxchannel)
		channel++;
	else
		channel = maxchannel;
}



void Tv::chandown()
{
	if (channel > 1)
		channel++;
	else
		channel = 1;	
}

void Tv::settings() const 
{
	cout << "Tv is " << ((state == On) ?  "On" : "Off") << endl;
	if (state == On)
	{
		cout << "volume: " << volume << endl;
		cout << "channel: " << channel << endl;
		cout << "mode = " << ((mode == Antenna) ? "Antenna" : "Cable") << endl;
		cout << "input: " << ((input == TV) ? "TV" : "DVD") << endl;
	}
	cout << endl;
}



int main()
{
	Tv s42;
	cout << "initial seetings for 42 " << endl;
	s42.settings();
	s42.onoff();
	s42.chanup();
	cout << "adjusted setting for 42" << endl;
	s42.chanup();
	cout << "adjusted setting for 42" << endl;
	s42.settings();
	
	Remote grey;
	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	cout << "setting after using remote" << endl;
	s42.settings(); 

	Tv s58(Tv::On);
	s58.set_mode();
	grey.set_chan(s58, 28);
	cout << "s58 settings: " << endl;
	s58.settings(); 
	
	return 0;
}
