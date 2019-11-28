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
	const int HR_LINE_NOT_FOUND = -1;
	vector< vector<int> > Board;
	void PlaceRook(int X, int Y);
	void DeleteRook(int X, int Y);
	bool CheckForUndoubted(int X, int Y);
	bool CheckHorizontal(int X, int Y);
	bool CheckVertical(int X, int Y);
	int CheckTripleHorizontal(int X, int Y1, int Y2, int Y3);
	int CheckTripleVertical(int Y, int X1, int X2, int X3);
	bool CheckThreeVertical(int Y, int X1, int X2, int& X3);
	bool CheckThreeHorizontal(int X, int Y1, int Y2, int& Y3);
	void FindAndPlaceUndoubted(int *UndoubtedX, int *UndoubtedY, int &Undoubted);
	int FindAndPlaceUndoubted();
	void FindAndPlaceTwoPairsHorizontal(int *UndoubtedX, int *UndoubtedY, int &Undoubted);
	void FindAndPlaceTwoPairsVertical(int *UndoubtedX, int *UndoubtedY, int &Undoubted);
	int FindAndPlaceTwoPairsVertical();
	int FindAndPlaceTwoPairsHorizontal();
	int FindAndPlaceThreeMatchingVertical();
	int FindAndPlaceThreeMatchingHorizontal();
	int FindAndPlaceTripleHorizontal();
	int FindAndPlaceTripleVertical();
	int SearchForPairRow(int X, int Y1, int Y2);
	void PlaceThreeRooks(int X1, int X2, int X3, int Y1, int Y2, int Y3);
	int SearchForMatchingThreeRows(int X, int Y1, int Y2, int Y3);
	int SearchForMatchingThreeCols(int Y, int X1, int X2, int X3);
	int SearchForThreeMatchingTwoRow(int X, int Y1, int Y2);
	int SearchForThreeMatchingTwoCol(int Y, int X1, int X2);
	int SearchForThirdRow(int X, int Y1, int Y2, int Y3);
	int SearchForThirdCol(int Y, int X1, int X2, int X3);
	int SearchForPairCol(int Y, int X1, int X2);
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
	if (Y1 > Y2) { 
		Y1 ^= Y2;
		Y2 ^= Y1;
		Y1 ^= Y2;
	}
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
	if (X1 > X2) { 
		X1 ^= X2;
		X2 ^= X1;
		X1 ^= X2;
	}
	for (int i = X1 - 1; i >= 0; i--) {
		if (Board[i][Y] == 0) return false;
		if (Board[i][Y] == INT_MAX) break;
	}
	for (int i = X1 + 1; i < X2; i++) {
		if (Board[i][Y] == 0) return false;
	}
	for (int i = X2 + 1; i < BoardSize; i++) {
		if (Board[i][Y] == 0) return false;
		if (Board[i][Y] == INT_MAX) break;
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
	return HR_LINE_NOT_FOUND;
}

int CHarmlessRooks::SearchForPairCol(int Y, int X1, int X2)
{
	for (int j = Y + 1; j < BoardSize; j++) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if ((Board[X1][j] == 0) && (Board[X2][j] == 0)) {
			if (CheckPairVertical(j, X1, X2))
				return j;
		}
	}
	for (int j = Y - 1; j >= 0; j--) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if ((Board[X1][j] == 0) && (Board[X2][j] == 0)) {
			if (CheckPairVertical(j, X1, X2))
				return j;
		}
	}
	return HR_LINE_NOT_FOUND;
}

bool CHarmlessRooks::CheckThreeVertical(int Y, int X1, int X2, int& X3)
{
	int FreeFields = 0;
	for (int i = X1 - 1; i >= 0; i--) {
		if (Board[i][Y] == 0) {
			FreeFields++;
			X3 = i;
		}
		if (Board[i][Y] == INT_MAX) break;
	}
	for (int i = X1 + 1; i < X2; i++) {
		if (Board[i][Y] == INT_MAX) return false;
		if (Board[i][Y] == 0) {
			FreeFields++;
			X3 = i;
		}
	}
	for (int i = X2 + 1; i < BoardSize; i++) {
		if (Board[i][Y] == 0) {
			FreeFields++;
			X3 = i;
		}
		if (Board[i][Y] == INT_MAX) break;
	}
	return (FreeFields == 1);
}

int CHarmlessRooks::CheckTripleVertical(int Y, int X1, int X2, int X3)
{
	int FreeFields = 0;
	if (Board[X1][Y] == 0) FreeFields++;
	if (Board[X2][Y] == 0) FreeFields++;
	if (Board[X3][Y] == 0) FreeFields++;
	if ((FreeFields == 2) || (FreeFields == 3)) {
		for (int i = X1 - 1; i >= 0; i--) {
			if (Board[i][Y] == 0) return 0;
			if (Board[i][Y] == INT_MAX) break;
		}
		for (int i = X3 + 1; i < BoardSize; i++) {
			if (Board[i][Y] == 0) return 0;
			if (Board[i][Y] == INT_MAX) break;
		}
		int FreeFieldsFromX1toX3 = 0;
		for (int i = X1; i <= X3; i++) {
			if (Board[i][Y] == INT_MAX) return 0; // уточнить
			if (Board[i][Y] == 0)
				FreeFieldsFromX1toX3++;
			if (FreeFieldsFromX1toX3 > FreeFields) return 0;
		}
	}
	return FreeFields;
}

int CHarmlessRooks::SearchForThirdCol(int Y, int X1, int X2, int X3)
{
	int FreeFields;
	int p1 = X1, p2 = X2, p3 = X3;
	if (X3 < X1) {
		p1 = X3;
		p2 = X1;
		p3 = X2;
	}
	if ((X3 > X1) && (X3 < X2)) {
		p2 = X3;
		p3 = X2;
	}
	for (int j = Y + 1; j < BoardSize; j++) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if (Board[X3][j] == INT_MAX) break;
		FreeFields = CheckTripleVertical(j, p1, p2, p3);
		if (FreeFields == 3) {
			return j;
		}
	}
	for (int j = Y - 1; j >= 0; j--) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if (Board[X3][j] == INT_MAX) break;
		FreeFields = CheckTripleVertical(j, p1, p2, p3);
		if (FreeFields == 3) {
			return j;
		}
	}
	return HR_LINE_NOT_FOUND;
}

int CHarmlessRooks::SearchForThreeMatchingTwoCol(int Y, int X1, int X2)
{
	int X3;
	for (int j = Y + 1; j < BoardSize; j++) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if ((Board[X1][j] == 0) && (Board[X2][j] == 0)) {
			if (CheckThreeVertical(j, X1, X2, X3)) {
				int ThirdCol = SearchForPairCol(j, X1, X3);
				if (ThirdCol != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X1, X2, X3, Y, j, ThirdCol);
					return 3;
				}
				ThirdCol = SearchForPairCol(j, X2, X3);
				if (ThirdCol != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X1, X2, X3, Y, j, ThirdCol);
					return 3;
				}
				ThirdCol = SearchForThirdCol(j, X1, X2, X3);
				if (ThirdCol != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X1, X2, X3, Y, j, ThirdCol);
					return 3;
				}
			}
		}
	}
	for (int j = Y - 1; j >= 0; j--) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if ((Board[X1][j] == 0) && (Board[X2][j] == 0)) {
			if (CheckThreeVertical(j, X1, X2, X3)) {
				int ThirdCol = SearchForPairCol(j, X1, X3);
				if (ThirdCol != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X1, X2, X3, Y, j, ThirdCol);
					return 3;
				}
				ThirdCol = SearchForPairCol(j, X2, X3);
				if (ThirdCol != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X1, X2, X3, Y, j, ThirdCol);
					return 3;
				}
				ThirdCol = SearchForThirdCol(j, X1, X2, X3);
				if (ThirdCol != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X1, X2, X3, Y, j, ThirdCol);
					return 3;
				}
			}
		}
	}
	return 0;
}

int CHarmlessRooks::FindAndPlaceThreeMatchingVertical()
{
	int NewRooks = 0;
	for (int j = 0; j < BoardSize; j++) {
		for (int i = 0; i < BoardSize; i++) {
			if (Board[i][j] == 0) {
				int k = i + 1;
				int FreeFields = 0;
				int Pair;
				while (k < BoardSize) {
					if (Board[k][j] == 0) {
						FreeFields++;
						if (FreeFields == 1) {
							Pair = k;
						}
					}
					if (Board[k][j] == INT_MAX) {
						break;
					}
					k++;
				}
				if (FreeFields == 1) {
						NewRooks += SearchForThreeMatchingTwoCol(j, i, Pair);
				}
				i = k;
			}
		}
	}
	return NewRooks;
}

int CHarmlessRooks::FindAndPlaceTwoPairsVertical()
{
	int NewRooks = 0;
	for (int j = 0; j < BoardSize; j++) {
		for (int i = 0; i < BoardSize; i++) {
			if (Board[i][j] == 0) {
				int k = i + 1;
				int FreeFields = 0;
				int Pair;
				while (k < BoardSize) {
					if (Board[k][j] == 0) {
						FreeFields++;
						if (FreeFields == 1) {
							Pair = k;
						}
					}
					if (Board[k][j] == INT_MAX) {
						break;
					}
					k++;
				}
				if (FreeFields == 1) {
					int PairCol = SearchForPairCol(j, i, Pair);
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

int CHarmlessRooks::CheckTripleHorizontal(int X, int Y1, int Y2, int Y3)
{
	int FreeFields = 0;
	if (Board[X][Y1] == 0) FreeFields++;
	if (Board[X][Y2] == 0) FreeFields++;
	if (Board[X][Y3] == 0) FreeFields++;
	if ((FreeFields == 2) || (FreeFields == 3)) {
		for (int j = Y1 - 1; j >= 0; j--) {
			if (Board[X][j] == 0) return 0;
			if (Board[X][j] == INT_MAX) break;
		}
		for (int j = Y3 + 1; j < BoardSize; j++) {
			if (Board[X][j] == 0) return 0;
			if (Board[X][j] == INT_MAX) break;
		}
		int FreeFieldsFromY1toY3 = 0;
		for (int j = Y1; j <= Y3; j++) {
			if (Board[X][j] == INT_MAX) return 0; // уточнить
			if (Board[X][j] == 0) 
				FreeFieldsFromY1toY3++;
			if (FreeFieldsFromY1toY3 > FreeFields) return 0;
		}
	}
	return FreeFields;
}

void CHarmlessRooks::PlaceThreeRooks(int X1, int X2, int X3, int Y1, int Y2, int Y3)
{
	PlaceRook(X1, Y1);
	PlaceRook(X2, Y2);
	PlaceRook(X3, Y3);
}

int CHarmlessRooks::SearchForMatchingThreeRows(int X, int Y1, int Y2, int Y3)
{
	int FirstLine = -1;
	int FreeFields;
	for (int i = X + 1; i < BoardSize; i++) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if (Board[i][Y3] == INT_MAX) break;
		FreeFields = CheckTripleHorizontal(i, Y1, Y2, Y3);
		if (FreeFields > 1) {
			if (FirstLine == -1) {
				FirstLine = i;
			} else {
				PlaceThreeRooks(X, i, FirstLine, Y1, Y2, Y3);
				return 3;
			}
		}
	}
	for (int i = X - 1; i >= 0; i--) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if (Board[i][Y3] == INT_MAX) break;
		FreeFields = CheckTripleHorizontal(i, Y1, Y2, Y3);
		if (FreeFields > 1) {
			if (FirstLine == -1) {
				FirstLine = i;
			}
			else {
				PlaceThreeRooks(X, i, FirstLine, Y1, Y2, Y3);
				return 3;
			}
		}
	}
	return 0;
}

bool CHarmlessRooks::CheckThreeHorizontal(int X, int Y1, int Y2, int& Y3)
{
	int FreeFields = 0;
	for (int j = Y1 - 1; j >= 0; j--) {
		if (Board[X][j] == 0) {
			FreeFields++;
			Y3 = j;
		}
		if (Board[X][j] == INT_MAX) break;
	}
	for (int j = Y1 + 1; j < Y2; j++) {
		if (Board[X][j] == INT_MAX) return false;
		if (Board[X][j] == 0) {
			FreeFields++;
			Y3 = j;
		}
	}
	for (int j = Y2 + 1; j < BoardSize; j++) {
		if (Board[X][j] == 0) {
			FreeFields++;
			Y3 = j;
		}
		if (Board[X][j] == INT_MAX) break;
	}
	return (FreeFields == 1);
}

int CHarmlessRooks::SearchForThirdRow(int X, int Y1, int Y2, int Y3)
{
	int FreeFields;
	int p1 = Y1, p2 = Y2, p3 = Y3;
	if (Y3 < Y1) {
		p1 = Y3;
		p2 = Y1;
		p3 = Y2;
	}
	if ((Y3 > Y1) && (Y3 < Y2)) {
		p2 = Y3;
		p3 = Y2;
	}
	for (int i = X + 1; i < BoardSize; i++) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if (Board[i][Y3] == INT_MAX) break;
		FreeFields = CheckTripleHorizontal(i, p1, p2, p3);
		if (FreeFields == 3) {
			return i;
		}
	}
	for (int i = X - 1; i >= 0; i--) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if (Board[i][Y3] == INT_MAX) break;
		FreeFields = CheckTripleHorizontal(i, p1, p2, p3);
		if (FreeFields == 3) {
			return i;
		}
	}
	return HR_LINE_NOT_FOUND;
}

int CHarmlessRooks::SearchForThreeMatchingTwoRow(int X, int Y1, int Y2)
{
	int Y3;
	for (int i = X + 1; i < BoardSize; i++) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if ((Board[i][Y1] == 0) && (Board[i][Y2] == 0)) {
			if (CheckThreeHorizontal(i, Y1, Y2, Y3)) {
				int ThirdRow = SearchForPairRow(i, Y1, Y3);
				if (ThirdRow != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X, i, ThirdRow, Y1, Y2, Y3);
					return 3;
				}
				ThirdRow = SearchForPairRow(i, Y2, Y3);
				if (ThirdRow != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X, i, ThirdRow, Y1, Y2, Y3);
					return 3;
				}
				ThirdRow = SearchForThirdRow(i, Y1, Y2, Y3);
				if (ThirdRow != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X, i, ThirdRow, Y1, Y2, Y3);
					return 3;
				}
			}
		}
	}
	for (int i = X - 1; i >= 0; i--) {
		if (Board[i][Y1] == INT_MAX) break;
		if (Board[i][Y2] == INT_MAX) break;
		if ((Board[i][Y1] == 0) && (Board[i][Y2] == 0)) {
			if (CheckThreeHorizontal(i, Y1, Y2, Y3)) {
				int ThirdRow = SearchForPairRow(i, Y1, Y3);
				if (ThirdRow != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X, i, ThirdRow, Y1, Y2, Y3);
					return 3;
				}
				ThirdRow = SearchForPairRow(i, Y2, Y3);
				if (ThirdRow != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X, i, ThirdRow, Y1, Y2, Y3);
					return 3;
				}
				ThirdRow = SearchForThirdRow(i, Y1, Y2, Y3);
				if (ThirdRow != HR_LINE_NOT_FOUND) {
					PlaceThreeRooks(X, i, ThirdRow, Y1, Y2, Y3);
					return 3;
				}
			}
		}
	}
	return 0;
}

int CHarmlessRooks::FindAndPlaceThreeMatchingHorizontal()
{
	int NewRooks = 0;
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (Board[i][j] == 0) {
				int k = j + 1;
				int FreeFields = 0;
				int Pair;
				while (k < BoardSize) {
					if (Board[i][k] == 0) {
						FreeFields++;
						if (FreeFields == 1) {
							Pair = k;
						}
					}
					if (Board[i][k] == INT_MAX) {
						break;
					}
					k++;
				}
				if (FreeFields == 1) {
					NewRooks += SearchForThreeMatchingTwoRow(i, j, Pair);
				}
				j = k;
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
				int FreeFields = 0;
				int Pair;
				while (k < BoardSize) {
					if (Board[i][k] == 0) {
						FreeFields++;
						if (FreeFields == 1) {
							Pair = k;
						}
					}
					if (Board[i][k] == INT_MAX) {
						break;
					}
					k++;
				}
				if (FreeFields == 1) {
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

int CHarmlessRooks::SearchForMatchingThreeCols(int Y, int X1, int X2, int X3)
{
	int FirstLine = -1;
	int FreeFields;
	for (int j = Y + 1; j < BoardSize; j++) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if (Board[X3][j] == INT_MAX) break;
		FreeFields = CheckTripleVertical(j, X1, X2, X3);
		if (FreeFields > 1) {
			if (FirstLine == -1) {
				FirstLine = j;
			}
			else {
				PlaceThreeRooks(X1, X2, X3, Y, j, FirstLine);
				return 3;
			}
		}
	}
	for (int j = Y - 1; j >= 0; j--) {
		if (Board[X1][j] == INT_MAX) break;
		if (Board[X2][j] == INT_MAX) break;
		if (Board[X3][j] == INT_MAX) break;
		FreeFields = CheckTripleVertical(j, X1, X2, X3);
		if (FreeFields > 1) {
			if (FirstLine == -1) {
				FirstLine = j;
			}
			else {
				PlaceThreeRooks(X1, X2, X3, Y, j, FirstLine);
				return 3;
			}
		}
	}
	return 0;
}

int CHarmlessRooks::FindAndPlaceTripleVertical()
{
	int NewRooks = 0;
	for (int j = 0; j < BoardSize; j++) {
		for (int i = 0; i < BoardSize; i++) {
			if (Board[i][j] == 0) {
				int k = i + 1;
				int FreeNeigbours = 0;
				int NeighbourRows[2];
				while (k < BoardSize) {
					if (Board[k][j] == 0) {
						FreeNeigbours++;
						if (FreeNeigbours == 1) {
							NeighbourRows[0] = k;
						}
						if (FreeNeigbours == 2) {
							NeighbourRows[1] = k;
						}
					}
					if (Board[k][j] == INT_MAX) {
						break;
					}
					k++;
				}
				if (FreeNeigbours == 2) {
					NewRooks += SearchForMatchingThreeCols(i, j, NeighbourRows[0], NeighbourRows[1]);
				}
				j = k;
			}
		}
	}
	return NewRooks;
}

int CHarmlessRooks::FindAndPlaceTripleHorizontal()
{
	int NewRooks = 0;
	for (int i = 0; i < BoardSize; i++) {
		for (int j = 0; j < BoardSize; j++) {
			if (Board[i][j] == 0) {
				int k = j + 1;
				int FreeNeigbours = 0;
				int NeighbourCols[2];
				while (k < BoardSize) {
					if (Board[i][k] == 0) {
						FreeNeigbours++;
						if (FreeNeigbours == 1) {
							NeighbourCols[0] = k;
						}
						if (FreeNeigbours == 2) {
							NeighbourCols[1] = k;
						}
					}
					if (Board[i][k] == INT_MAX) {
						break;
					}
					k++;
				}
				if (FreeNeigbours == 2) {
					NewRooks += SearchForMatchingThreeRows(i, j, NeighbourCols[0], NeighbourCols[1]);
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
					int PairCol = SearchForPairCol(j, i, Pair);
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
	int PrevRooks, NewRooks;
	int  PlacedRooks = 0;
	do {
		PrevRooks = PlacedRooks;
		do {
			NewRooks = FindAndPlaceUndoubted();
			PlacedRooks += NewRooks;
		} while (NewRooks != 0);
		do {
			NewRooks = FindAndPlaceTwoPairsHorizontal();
			PlacedRooks += NewRooks;
		} while (NewRooks != 0);
		do {
			NewRooks = FindAndPlaceTwoPairsVertical();
			PlacedRooks += NewRooks;
		} while (NewRooks != 0);
		PlacedRooks += FindAndPlaceThreeMatchingHorizontal();
		PlacedRooks += FindAndPlaceThreeMatchingVertical();
	} while (PlacedRooks != PrevRooks);
	do {
		PrevRooks = PlacedRooks;
//		PlacedRooks += FindAndPlaceTripleHorizontal();
//		PlacedRooks += FindAndPlaceTripleVertical();
	} while (PlacedRooks != PrevRooks);
	return PlacedRooks;
}

int main()
{
	CHarmlessRooks HarmlessRooks;
	HarmlessRooks.GetData();
	int Undoubted = HarmlessRooks.CheckAndPlaceUndoubtedRooks();
	HarmlessRooks.ShowCurBoard();
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
//	HarmlessRooks.ShowBoard();
	cin >> Max;
}
