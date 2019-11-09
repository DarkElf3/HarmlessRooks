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
struct TRookInfo {
	int PlacedRooks;
	int FreeLinesUsed;
};

class CHarmlessRooks {
private:
	vector< vector<int> > Board;

	void PlaceRook(int X, int Y);
	void DeleteRook(int X, int Y);
	bool CheckForUndoubted(int X, int Y);
	bool CheckHorizontal(int X, int Y);
	bool CheckVertical(int X, int Y);
	int FreeLinesOccupied(int X, int Y);
	void FindAndPlaceUndoubted(int *UndoubtedX, int *UndoubtedY, TRookInfo &Undoubted);
	void FindAndPlaceUndoubtedTwoPairs(int *UndoubtedX, int *UndoubtedY, TRookInfo &Undoubted);
	int SearchForPair(int X, int Y1, int Y2);
	bool CheckPair(int X, int Y1, int Y2);
public:
	int BoardSize;
	vector<int> FreeRow, FreeCol, HenceRow, HenceCol;
	void GetData();
	void ShowBoard();
	TRookInfo PlaceRooks(int X, int Y);
	int CheckAndPlaceUndoubtedRooks();
};

void CHarmlessRooks::GetData()
{
	cin >> BoardSize; cin.ignore();
	Board.resize(BoardSize);
	for (auto& BoardStr : Board) {
		BoardStr.resize(BoardSize, 0);
		string Row;
		getline(cin, Row);
		for (int i = 0; i < BoardSize; i++) {
			if (Row[i] == 'X')
				BoardStr[i] = INT_MAX;
		}
	}
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			if (Board[i][j] == INT_MAX) {
				HenceRow.push_back(i);
				break;
			}
			if (j == BoardSize - 1)
				FreeRow.push_back(i);
		}
	}
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			if (Board[j][i] == INT_MAX) {
				HenceCol.push_back(i);
				break;
			}
			if (j == BoardSize - 1)
				FreeCol.push_back(i);
		}
	}
}

void CHarmlessRooks::ShowBoard()
{
	for (auto& BoardStr : Board) {
		cerr << endl;
		for (int i : BoardStr) {
			char Symbol;
			if ((i == INT_MAX) || (i == 0)) {
				Symbol = (i == INT_MAX) ? 'X' : '.';
				cerr << Symbol << ' ';
			}
			else {
				cerr << i;
				if (i <= 9) cerr << ' ';
			}
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
	//	cerr << "Add " << X << ' ' << Y << endl;
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
	//	cerr << "Del " << X << ' ' << Y << endl;
}

int CHarmlessRooks::FreeLinesOccupied(int X, int Y)
{
	int Result = 0;
	for (int i : FreeRow)
	{
		if (i == X) {
			Result++;
			break;
		}
	}
	for (int i : FreeCol)
	{
		if (i == Y) {
			Result++;
			break;
		}
	}
	return Result;
}

void CHarmlessRooks::FindAndPlaceUndoubted(int *UndoubtedX, int *UndoubtedY, TRookInfo &Undoubted)
{
	
		for (int i = 0; i < BoardSize; i++)
		{
			for (int j = 0; j < BoardSize; j++)
			{
				if (Board[i][j] == 0) {
					if (CheckForUndoubted(i, j)) {
						PlaceRook(i, j);
						UndoubtedX[Undoubted.PlacedRooks] = i;
						UndoubtedY[Undoubted.PlacedRooks] = j;
						Undoubted.FreeLinesUsed += FreeLinesOccupied(i, j);
						Undoubted.PlacedRooks++;
					}
				}
			}
		}
	
}

bool CHarmlessRooks::CheckPair(int X, int Y1, int Y2)
{
	for (int j = Y1 - 1; j >= 0; j--)
	{
		if (Board[X][j] == 0) return false;
		if (Board[X][j] == INT_MAX) break;
	}
	for (int j = Y1 + 1; j < Y2; j++)
	{
		if (Board[X][j] == 0) return false;
	}
	for (int j = Y2 + 1; j < BoardSize; j++)
	{
		if (Board[X][j] == 0) return false;
		if (Board[X][j] == INT_MAX) break;
	}
	return true;
}

int CHarmlessRooks::SearchForPair(int X, int Y1, int Y2)
{
	for (int i = 0; i < BoardSize; i++) 
	{
		if (i == X) continue;
		if ((Board[i][Y1] == 0) && (Board[i][Y2] == 0)) {
			if (CheckPair(i, Y1, Y2))
				return i;
		}
	}
	return -1;
}

void CHarmlessRooks::FindAndPlaceUndoubtedTwoPairs(int *UndoubtedX, int *UndoubtedY, TRookInfo &Undoubted)
{
	for (int i = 0; i < BoardSize; i++)
	{
		for (int j = 0; j < BoardSize; j++)
		{
			if (Board[i][j] == 0) {
				int k = j + 1;
				bool TwoFound = false;
				bool ThreeOrMore = false;
				int Pair;
				while (k < BoardSize)
				{
					if (Board[i][k] == 0) {
						if (TwoFound) {
							ThreeOrMore = true;
						} else {
							TwoFound = true;
							Pair = k;
						}
					}
					if (Board[i][k] == INT_MAX) {
						break;
					}
					k++;
				}
				if (!ThreeOrMore && TwoFound) {
					int PairRow = SearchForPair(i, j, Pair);
					if (PairRow >= 0) {
						PlaceRook(i, j);
						UndoubtedX[Undoubted.PlacedRooks] = i;
						UndoubtedY[Undoubted.PlacedRooks] = j;
						Undoubted.FreeLinesUsed += FreeLinesOccupied(i, j);
						Undoubted.PlacedRooks++;
						PlaceRook(PairRow, Pair);
						UndoubtedX[Undoubted.PlacedRooks] = PairRow;
						UndoubtedY[Undoubted.PlacedRooks] = Pair;
						Undoubted.FreeLinesUsed += FreeLinesOccupied(i, j);
						Undoubted.PlacedRooks++;
//						ShowBoard(); cin >> PairRow;
					}
				}
				j = k;
			}
		}
	}

}

TRookInfo CHarmlessRooks::PlaceRooks(int X, int Y)
{
	TRookInfo Max = { 0, 0 };
	if (Board[X][Y] != 0) return Max;

	PlaceRook(X, Y);

	TRookInfo Undoubted = { 0, 0 };
	int UndoubtedX[100];
	int UndoubtedY[100];

	int  PlacedRooks;
	do {
		PlacedRooks = Undoubted.PlacedRooks;
		FindAndPlaceUndoubted(UndoubtedX, UndoubtedY, Undoubted);
		FindAndPlaceUndoubtedTwoPairs(UndoubtedX, UndoubtedY, Undoubted);
	} while (PlacedRooks < Undoubted.PlacedRooks);

	//	for (int i = 0; i < BoardSize; i++)
	for (int i : HenceRow)
	{
		//		for (int j = 0; j < BoardSize; j++)
		for (int j : HenceCol)
		{
			auto Cur = PlaceRooks(i, j);
			if (Cur.PlacedRooks > Max.PlacedRooks) Max = Cur;
		}
	}
	//	Max.PlacedRooks += Undoubted.PlacedRooks;
	//	Max.RooksOnFreeLines += Undoubted.RooksOnFreeLines;

	int Maximum = FreeRow.size() + FreeCol.size() - Max.FreeLinesUsed - Undoubted.FreeLinesUsed;

	bool MaxFound = (Max.PlacedRooks < Maximum);

	for (int i : FreeRow)
	{
		if (MaxFound) break;
		for (int j : HenceCol)
		{
			auto Cur = PlaceRooks(i, j);
			if (Cur.PlacedRooks > Max.PlacedRooks) Max = Cur;
			if (Cur.PlacedRooks == Maximum) {
				MaxFound = true;
				break;
			}
		}
	}

	for (int i : HenceRow)
	{
		if (MaxFound) break;
		for (int j : FreeCol)
		{
			auto Cur = PlaceRooks(i, j);
			if (Cur.PlacedRooks > Max.PlacedRooks) Max = Cur;
			if (Cur.PlacedRooks == Maximum) {
				MaxFound = true;
				break;
			}
		}
	}

	for (int i : FreeRow) // TODO çàìåíèòü ìàêñèìàëüíîå êîëè÷åñòâî ñòðîê èëè ñòîëáöîâ
	{
		if (MaxFound) break;
		for (int j : FreeCol)
		{
			auto Cur = PlaceRooks(i, j);
			if (Cur.PlacedRooks > Max.PlacedRooks) Max = Cur;
			if (Cur.PlacedRooks == Maximum) {
				MaxFound = true;
				break;
			}
		}
	}


	if (Undoubted.PlacedRooks > 0) {
		for (int i = (Undoubted.PlacedRooks - 1); i >= 0; i--) {
			DeleteRook(UndoubtedX[i], UndoubtedY[i]);
		}
	}

	DeleteRook(X, Y);

	Max.PlacedRooks += Undoubted.PlacedRooks;
	Max.FreeLinesUsed += Undoubted.FreeLinesUsed;
	Max.PlacedRooks++;
	Max.FreeLinesUsed += FreeLinesOccupied(X, Y);
	return Max;
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
	if (CheckHorizontal(X, Y)) return true;
	return CheckVertical(X, Y);
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
					for (size_t k = 0; k < FreeRow.size(); k++)
					{
						if (FreeRow[k] == i) {
							FreeRow.erase(FreeRow.begin() + k);
							break;
						}
					}
					for (size_t k = 0; k < FreeCol.size(); k++)
					{
						if (FreeCol[k] == j) {
							FreeCol.erase(FreeCol.begin() + k);
							break;
						}
					}
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
//	HarmlessRooks.ShowBoard();
	int Max = 0;
	//	for (int i = 0; i < HarmlessRooks.BoardSize; i++)
	for (int i : HarmlessRooks.HenceRow)
	{
		//		for (int j = 0; j < HarmlessRooks.BoardSize; j++)
		for (int j : HarmlessRooks.HenceCol)
		{
			auto Cur = HarmlessRooks.PlaceRooks(i, j);
			cerr << Cur.PlacedRooks + Undoubted << ' ';
			if (Cur.PlacedRooks > Max) Max = Cur.PlacedRooks;
		}
		cerr << endl;
	}
	cout << Max + Undoubted;
	HarmlessRooks.ShowBoard();
	cin >> Max;
}