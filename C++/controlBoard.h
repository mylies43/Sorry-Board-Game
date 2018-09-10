/*

David Wolak
3/16/18
CPL Sorry! Project

This file is the header for the "main" class, the controller class. It brings everything together and is what lets everythign move around. It draws the cards, gets the user inputs, ect. This is the only class that directly  interacts with the user.

*/
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <ctype.h>
#include <fstream>


#include "PositionTracker.h"
#include "gameBoard.h"
#include "logic.h"


using namespace std;


class controller//This class controls everything and interacts with the users
{
public:
	
	controller();//Creates two players right now, creates deck, and creates gameboard of size 20
	int menu();//3 options return number

//	void display();//Show positions
	void movePiece(int color,int pawn,int amount);//Moves a piece on the board and updates it position in the score tracker			
	void displayBoard();//Displays the board	
	void displayScore();//Diplays the score
	int move(int color);//A different move function

	bool winCheck(int color);//Make this private


	int operator +(int amount);//Moves a color forward
	int operator -(int amount);//Moves a color back
	
	friend ostream & operator << (ostream &out,const tracker &positions);//Outputs the scores
	friend ostream & operator << (ostream &out,const board &gameBoard);//Diplays the game board

private:


	void readFile();//Reads the settings file and sets up the board
	int drawCard();//Get cards from top of tree
	int pawnGetter(char pawn);//Returns the int number of the correct color pawn
	int homeCalculation(int color);//Calculates where the home is given a color of a pawn
	int colorGetter(char color);//Returns the int value of a color

	int sizeBoard;//Holds the size of the board
	int playerAmt;//Holds the player amounts

	tracker positions;//Tracks positions
	AVLTree cards;//Draw cards from here
	board gameBoard;//creates gameboard


};
