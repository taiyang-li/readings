#include <iostream>
#include <string>
using namespace std;


class TableTennisPlayer
{
private:
	string firstname;
	string lastname;
	bool hasTable;
public:
	TableTennisPlayer(const string &fn = "none",
			   const string &ln = "none", bool ht = false);
	void Name() const;
	bool HasTable() const {return hasTable;}
	void ResetTable(bool v) {hasTable = v;}
};

TableTennisPlayer::TableTennisPlayer(const string &fn, 
		const string &ln, bool ht): 
			firstname(fn), lastname(ln), hasTable(ht) {}

void TableTennisPlayer::Name() const 
{
	cout << lastname << ", " << firstname;
}


class RatedPlayer : public TableTennisPlayer
{
private:
	unsigned int rating;  
	
public:
	RatedPlayer(unsigned int r=0, const string &fn = "none", 
			const string &ln =  "none", bool ht = false);
	RatedPlayer(unsigned int r, const TableTennisPlayer &tp);
	unsigned int Rating() const {return rating;}
	void ResetRating(unsigned int r) {rating = r;}
};


RatedPlayer::RatedPlayer(unsigned int r, const string &fn, 
		const string &ln, bool ht) : TableTennisPlayer(fn, ln, ht)
{	
	rating = r;
}

/*
RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer &tp)
	: TableTennisPlayer(tp)
{
	rating = r;
} */


RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer &tp)
	: TableTennisPlayer(tp), rating(r)  {}

	




void show(const TableTennisPlayer &rt)
{
	cout << "Name: ";
	rt.Name();
	if (rt.HasTable())
		cout << ": has a table" << endl;
	else
		cout << ": has no table" << endl;
}

void show1(const TableTennisPlayer *rt)
{	
	cout << "Name: ";
	rt->Name();
	if (rt->HasTable())
		cout << ": has a table" << endl;
	else
		cout << ": has no table" << endl;
}



int main()
{
	/*
	TableTennisPlayer player1("Chuck", "Blizzard", true);
	TableTennisPlayer player2("Tara", "Boomdea", false);

	player1.Name();	
	if (player1.HasTable())
		cout << ": has a table" << endl;
	else
		cout << ": has no table" << endl;

	player2.Name();
	if (player2.HasTable())
		cout << ": has a table" << endl;
	else
		cout << ": has no table" << endl;
	*/
	
	TableTennisPlayer player1("Tara", "Boomdea", false);
	RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
	
	rplayer1.Name();
	if (rplayer1.HasTable())
		cout << ": has a table" << endl; 
	else
		cout << ": has no table" << endl;

	player1.Name();
	if ((player1.HasTable()))
		cout << ": has a table" << endl;
	else
		cout << ": has no table" << endl;
	
	cout << "Name: ";
	rplayer1.Name();
	cout << "; Rating: " << rplayer1.Rating() << endl;
	
	show(player1);
	show(rplayer1);
	
	show1(&player1);
	show1(&rplayer1);

	RatedPlayer rplayer2(1212, player1);
	TableTennisPlayer player3(rplayer2);
	player3.Name();
	cout << "Name: ";
	rplayer2.Name();
	cout << "; Rating: " << rplayer2.Rating() << endl;
	
	return 0;
}
