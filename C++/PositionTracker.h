/*
David Wolak
3/16/18
CPL Sorry! Project

This function contains the header for the array of linked list. Each list contains information about the pawns that the player controls and where they are. The array is how how ever many players there are big.

*/


#include <iostream>
#include <string.h>
using namespace std;




class piece//This could also be named pawn, its the abstract base class for all the different colored pieces.
{
	public:
		virtual ~piece() = 0;//This function creates the piece
		virtual void displayPiece(int) = 0;//Displays the piece
		virtual int getPosition()= 0;//Returns the value of the piece
		virtual void editPosition(int) = 0;//EDits the position of the piece
	protected:
		int position;//Holds the position of the piece
		int home;//Holds where the home is of the piece

};

class node//Class for the nodes linked list class
{

	public:
		node();//Creates a node
		node(int color,int size);//Sets a node of color and with its home

		virtual ~node();//Virtual descurctor for node, made virtual to stop undefined behavior from
			

		node *& goForward();//Gets the next node
		void connectPiece(node *& current,node *& toAdd);//Connects a node infront of the current one
		void displayNode(int number);//Displays the nodes
		void editPosition(int piece,int pos);//Edits the position of a node
		int position()const;//Returns the position of the node

		bool operator ==(const node*)const;//Can compare two nodes 
		
		
		
	protected:

		node * next;//Pointer for the next node
		piece * pawn;//Each node has a pawn
};


class linkedlist//This is the class for the acutal linked list
{
	public:
		linkedlist();//Creates the list
		~linkedlist();//Deletes the list


		void createList(int color,int size);//Creates a list of color color and of size size
		void displayList();//Displays the list
		void deleteList();//Deletes the list
		void editItem(int piece,int pos);//Edits a specific piece with a new position
		bool winCheck(int win);//Checks to see if a pawn won

		void addNode(node *& toAdd);//Adds a new node
		void deleteNode(node *&);//Deletes a node

	protected:

	
		bool winCheck(node *& current,int win);//Recurssive function for checking if someone won

		void deleteNode(node *&,node *&);//Recurssive function for deleting
		void addNode(node *& current, node *& toAdd);	//Recurssive function for adding a node to the list
		void editItem(node *& current,int piece,int pos);//Recurssive function for editing a node
		void deleteList(node *& current);	//Recurssive functionm for deleting the list
		void createList(node *& current,int color,int counter,int size);//Recurssive function for deleting the list
		void displayList(node *& current,int number);//Recurssive function for displaying the list

		linkedlist * operator + (node *&);//Overloaded operator that adds a node
		linkedlist * operator - (node *&);//Overloaded operator that deletes a node

		node * head = NULL;//Head of the list	
		int boardSize;//Holds the board size

};

class tracker//This has the array of linked list
{
	public:
		tracker();//Creates the array
		~tracker();//Deletes the aray

		void createTracker(int size,int sizeBoard);//Creates a array of size size 
		void display();//Displays everything in the array
		void movePiece(int color, int piece,int position);//Moves a piece of color and piece into a new position
		bool winCheck(int color,int win);//Checks if a specific color won
		
	private:
		int length;//Length of the array
		linkedlist * array = NULL;//The actaully array

};

class greenPiece:public piece//Class for the green pawn, all functions do what piece does but calculates home differently, refer to piece class for specifics 
{
	public:
	greenPiece(int size);
	~greenPiece();

	void displayPiece(int);
	int getPosition();
	void editPosition(int);


};

class redPiece:public piece//Class for the red pawn, all functions do what piece does but calculates home differently, refer to piece class for specifics 

{
	public:
	redPiece(int size);
	~redPiece();

	void displayPiece(int);
	int getPosition();
	void editPosition(int);

};

class yellowPiece:public piece//Class for the yellow pawn, all functions do what piece does but calculates home differently, refer to piece class for specifics 

{
	public:
	yellowPiece(int size);
	~yellowPiece();

	void displayPiece(int);
	int getPosition();
	void editPosition(int);


};
class bluePiece:public piece//Class for the blue pawn, all functions do what piece does but calculates home differently, refer to piece class for specifics 

{
	public:

	bluePiece(int size);
	~bluePiece();
	void displayPiece(int);
	int getPosition();
	void editPosition(int);

};
