#include <iostream>
#define MAX_STRING_SIZE 50
#define PLAYER1 '1'
#define PLAYER2 '2'
#define MIN -999
#define MAX 999

using namespace std;

const char genAllPosMov[] = { "GEN_ALL_POS_MOV" };
const char genAllPosMovCutIfGameOver[] = { "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER" };
const char solveGameState[] = { "SOLVE_GAME_STATE" };


bool comparison(const char A[], const char B[])
{
	int sizeA = 0;
	int sizeB = 0;
	while (A[sizeA] != '\0')
	{
		sizeA++;
	}
	while (A[sizeB] != '\0')
	{
		sizeB++;
	}
	if (sizeA != sizeB)
	{
		return false;
	}
	for (int i = 0; i < sizeA; i++)
	{
		if (A[i] != B[i])
		{
			return false;
		}
	}
	return true;
}

bool rowCrossed(char** board, int N, int M, int K)
{

	for (int i = 0; i < N; i++)
	{
		int counter1 = 0;
		int counter2 = 0;
		for (int j = 0; j < M; j++)
		{
			if (board[i][j] == PLAYER1)
				counter1++;
			else
				counter1 = 0;
			if (board[i][j] == PLAYER2)
				counter2++;
			else
				counter2 = 0;
			if (counter1 == K || counter2 == K)
				return true;
		}
	}
	return false;
}

bool columnCrossed(char** board, int N, int M, int K)
{

	for (int i = 0; i < M; i++)
	{
		int counter1 = 0;
		int counter2 = 0;
		for (int j = 0; j < N; j++)
		{
			if (board[j][i] == PLAYER1)
				counter1++;
			else
				counter1 = 0;
			if (board[j][i] == PLAYER2)
				counter2++;
			else
				counter2 = 0;
			if (counter1 == K || counter2 == K)
				return true;
		}
	}
	return false;
}

bool diagonalCrossedDownward(char** board, int N, int M, int K)
{
	for (int i = 0; i < N; i++)
	{
		int m = i;
		int j = 0;
		int counter1 = 0;
		int counter2 = 0;
		while (i < N && j < M)
		{
			if (board[i][j] == PLAYER1)
				counter1++;
			else
				counter1 = 0;
			if (board[i][j] == PLAYER2)
				counter2++;
			else
				counter2 = 0;
			if (counter1 == K || counter2 == K)
				return true;

			i++; j++;
		}
		i = m;
	}
	for (int j = 0; j < M; j++)
	{
		int m = j;
		int z = 0;
		int counter1 = 0;
		int counter2 = 0;
		while (z < N && j < M)
		{
			if (board[z][j] == PLAYER1)
				counter1++;
			else
				counter1 = 0;
			if (board[z][j] == PLAYER2)
				counter2++;
			else
				counter2 = 0;
			if (counter1 == K || counter2 == K)
				return true;
			z++; j++;
		}
		j = m;
	}
	return false;
}

bool diagonalCrossedUpward(char** board, int N, int M, int K)
{
	int j = M - 1;
	for (int i = 0; i < N - 1; i++)
	{
		int m = i;
		j = M - 1;
		int counter1 = 0;
		int counter2 = 0;
		while (i < N && j >= 0)
		{
			if (board[i][j] == PLAYER1)
				counter1++;
			else
				counter1 = 0;
			if (board[i][j] == PLAYER2)
				counter2++;
			else
				counter2 = 0;
			if (counter1 == K || counter2 == K)
				return true;
			i++; j--;
		}
		i = m;
	}
	for (j = M - 1; j >= 0; j--)
	{
		int m = j;
		int w = 0;
		int counter1 = 0;
		int counter2 = 0;
		while (w < N && j >= 0)
		{
			if (board[w][j] == PLAYER1)
				counter1++;
			else
				counter1 = 0;
			if (board[w][j] == PLAYER2)
				counter2++;
			else
				counter2 = 0;
			if (counter1 == K || counter2 == K)
				return true;

			w++; j--;
		}
		j = m;
	}
	return false;
}

bool fullGrid(char** board, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (board[i][j] == '0')
				return false;
		}
	}
	return true;
}

void showBoard(char** board, int N, int M)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void initializeBoard(char** board, int N, int M, int& counter)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
			if (board[i][j] == '0')
				counter++;
		}
	}
}

bool gameOver(char**& board, int N, int M, int K)
{
	return(rowCrossed(board, N, M, K) || columnCrossed(board, N, M, K) || diagonalCrossedDownward(board, N, M, K) || diagonalCrossedUpward(board, N, M, K));
}

void whoWon(int result)
{
	if (result == 1) cout << "FIRST_PLAYER_WINS" << endl;
	else if (result == -1) cout << "SECOND_PLAYER_WINS" << endl;
	else if (result == 0) cout << "BOTH_PLAYERS_TIE" << endl;
}

void showAllPositions(int N, int M, int K, char player)
{
	int counter = 0;
	char** board = new char* [N];
	for (int i = 0; i < N; i++)
		board[i] = new char[M];

	initializeBoard(board, N, M, counter);

	if (gameOver(board, N, M, K) || fullGrid(board, N, M))
	{
		cout << "0" << endl;
		delete[] board;
		return;
	}
	cout << counter << endl;
	for (int i = 0; i < N * M; i++)
	{
		int x = i / M;
		int y = i % M;
		if (x >= 0 && y >= 0 && x <= (N - 1) && y <= (M - 1))
		{
			if (board[x][y] == '0')
			{
				board[x][y] = player;
				showBoard(board, N, M);
				board[x][y] = '0';
			}
		}
	}
	delete[] board;
}

void showAllPositionsIfGameOver(int N, int M, int K, char player)
{
	int counter = 0;
	int x = 0; int y = 0;

	char** board = new char* [N];
	for (int i = 0; i < N; i++)
		board[i] = new char[M];

	initializeBoard(board, N, M, counter);

	if (gameOver(board, N, M, K) || fullGrid(board, N, M))
	{
		cout << "0" << endl;
		delete[] board;
		return;
	}
	for (int i = 0; i < N * M; i++)
	{
		x = i / M;
		y = i % M;
		if (x >= 0 && y >= 0 && x <= (N - 1) && y <= (M - 1))
		{
			if (board[x][y] == '0')
			{
				board[x][y] = player;
				if (gameOver(board, N, M, K) || fullGrid(board, N, M))
				{
					cout << "1" << endl;
					showBoard(board, N, M);
					delete[] board;
					return;
				}
				board[x][y] = '0';
			}
		}
	}
	cout << counter << endl;
	for (int i = 0; i < N * M; i++)
	{
		x = i / M;
		y = i % M;
		if (x >= 0 && y >= 0 && x <= (N - 1) && y <= (M - 1))
		{
			if (board[x][y] == '0')
			{
				board[x][y] = player;
				showBoard(board, N, M);
				board[x][y] = '0';
			}
		}
	}
	delete[] board;
}

int minimax(char** board, int depth, bool isMaximizing, int N, int M, int K, int alpha, int beta)
{
	int bestScore = 0;
	int score = 0;

	if (gameOver(board, N, M, K))
	{
		if (isMaximizing)
			return -1;
		else
			return 1;
	}
	else
	{
		if (fullGrid(board, N, M) == false)
		{
			if (isMaximizing)
			{
				bestScore = MIN;
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						if (board[i][j] == '0')
						{
							board[i][j] = PLAYER1;
							score = minimax(board, depth + 1, false, N, M, K, alpha, beta);
							board[i][j] = '0';
							if (score > bestScore)
								bestScore = score;
							if (bestScore > alpha)
								alpha = bestScore;
							if (beta <= alpha)
								break;
						}
					}
				}
				return bestScore;
			}
			else if (isMaximizing == false)
			{
				bestScore = MAX;
				for (int i = 0; i < N; i++)
				{
					for (int j = 0; j < M; j++)
					{
						if (board[i][j] == '0')
						{
							board[i][j] = PLAYER2;
							score = minimax(board, depth + 1, true, N, M, K, alpha, beta);
							board[i][j] = '0';
							if (score < bestScore)
								bestScore = score;
							if (bestScore < beta)
								beta = bestScore;
							if (beta <= alpha)
								break;
						}
					}
				}
				return bestScore;
			}
		}
	}
	return 0;
}

void playTicTacToe(char whoseTurn, int N, int M, int K)
{
	char** board = new char* [N];
	for (int i = 0; i < N; i++)
		board[i] = new char[M];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> board[i][j];
		}
	}

	if (gameOver(board, N, M, K) == false && fullGrid(board, N, M) == true)
	{
		cout << "BOTH_PLAYERS_TIE" << endl;
		delete[] board;
		return;
	}
	else
	{
		int result = 0;
		if (whoseTurn == PLAYER1)
			result = minimax(board, 0, true, N, M, K, MIN, MAX);
		else if (whoseTurn == PLAYER2)
			result = minimax(board, 0, false, N, M, K, MIN, MAX);

		whoWon(result);
		delete[] board;
		return;
	}
	delete[] board;
}

int main()
{
	char option[MAX_STRING_SIZE];
	int N, M, K;
	char player;
	while (cin >> option)
	{
		cin >> N >> M >> K >> player;
		if (comparison(option, genAllPosMov))
		{
			showAllPositions(N, M, K, player);
		}
		else if (comparison(option, genAllPosMovCutIfGameOver))
		{
			showAllPositionsIfGameOver(N, M, K, player);
		}
		else if (comparison(option, solveGameState))
		{
			playTicTacToe(player, N, M, K);
		}
	}
	return 0;
}
