//============================================================================
// Name        : 2048A.cpp
// Author      : David Huang
// Version     : 0.1
// Copyright   : Free
// Description : 2048 game in C++, Ansi-style
//============================================================================

//============================================================================
// TODO LIST:
// 1. Add random number generator.
// 2.
//
// NEW Action:
// 1. Random number generator is finished
// 2.
//============================================================================

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <iomanip>

#include <conio.h>

using namespace std;

struct Point{
	int x;
	int y;
};

vector<Point> pointQueue;

int board[4][4], moveFlag[4][4];
int randNum = 2;
int randX = 4, randY = 4;	//Coordinate
int score = 0;

random_device rd;
default_random_engine gen(time(NULL));
uniform_int_distribution <> d(1, 10);

//============================================================================
//Initialization.
//============================================================================
//Show board
void showBoard()
{
	cout << "*** Scores: " << score << " ***" << endl;
	cout << "---------------------" << endl;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			cout << board[i][j] << "    ";
		}
		cout << endl << endl;
	}
	cout << "---------------------" << endl;
}

//MoveFlag=1，no merge is permitted here. Initial value is 0.
void initMoveFlag()
{
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++){
			moveFlag[i][j] = 0;
		}
}

//Initialize all tiles' value to zero.
void initBoard()
{
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++){
			board[i][j] = 0;
		}
	initMoveFlag();
}

//============================================================================
//Check status.
//============================================================================
//To check whether there is an available move. 1 - Yes, 0 - No.
bool checkMove()
{
	bool canMove = 0;

	for(int m=0; m<4; m++)
			for(int n=0; n<4; n++)
				if(board[m][n] == 0){
					canMove =1;
					break;
				}

	if(canMove != 1){
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
			{
				if(j != 0)
				{
					if(board[i][j] == board[i][j-1])	//向上比较
					{
						canMove = 1;
						break;
					}
				}
				if(i != 0)
				{
					if(board[i][j] == board[i-1][j])	//向左比较
					{
						canMove = 1;
						break;
					}
				}
				if(j != 3)
				{
					if(board[i][j] == board[i][j+1])	//向右比较
					{
						canMove = 1;
						break;
					}
				}
				if(i != 3)
				{
					if(board[i][j] == board[i+1][j])	//向右比较
					{
						canMove = 1;
						break;
					}
				}
			}
	}

	return canMove;
}


//============================================================================
//Move up.
//============================================================================
int moveUpByCol(int row, int col)
{
	int m = 1;
	int n;
	int cur;
	int mergeFlag = 0;

	while(m <=3){
		n = m-1;
		cur = m;	//Current row value of the tile being moved
		while(n >=0){
			if(board[n][col] == 0){
				board[n][col] = board[cur][col];
				board[cur][col] = 0;
				cur = n;
				n = n-1;
				if(board[cur][col] != 0)
					mergeFlag = 1;
			}
			else if(board[n][col] == board[cur][col] && moveFlag[n][col] != 1){
				board[n][col] += board[cur][col];
				score += board[n][col];
				moveFlag[n][col] = 1;
				board[cur][col] = 0;
				mergeFlag = 1;
				break;
			}
			else
				break;
		}
		m = m+1;
	}
	return mergeFlag;
}

int moveUp()
{
	int mergeFlag = 0;

	initMoveFlag();

	for(int j=0; j<4; j++){
		if((board[0][j] +
				board[1][j] +
				board[2][j] +
				board[3][j]) != 0)
		if(moveUpByCol(0, j) == 1)
			mergeFlag = 1;
	}
	return mergeFlag;
}

//============================================================================
//Move down.
//============================================================================
int moveDownByCol(int row, int col)
{
	int m = 2;
	int n;
	int cur;
	int mergeFlag = 0;

	while(m >= 0){
		n = m+1;
		cur = m;	//Current row value of the tile being moved.
		while(n <= 3){
			if(board[n][col] == 0){
				board[n][col] = board[cur][col];
				board[cur][col] = 0;
				cur = n;
				n = n+1;
				if(board[cur][col] != 0)
					mergeFlag = 1;
			}
			else if(board[n][col] == board[cur][col] && moveFlag[n][col] != 1){
				board[n][col] += board[cur][col];
				score += board[n][col];
				moveFlag[n][col] = 1;
				board[cur][col] = 0;
				mergeFlag = 1;
				break;
			}
			else
				break;
		}
		m = m-1;
	}
	return mergeFlag;
}

int moveDown()
{
	int mergeFlag = 0;

	initMoveFlag();

	for(int j=3; j>=0; j--){
		if((board[0][j] +
				board[1][j] +
				board[2][j] +
				board[3][j]) != 0)
		if(moveDownByCol(3, j) == 1)
			mergeFlag = 1;
	}
	return mergeFlag;
}

//============================================================================
//Move left.
//============================================================================
int moveLeftByRow(int row, int col)
{
	int m = 1;
	int n;
	int cur;
	int mergeFlag = 0;

	while(m <=3){
		n = m-1;
		cur = m;	//Current column value of the tile being moved.
		while(n >=0){
			if(board[row][n] == 0){
				board[row][n] = board[row][cur];
				board[row][cur] = 0;
				cur = n;
				n = n-1;
				if(board[row][cur] != 0)
					mergeFlag = 1;
			}
			else if(board[row][n] == board[row][cur] && moveFlag[row][n] != 1){
				board[row][n] += board[row][cur];
				score += board[row][n];
				moveFlag[row][n] = 1;
				board[row][cur] = 0;
				mergeFlag = 1;
				break;
			}
			else
				break;
		}
		m = m+1;
	}
	return mergeFlag;
}

int moveLeft()
{
	int mergeFlag = 0;

	initMoveFlag();

	for(int i=0; i<4; i++){
		if((board[i][0] +
				board[i][1] +
				board[i][2] +
				board[i][3]) != 0)
		if(moveLeftByRow(i, 0) == 1)
			mergeFlag = 1;
	}
	return mergeFlag;
}

//============================================================================
//Move right.
//============================================================================
int moveRightByRow(int row, int col)
{
	int m = 2;
	int n;
	int cur;
	int mergeFlag = 0;

	while(m >= 0){
		n = m+1;
		cur = m;	//Current column value of the tile being moved.
		while(n <= 3){
			if(board[row][n] == 0){
				board[row][n] = board[row][cur];
				board[row][cur] = 0;
				cur = n;
				n = n+1;
				if(board[row][cur] != 0)
					mergeFlag = 1;
			}
			else if(board[row][n] == board[row][cur] && moveFlag[row][n] != 1){
				board[row][n] += board[row][cur];
				score += board[row][n];
				moveFlag[row][n] = 1;
				mergeFlag = 1;
				board[row][cur] = 0;
				break;
			}
			else
				break;
		}
		m = m-1;
	}
	return mergeFlag;
}

int moveRight()
{
	int mergeFlag = 0;
	initMoveFlag();

	for(int i=3; i>=0; i--){
		if((board[i][0] +
				board[i][1] +
				board[i][2] +
				board[i][3]) != 0)
		if(moveRightByRow(i, 3) == 1)
			mergeFlag = 1;
	}

	return mergeFlag;
}

//Randomly generate a tile.
int generateRandTile()
{
	/* 1 - Up
	 * 2 - Down
	 * 3 - Left
	 * 4 - Right
	 */
	int row, col;
	int gotIt = 0;
	int randN;
	int randT;

	Point point;

	vector<Point>().swap(pointQueue);

	for(int m=0; m<4; m++)
		for(int n=0; n<4; n++){
			if(board[m][n] == 0){
				point.x = m;
				point.y = n;
				pointQueue.push_back(point);	//Record the empty tile in a queue.
			}
		}

	randN = d(gen);
	if(randN <=9)
		randN = 2;
	else
		randN = 4;

	//If there is any empty tile, new random number will be placed there.
	if(pointQueue.size() != 0){
		uniform_int_distribution <> t(0, pointQueue.size() - 1);
		randT = t(gen);
		row = pointQueue[randT].x;
		col = pointQueue[randT].y;
		board[row][col] = randN;
		gotIt = 1;
	}

	return gotIt;
}

//============================================================================
//Main program.
//============================================================================
int main() {

	char dirKey;
	int randN;

	randN = d(gen);
	if(randN <=9)
		board[3][3] = 2;
	else
		board[3][3] = 4;

	showBoard();
	while(checkMove() != 0)		//Check wether there is an available move.
	{
		dirKey = getch();

		if(dirKey == 'a'){
			if(moveLeft() == 1){
				//if(generateFixTile(3) == 0) continue;
				if(generateRandTile() == 0)
					continue;
			}
			showBoard();
		}
		else if(dirKey == 's'){
			if(moveDown() == 1){
				//if(generateFixTile(2) == 0) continue;
				if(generateRandTile() == 0)
					continue;
			}
			showBoard();
		}
		else if(dirKey == 'd'){
			if(moveRight() == 1){
				//if(generateFixTile(4) == 0) continue;
				if(generateRandTile() == 0)
					continue;
			}
			showBoard();
		}
		else if(dirKey == 'w'){
			if(moveUp() == 1){
				//if(generateFixTile(1) == 0)	continue;
				if(generateRandTile() == 0)
					continue;
			}
			showBoard();
		}
		else{
			cout << dirKey << " --- It's not a direction (a/s/d/w) key!" << endl;
		}
		cout << endl;
	}

	cout << endl << "Game over!" << endl;

	return 0;
}
