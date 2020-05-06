#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum PieceColor {BLACK, WHITE};
struct PiecePos
{
	size_t x;
	size_t y;
	PiecePos(int xval, int yval) : x(xval), y(yval) {}
	PiecePos(const PiecePos& p) : x(p.x), y(p.y) {}
};

class Piece
{
	public:
		Piece() : _color(BLACK), _pos(0, 0) {}
		Piece(const PieceColor& c, const PiecePos& p) : _color(c), _pos(p) {}
		virtual ~Piece() {}
		virtual void draw() {
			if (_color == BLACK)
				cout << "draw black piece in place(" << _pos.x << ", " << _pos.y << ")" << endl;
			else
				cout << "draw white piece in place(" << _pos.x << ", " << _pos.y << ")" << endl;
		}
		
	private:
		PieceColor _color;
		PiecePos   _pos;
};

class PieceBoard
{
	public:
		PieceBoard(const string& black_name, const string& white_name) : _black_name(black_name),
			_white_name(white_name) {}

		~PieceBoard()
		{
			clear();
		}

		void clear()
		{
			for (vector<Piece*>::iterator it=_vec_piece.begin(); it!=_vec_piece.end(); it++)
				delete (*it);
		}

		void set_piece(const PieceColor& c, const PiecePos p)
		{
			Piece* ptr = new Piece(c, p);	
			ptr->draw();
			_vec_piece.push_back(ptr);
		}

	private:
		vector<Piece*> _vec_piece;
		string _black_name;
		string _white_name;
};

int main()
{
	PieceBoard pieceBoard("A","B");  
	pieceBoard.set_piece(BLACK, PiecePos(4, 4));  
	pieceBoard.set_piece(WHITE, PiecePos(4, 16));  
	pieceBoard.set_piece(BLACK, PiecePos(16, 4));  
	pieceBoard.set_piece(WHITE, PiecePos(16, 16));  

	return 0;
}
