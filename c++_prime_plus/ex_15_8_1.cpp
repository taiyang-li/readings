// vect3.cpp -- using STL functions
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

class Remote;

class Tv
{
private:
    int state;             // on or off
    int volume;            // assumed to be digitized
    int maxchannel;        // maximum number of channels
    int channel;           // current channel setting
    int mode;              // broadcast or cable
    int input;             // TV or DVD
	
public:
    friend class Remote;   // Remote can access Tv private parts
    enum {Off, On};
    enum {MinVal,MaxVal = 20};
    enum {Antenna, Cable};
    enum {TV, DVD};

    Tv(int s = Off, int mc = 125) : state(s), volume(5),
        maxchannel(mc), channel(2), mode(Cable), input(TV) {}
    void onoff() {state = (state == On)? Off : On;} 
    bool ison() const {return state == On;}
    bool volup()
	{
		if (volume < MaxVal)
		{
			volume++;
			return true;
		}
		else
			return false;
	}
    bool voldown()
	{
		if (volume > MinVal)
		{
			volume--;
			return true;
		}
		else
			return false;
	}
    void chanup()
	{
		if (channel < maxchannel)
			channel++;
		else
			channel = 1;
	}
    void chandown()
	{
		if (channel > 1)
			channel--;
		else
			channel = maxchannel;
	}
    void set_mode() {mode = (mode == Antenna)? Cable : Antenna;} 
    void set_input() {input = (input == TV)? DVD : TV;}
    void settings() const// display all settings
	{
		cout << "TV is " << (state == Off? "Off" : "On") << endl;
		if (state == On)
		{
			cout << "Volume setting = " << volume << endl;
			cout << "Channel setting = " << channel << endl;
			cout << "Mode = "
				<< (mode == Antenna? "antenna" : "cable") << endl;
			cout << "Input = "
				<< (input == TV? "TV" : "DVD") << endl;
		}
	}
	
	void set_remote_mode(Remote &r);
	
};


class Remote
{
private:
    int mode;              // controls TV or DVD
	int remote_mode;      // 常规模式 或者 互动模式
	enum {RemoteOn, RemoteOff};
public:
	friend class Tv; 
    Remote(int m = Tv::TV, int rm=RemoteOn) : mode(m), remote_mode(RemoteOn)  {}
    bool volup(Tv & t) { return t.volup();}          
    bool voldown(Tv & t) { return t.voldown();}
    void onoff(Tv & t) { t.onoff(); }
    void chanup(Tv & t) {t.chanup();}
    void chandown(Tv & t) {t.chandown();}
    void set_chan(Tv & t, int c) {t.channel = c;}  
    void set_mode(Tv & t) {t.set_mode();}
    void set_input(Tv & t) {t.set_input();}
	void show_remote_mode() 
	{
		if  (RemoteOn == remote_mode) 
			cout << "遥控器处于常规模式" << endl;
		else
			cout << "遥控器处于互动模式" << endl;
	}
};


void Tv::set_remote_mode(Remote &r) 
{
	if (state == On)
		r.remote_mode = ((r.remote_mode == Remote::RemoteOn) ? Remote::RemoteOff : Remote::RemoteOn); 
}


int main()
{
	Remote r;
	r.show_remote_mode();

	Tv t(Tv::On);
	t.settings();
	cout << endl;
	
	t.onoff();
	t.set_remote_mode(r);
	r.show_remote_mode();

	t.onoff();
	t.set_remote_mode(r);
	r.show_remote_mode(); 
	 
	system("pause");
	return 0;
}
