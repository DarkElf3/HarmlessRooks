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
	void PlaceRook(int X, int Y);
	void DeleteRook(int X, int Y);
	bool CheckForUndoubted(int X, int Y);
	bool CheckHorizontal(int X, int Y);
	bool CheckVertical(int X, int Y);
	void FindAndPlaceUndoubted(int *UndoubtedX, int *UndoubtedY, int &Undoubted);
	int FindAndPlaceUndoubted();
	void FindAndPlaceTwoPairsHorizontal(int *UndoubtedX, int *UndoubtedY, int &Undoubted);
	void FindAndPlaceTwoPairsVertical(int *UndoubtedX, int *UndoubtedY, int &Undoubted);
	int FindAndPlaceTwoPairsVertical();
	int FindAndPlaceTwoPairsHorizontal();
	int SearchForPairRow(int X, int Y1, int Y2);
	int SearchForPairCol(int X1, int Y, int X2);
	bool CheckPairHorizontal(int X, int Y1, int Y2);
	bool CheckPairVertical(int Y, int X1, int X2);
public:
	int BoardSize;
	void GetData();
	void ShowBoard();
	void ShowCurBoard();
	int PlaceRooks(int X, int Y);
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
}

void CHarmlessRooks::ShowCurBoard()
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

void CHarmlessRooks::ShowBoard()
{
	for (auto& BoardStr : Board) {
		cerr << endl;
		for (int i : BoardStr) {
			char Symbol;
			Symbol = (i == INT_MAX) ? 'X' : '.';
			cerr << Symbol;
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

void CHarmlessRooks::FindAndPlaceUndoubted(int *UndoubtedX, int *UndoubtedY, int &Undoubted)
{
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (Board[i][j] == 0) {
				if (CheckForUndoubted(i, j)) {
					PlaceRook(i, j);
					UndoubtedX[Undoubted] = i;
					UndoubtedY[Undoubted] = j;
					Undoubted++;
				}
			}
		}
	}
}

int CHarmlessRooks::FindAndPlaceUndoubted()
{
	int PlacedRooks = 0;
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (Board[i][j] == 0) {
				if (CheckForUndoubted(i, j)) {
					PlaceRook(i, j);
					PlacedRooks++;
				}
			}
		}
	}
	return PlacedRooks;
}

bool CHarmlessRooks::CheckPairHorizontal(int X, int Y1, int Y2)
{
	for (int j = Y1 - 1; j >= 0; j--) {
		if (Board[X][j] == 0) return false;
		if (Board[X][j] == INT_MAX) break;
	}
	for (int j = Y1 + 1; j < Y2; j++) {
		if (Board[X][j] == 0) return false;
	}
	for (int j = Y2 + 1; j < BoardSize; j++) {
		if (Board[X][j] == 0) return false;
		if (Board[X][j] == INT_MAX) break;
	}
	return true;
}

bool CHarmlessRooks::CheckPairVertical(int Y, int X1, int X2)
{
	for (int j = X1 - 1; j >= 0; j--) {
		if (Board[j][Y] == 0) return false;
		if (Board[j][Y] == INT_MAX) break;
	}
	for (int j = X1 + 1; j < X2; j++) {
		if (Board[j][Y] == 0) return false;
	}
	for (int j = X2 + 1; j < BoardSize; j++) {
		if (Board[j][Y] == 0) return false;
		if (Board[j][Y] == INT_MAX) break;
	}
	return true;
}

int CHarmlessRooks::SearchForPairRow(int X, int Y1, int Y2)
{
	for (int i = X + 1; i < BoardSize; i++) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if ((Board[i][Y1] == 0) && (Board[i][Y2] == 0)) {
			if (CheckPairHorizontal(i, Y1, Y2))
				return i;
		}
	}
	for (int i = X - 1; i >= 0; i--) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if ((Board[i][Y1] == 0) && (Board[i][Y2] == 0)) {
			if (CheckPairHorizontal(i, Y1, Y2))
				return i;
		}
	}
	return -1;
}

int CHarmlessRooks::SearchForPairCol(int X1, int Y, int X2)
{
	for (int i = Y + 1; i < BoardSize; i++) {
		if (Board[X1][i] == INT_MAX) break;
		if (Board[X2][i] == INT_MAX) break;
		if ((Board[X1][i] == 0) && (Board[X2][i] == 0)) {
			if (CheckPairVertical(i, X1, X2))
				return i;
		}
	}
	for (int i = Y - 1; i >= 0; i--) {
		if (Board[X1][i] == INT_MAX) break;
		if (Board[X2][i] == INT_MAX) break;
		if ((Board[X1][i] == 0) && (Board[X2][i] == 0)) {
			if (CheckPairVertical(i, X1, X2))
				return i;
		}
	}
	return -1;
}

int CHarmlessRooks::FindAndPlaceTwoPairsVertical()
{
	int NewRooks = 0;
	for (int j = 0; j < BoardSize; j++) {
		for (int i = 0; i < BoardSize; i++) {
			if (Board[i][j] == 0) {
				int k = i + 1;
				bool TwoFound = false;
				bool ThreeOrMore = false;
				int Pair;
				while (k < BoardSize) {
					if (Board[k][j] == 0) {
						if (TwoFound) {
							ThreeOrMore = true;
						}
						else {
							TwoFound = true;
							Pair = k;
						}
					}
					if (Board[k][j] == INT_MAX) {
						break;
					}
					k++;
				}
				if (!ThreeOrMore && TwoFound) {
					int PairCol = SearchForPairCol(i, j, Pair);
					if (PairCol >= 0) {
						PlaceRook(i, j);
						NewRooks++;
						PlaceRook(Pair, PairCol);
						NewRooks++;
					}
				}
				i = k;
			}
		}
	}
	return NewRooks;
}

int CHarmlessRooks::FindAndPlaceTwoPairsHorizontal()
{
	int NewRooks = 0;
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (Board[i][j] == 0) {
				int k = j + 1;
				bool TwoFound = false;
				bool ThreeOrMore = false;
				int Pair;
				while (k < BoardSize) {
					if (Board[i][k] == 0) {
						if (TwoFound) {
							ThreeOrMore = true;
						}
						else {
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
					int PairRow = SearchForPairRow(i, j, Pair);
					if (PairRow >= 0) {
						PlaceRook(i, j);
						NewRooks++;
						PlaceRook(PairRow, Pair);
						NewRooks++;
					}
				}
				j = k;
			}
		}
	}
	return NewRooks;
}

void CHarmlessRooks::FindAndPlaceTwoPairsHorizontal(int *UndoubtedX, int *UndoubtedY, int &Undoubted)
{
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (Board[i][j] == 0) {
				int k = j + 1;
				bool TwoFound = false;
				bool ThreeOrMore = false;
				int Pair;
				while (k < BoardSize) {
					if (Board[i][k] == 0) {
						if (TwoFound) {
							ThreeOrMore = true;
						}
						else {
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
					int PairRow = SearchForPairRow(i, j, Pair);
					if (PairRow >= 0) {
//						ShowCurBoard();
						PlaceRook(i, j);
						UndoubtedX[Undoubted] = i;
						UndoubtedY[Undoubted] = j;
						Undoubted++;
						PlaceRook(PairRow, Pair);
						UndoubtedX[Undoubted] = PairRow;
						UndoubtedY[Undoubted] = Pair;
						Undoubted++;
					}
				}
				j = k;
			}
		}
	}

}

void CHarmlessRooks::FindAndPlaceTwoPairsVertical(int *UndoubtedX, int *UndoubtedY, int &Undoubted)
{
	for (int j = 0; j < BoardSize; j++) {
		for (int i = 0; i < BoardSize; i++) {
			if (Board[i][j] == 0) {
				int k = i + 1;
				bool TwoFound = false;
				bool ThreeOrMore = false;
				int Pair;
				while (k < BoardSize) {
					if (Board[k][j] == 0) {
						if (TwoFound) {
							ThreeOrMore = true;
						}
						else {
							TwoFound = true;
							Pair = k;
						}
					}
					if (Board[k][j] == INT_MAX) {
						break;
					}
					k++;
				}
				if (!ThreeOrMore && TwoFound) {
					int PairCol = SearchForPairCol(i, j, Pair);
					if (PairCol >= 0) {
						PlaceRook(i, j);
						UndoubtedX[Undoubted] = i;
						UndoubtedY[Undoubted] = j;
						Undoubted++;
						PlaceRook(Pair, PairCol);
						UndoubtedX[Undoubted] = Pair;
						UndoubtedY[Undoubted] = PairCol;
						Undoubted++;
					}
				}
				i = k;
			}
		}
	}

}

int CHarmlessRooks::PlaceRooks(int X, int Y)
{
	if (Board[X][Y] != 0) return 0;

	PlaceRook(X, Y);

	int Undoubted = 0;
	int UndoubtedX[100];
	int UndoubtedY[100];
	int  PlacedRooks;
	do {
		PlacedRooks = Undoubted;
		FindAndPlaceUndoubted(UndoubtedX, UndoubtedY, Undoubted);
		FindAndPlaceTwoPairsHorizontal(UndoubtedX, UndoubtedY, Undoubted);
		FindAndPlaceTwoPairsVertical(UndoubtedX, UndoubtedY, Undoubted);
	} while (PlacedRooks < Undoubted);

	int Max = 0;
	for (int i = 0; i < BoardSize; i++)	{
		for (int j = 0; j < BoardSize; j++)	{
			int Cur = PlaceRooks(i, j);
			if (Cur > Max) Max = Cur;
		}
	}

	if (Undoubted > 0) {
		for (int i = (Undoubted - 1); i >= 0; i--) {
			DeleteRook(UndoubtedX[i], UndoubtedY[i]);
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
	return CheckHorizontal(X, Y) || CheckVertical(X, Y);
}

int CHarmlessRooks::CheckAndPlaceUndoubtedRooks()
{
	int PrevRooks;
	int  PlacedRooks = 0;
	do {
		do {
			PrevRooks = PlacedRooks;
			PlacedRooks += FindAndPlaceUndoubted();
		} while (PlacedRooks != PrevRooks);
		PrevRooks = PlacedRooks;
		PlacedRooks += FindAndPlaceTwoPairsHorizontal();
		PlacedRooks += FindAndPlaceTwoPairsVertical();
	} while (PlacedRooks != PrevRooks);
	return PlacedRooks;
}

int main()
{
	CHarmlessRooks HarmlessRooks;
	HarmlessRooks.GetData();
	int Undoubted = HarmlessRooks.CheckAndPlaceUndoubtedRooks();
//	HarmlessRooks.ShowCurBoard();
	int Max = 0;
	for (int i = 0; i < HarmlessRooks.BoardSize; i++) {
		for (int j = 0; j < HarmlessRooks.BoardSize; j++) {
			int Cur = HarmlessRooks.PlaceRooks(i, j);
//			cerr << Cur + Undoubted << ' ';
			if (Cur > Max) Max = Cur;
		}
//		cerr << endl;
	}
	cout << Max + Undoubted;
	HarmlessRooks.ShowBoard();
	cin >> Max;
}
