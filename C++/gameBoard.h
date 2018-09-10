/*
David Wolak
3/16/18
CPL Sorry! Project

This file contains the header for the position, doubleNode, and gameboard class! These functions are all responsible for creating the gameboard and moving pieces around on it. Another way to describe the position class is also to call it a tile class since it is responsible for just the tile. The doubleNode class inhertis the postion class and has the reponsiblity of being a node in a doubly linked circular list. I decided to go with a doubly circular list for my board because this way I could move each piece on one big board and have the homes be on different tiles, meaning less memory overhead. Not to mention that when they get to the end of the list the logic to have them move forward more is dead simple.
*/


#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

class position//This class is like a tile on the board, it takes care of itself, what number it is, and what pawn if any is currently on it
{
	public:
		position();//Construcotr that sets name to null
		position(int position);//This constructor also sets the tile number
		~position();//Deletes the name and sets it to null
			


		char * currentPiece();//Returns the current piece that is on the tile
		int tileNumber();//Returns what tile numbrer this one is
		bool winCheck();//Checks to see if someone has won by being on the tile before home

		void display();//Displays the tile
		void movePiece(char * name);//Moves a piece onto the tile
		bool emptyCheck();//returns true if something is there, false otherwise

		void deletePosition();//Clears a position		
		void showNumber();//Outputs just the number of the board used for testing
	private:

		int number;//Holds the tile number
		char * name;//Holds what pawn it is
};

class doubleNode:public position//This is the node class that is reponsible for just itself
{
	public:
		doubleNode();//Creates the node
		~doubleNode();//Deletes the node

		doubleNode(int position);//Can create the node and set the position at the same time
	
		doubleNode *& goForward();//Returns the next pointer
		doubleNode *& goBackward();//Returns the previous pointer
		void connectFront(doubleNode *& toConnect);//Connects a node infront of it
		void connectBack(doubleNode *& toConnect);//Connects a pointer behind it

		doubleNode *& operator++();//Moves the pointer forward
		doubleNode *& operator++(int);//Moves the pointer forward postfix

		doubleNode *& operator--();//Moves the pointer backwards
		doubleNode *& operator--(int);//Moves the pointe backwards postfix
	private:
		doubleNode * next;//Points to the next node
		doubleNode * prev;//Points to the previous node

};

class board//This class manages the board itself(a double linked circular list) 
{

public:
	board();//Creates the list
	~board();//Deletes the list

	void createList(int size);//Creates a list of a certain size
	void movePiece(char * name,int position);//Moves a piece based on name forward based on position
	void displayBoard();//Displays the board and says extra if there is apiece on it

	bool emptyCheck(int pos);//Checks if a position is empty

	doubleNode * getPosition(int pos);//Returns a tile that is in location position
	doubleNode * findPiece(char * name);//Finds a piece based on the name of it on the board and returns the tile
private:
	
	void deleteList();//Used to start deletion of the list
	bool emptyCheck(int pos,doubleNode * current);//Private method to check if the board is empty
	void movePiece(char * name,int position,doubleNode *& current);//Private ethod to move a piece position amount
	void deleteList(doubleNode *& current);//Recurrsive function to delete the list
	void displayBoard(doubleNode * current);//Recurssive function to display the list
	void createList(int size,doubleNode *& head,doubleNode *& rear);//Recurrsive method for creating the list

	doubleNode* findPiece(char * name,doubleNode * current);//Private method to find a piece by name
	doubleNode * getPosition(int pos,doubleNode *& current);//Private method to find a node based on position
	
	doubleNode * head;//Head of the list, no tail pointer in this list


};
