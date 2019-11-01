#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "limits.h"

using namespace std;

/**
* Auto-generated code below aims at helping you parse
* the standard input according to the problem statement.
**/
class CHarmlessRooks {
private:
	vector< vector<int> > Board;
	vector <int> UndoubtedX;
	vector <int> UndoubtedY;
	void PlaceRook(int X, int Y);
	void DeleteRook(int X, int Y);
	bool CheckForUndoubted(int X, int Y);
	bool CheckHorizontal(int X, int Y);
	bool CheckVertical(int X, int Y);
public:
	int BoardSize;
	void GetData();
	void ShowBoard();
	int PlaceRooks(int X, int Y);
	int CheckAndPlaceUndoubtedRooks();
};

void CHarmlessRooks::GetData()
{
	cin >> BoardSize; cin.ignore();
	Board.resize(BoardSize);
//	UndoubtedX.resize(BoardSize * BoardSize / 2);
//	UndoubtedY.resize(BoardSize * BoardSize / 2);
	for (auto& BoardStr : Board) {
		BoardStr.resize(BoardSize, 0);
		string Row;
		getline(cin, Row);
		for (int i = 0; i < BoardSize; i++) {
			if (Row[i] == 'X')
				BoardStr[i] = INT_MAX;
		}
	}
}

void CHarmlessRooks::ShowBoard()
{
	for (auto& BoardStr : Board) {
		cerr << endl;
		for (int i : BoardStr) {
			char Symbol;
			Symbol = (i == INT_MAX) ? 'X' : '.';
			cerr << Symbol << ' ';
		}
	}
	cerr << endl;
}

void CHarmlessRooks::PlaceRook(int X, int Y)
{
	Board[X][Y]++;

	for (int i = 1; (i + X) < BoardSize; i++) {
		if (Board[X + i][Y] == INT_MAX) break;
		Board[X + i][Y]++;
	}

	for (int i = -1; (i + X) >= 0; i--) {
		if (Board[X + i][Y] == INT_MAX) break;
		Board[X + i][Y]++;
	}

	for (int i = 1; (i + Y) < BoardSize; i++) {
		if (Board[X][Y + i] == INT_MAX) break;
		Board[X][Y + i]++;
	}

	for (int i = -1; (i + Y) >= 0; i--) {
		if (Board[X][Y + i] == INT_MAX) break;
		Board[X][Y + i]++;
	}
}

void CHarmlessRooks::DeleteRook(int X, int Y)
{
	Board[X][Y]--;

	for (int i = 1; (i + X) < BoardSize; i++) {
		if (Board[X + i][Y] == INT_MAX) break;
		Board[X + i][Y]--;
	}

	for (int i = -1; (i + X) >= 0; i--) {
		if (Board[X + i][Y] == INT_MAX) break;
		Board[X + i][Y]--;
	}

	for (int i = 1; (i + Y) < BoardSize; i++) {
		if (Board[X][Y + i] == INT_MAX) break;
		Board[X][Y + i]--;
	}

	for (int i = -1; (i + Y) >= 0; i--) {
		if (Board[X][Y + i] == INT_MAX) break;
		Board[X][Y + i]--;
	}
}

int CHarmlessRooks::PlaceRooks(int X, int Y)
{
	if (Board[X][Y] != 0) return 0;

	PlaceRook(X, Y);

	int Undoubted = 0;
		
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			if (Board[i][j] == 0) {
				if (CheckForUndoubted(i, j)) {
					PlaceRook(i, j);
				//	UndoubtedX[Undoubted] = i;
				//	UndoubtedY[Undoubted] = j;
					UndoubtedX.push_back(i);
					UndoubtedY.push_back(j);
					Undoubted++;
				}
			}
		}
	}

	int Max = 0;
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			int Cur = PlaceRooks(i, j);
			if (Cur > Max) Max = Cur;
		}
	}

	if (Undoubted > 0) {
		for (int i = (Undoubted - 1); i >= 0; i--) {
			DeleteRook(UndoubtedX.back(), UndoubtedY.back());
			UndoubtedX.pop_back();
			UndoubtedY.pop_back();
		}
	}

	DeleteRook(X, Y);

	Max++;
	return Max + Undoubted;
}

bool CHarmlessRooks::CheckHorizontal(int X, int Y)
{
	for (int i = 1; (i + X) < BoardSize; i++) {
		if (Board[X + i][Y] == 0) return false;
		if (Board[X + i][Y] == INT_MAX) break;
	}
	for (int i = -1; (i + X) >= 0; i--) {
		if (Board[X + i][Y] == 0) return false;
		if (Board[X + i][Y] == INT_MAX) break;
	}
	return true;
}

bool CHarmlessRooks::CheckVertical(int X, int Y)
{
	for (int i = 1; (i + Y) < BoardSize; i++) {
		if (Board[X][Y + i] == 0) return false;
		if (Board[X][Y + i] == INT_MAX) break;
	}
	for (int i = -1; (i + Y) >= 0; i--) {
		if (Board[X][Y + i] == 0) return false;
		if (Board[X][Y + i] == INT_MAX) break;
	}
	return true;
}

bool CHarmlessRooks::CheckForUndoubted(int X, int Y)
{
	if (CheckHorizontal(X,Y)) return true;
	return CheckVertical(X,Y);
}

int CHarmlessRooks::CheckAndPlaceUndoubtedRooks()
{
	int PlacedRooks = 0;
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			if (Board[i][j] == 0) {
				if (CheckForUndoubted(i, j)) {
					PlaceRook(i, j);
					PlacedRooks++;
				}
			}
		}
	}
	if (PlacedRooks > 0) {
		int NewRooks;
		do {
			NewRooks = CheckAndPlaceUndoubtedRooks();
			PlacedRooks += NewRooks;
		} while (NewRooks != 0);
	}
	return PlacedRooks;
}

int main()
{
	CHarmlessRooks HarmlessRooks;
	HarmlessRooks.GetData();
	int Undoubted = HarmlessRooks.CheckAndPlaceUndoubtedRooks();
	int Max = 0;
	for (int i = 0; i < HarmlessRooks.BoardSize; i++)
	{
		for (int j = 0; j < HarmlessRooks.BoardSize; j++)
		{
			int Cur = HarmlessRooks.PlaceRooks(i, j);
			cerr << Cur + Undoubted << ' ';
			if (Cur > Max) Max = Cur;
		}
		cerr << endl;
	}
	cout << Max + Undoubted;
	HarmlessRooks.ShowBoard();
}

