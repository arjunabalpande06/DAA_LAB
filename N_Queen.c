#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int solutionCount = 0;


bool isSafe(int board[MAX][MAX], int row, int col, int n) {
	int i, j;


	for (i = 0; i < row; i++)
		if (board[i][col])
			return false;


	for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if  (board[i][j])
			return false;


	for (i = row, j = col; i >= 0 && j < n;i--, j++)
		if (board[i][j])
			return false;

	return true;
}

void solveNQ(int board[MAX][MAX], int row, int n) {
	if (row == n) {
		solutionCount++;
		return;
	}

	for (int col = 0; col < n; col++) {
		if (isSafe(board, row, col, n)) {
			board[row][col] = 1;
			solveNQ(board, row + 1, n);
			board[row][col] = 0;
		}
	}
}

int nQueen(int n) {
	int board[MAX][MAX] = {0};
	solutionCount = 0;
	solveNQ(board, 0, n);
	return solutionCount;
}

int main() {
	int n;
	scanf("%d", &n);
	printf("%d\n", nQueen(n));
	return 0;
}
