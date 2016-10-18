//============================================================================
// Name        : 2048A.cpp
// Author      : David Huang
// Version     : 0.1
// Copyright   : Free
// Description : 2048 game in C++, Ansi-style
//============================================================================

//============================================================================
//TODO LIST
//1. Add random number generator.
//2.
//============================================================================

#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <conio.h>

using namespace std;

int board[4][4], moveFlag[4][4];
int randNum = 2;
int randX = 4, randY = 4;	//Coordinate
int score = 0;

//============================================================================
//Initialization.
//============================================================================
//Show board
void showBoard()
{
	cout << "*** Scores: " << score << " ***" << endl;
	cout << "----------------------" << endl;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			cout << board[i][j] << "    ";
		}
		cout << endl << endl;
	}
	cout << "----------------------" << endl;
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

	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
		{
			if(board[i][j] == 0)
			{
				canMove =1;
				break;
			}

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
		return canMove;
}


//============================================================================
//Move up.
//============================================================================
void moveUpByCol(int row, int col)
{
	int m = 1;
	int n;
	int cur;

	while(m <=3){
		n = m-1;
		cur = m;	//Current row value of the tile being moved
		while(n >=0){
			if(board[n][col] == 0){
				board[n][col] = board[cur][col];
				board[cur][col] = 0;
				cur = n;
				n = n-1;
			}
			else if(board[n][col] == board[cur][col] && moveFlag[n][col] != 1){
				board[n][col] += board[cur][col];
				score += board[n][col];
				moveFlag[n][col] = 1;
				board[cur][col] = 0;
				break;
			}
			else
				break;
		}
		m = m+1;
	}
}

void moveUp()
{
	initMoveFlag();

	for(int j=0; j<4; j++){
		if((board[0][j] +
				board[1][j] +
				board[2][j] +
				board[3][j]) != 0)
		moveUpByCol(0, j);
	}
}

//============================================================================
//Move down.
//============================================================================
void moveDownByCol(int row, int col)
{
	int m = 2;
	int n;
	int cur;

	while(m >= 0){
		n = m+1;
		cur = m;	//Current row value of the tile being moved.
		while(n <= 3){
			if(board[n][col] == 0){
				board[n][col] = board[cur][col];
				board[cur][col] = 0;
				cur = n;
				n = n+1;
			}
			else if(board[n][col] == board[cur][col] && moveFlag[n][col] != 1){
				board[n][col] += board[cur][col];
				score += board[n][col];
				moveFlag[n][col] = 1;
				board[cur][col] = 0;
				break;
			}
			else
				break;
		}
		m = m-1;
	}
}

void moveDown()
{
	initMoveFlag();

	for(int j=3; j>=0; j--){
		if((board[0][j] +
				board[1][j] +
				board[2][j] +
				board[3][j]) != 0)
		moveDownByCol(3, j);
	}

}

//============================================================================
//Move left.
//============================================================================
void moveLeftByRow(int row, int col)
{
	int m = 1;
	int n;
	int cur;

	while(m <=3){
		n = m-1;
		cur = m;	//Current column value of the tile being moved.
		while(n >=0){
			if(board[row][n] == 0){
				board[row][n] = board[row][cur];
				board[row][cur] = 0;
				cur = n;
				n = n-1;
			}
			else if(board[row][n] == board[row][cur] && moveFlag[row][n] != 1){
				board[row][n] += board[row][cur];
				score += board[n][col];
				moveFlag[row][n] = 1;
				board[row][cur] = 0;
				break;
			}
			else
				break;
		}
		m = m+1;
	}
}

void moveLeft()
{
	initMoveFlag();

	for(int i=0; i<4; i++){
		if((board[i][0] +
				board[i][1] +
				board[i][2] +
				board[i][3]) != 0)
		moveLeftByRow(i, 0);
	}
}

//============================================================================
//Move right.
//============================================================================
void moveRightByRow(int row, int col)
{
	int m = 2;
	int n;
	int cur;

	while(m >= 0){
		n = m+1;
		cur = m;	//Current column value of the tile being moved.
		while(n <= 3){
			if(board[row][n] == 0){
				board[row][n] = board[row][cur];
				board[row][cur] = 0;
				cur = n;
				n = n+1;
			}
			else if(board[row][n] == board[row][cur] && moveFlag[row][n] != 1){
				board[row][n] += board[row][cur];
				score += board[n][col];
				moveFlag[row][n] = 1;
				board[row][cur] = 0;
				break;
			}
			else
				break;
		}
		m = m-1;
	}
}

void moveRight()
{
	initMoveFlag();

	for(int i=3; i>=0; i--){
		if((board[i][0] +
				board[i][1] +
				board[i][2] +
				board[i][3]) != 0)
		moveRightByRow(i, 3);
	}
}

//============================================================================
//Random number.
//============================================================================
//Randomly generate 2 or 4.
int generateRandNum(float deviation)
{
	random_device rd;
	int randNum;

	mt19937 gen(rd());
	// values near the mean are the most likely
	// standard deviation affects the dispersion of generated values from the mean
	std::normal_distribution<> d(2,deviation);
	randNum = round(d(gen));
	if(randNum ==2)
		randNum = 2;
	else
		randNum = 4;
	return randNum;
}

//Randomly generate coordinate
void generateRandXY()
{
	randX = 3;
	randY = 3;
}

int generateFixXY(int dir)
{
	/* 1 - Up
	 * 2 - Down
	 * 3 - Left
	 * 4 - Right
	 */
	int row, col;
	int gotIt = 0;

	switch(dir){
	case 1:
		row = 3;
		col = 3;
		for(int i=row; i>=0; i--)
			for(int j=col; j>=0; j--)
				if(board[i][j] == 0){
					board[i][j] = 2;
					gotIt = 1;
					return gotIt;
				}
		break;
	case 2:
		row = 0;
		col = 0;
		for(int i=row; i<=3; i++)
			for(int j=col; j<=3; j++)
				if(board[i][j] == 0){
					board[i][j] = 2;
					gotIt = 1;
					return gotIt;
				}
		break;
	case 3:
		row = 0;
		col = 3;
		for(int i=row; i<=3; i++)
			for(int j=col; j>=0; j--)
				if(board[i][j] == 0){
					board[i][j] = 2;
					gotIt = 1;
					return gotIt;
				}
		break;
	case 4:
		row = 3;
		col = 0;
		for(int i=row; i>=0; i--)
			for(int j=col; j<=3; j++)
				if(board[i][j] == 0){
					board[i][j] = 2;
					gotIt = 1;
					return gotIt;
				}
		break;
	}
	return gotIt;
}
//============================================================================
//Main program.
//============================================================================
int main() {

	char dirKey;
	/*
	randNum = generateRandNum(0.5);	//随机产生第一个数字
	generateRandXY();	//随机产生第一个数字的坐标
	board[randX][randY] = randNum;

	randNum = generateRandNum(0.5);	//随机产生第二个数字
	generateRandXY();	//随机产生第二个数字的坐标
	board[2][2] = randNum;
	*/

	board[3][3] = 2;
	showBoard();
	while(checkMove() != 0)		//Check wether there is an available move.
	{
		cin.clear();
		dirKey = getch();

		if(dirKey == 'a'){
			moveLeft();
			if(generateFixXY(3) == 0) continue;
			showBoard();

		}
		else if(dirKey == 's'){
			moveDown();
			if(generateFixXY(2) == 0) continue;
			showBoard();
		}
		else if(dirKey == 'd'){
			moveRight();
			if(generateFixXY(4) == 0) continue;
			showBoard();
		}
		else if(dirKey == 'w'){
			moveUp();
			if(generateFixXY(1) == 0)	continue;
			showBoard();
		}
		else{
			cout << dirKey << " --- It's not a arrow key!" << endl;
		}

		showBoard();
		cout << endl;
	}

	cout << endl << "Game over!" << endl;

	return 0;
}
