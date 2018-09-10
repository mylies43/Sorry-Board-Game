/*
David Wolak
3/16/18
CPL Sorry! Project

This file holds all the definitions for the functions in gameBoard.h, it is a circularlly double-linked list, with each node holding a position value, along with a char *. It is responsible for moving the pieces around the board.Something fun to note is that when adding pieces to the board it has to move backwards to get a increase in tile number.

*/

#include "gameBoard.h"

board::board()//Board constructor
{
	head =NULL;
}

board::~board()//Descructor that just calls a deleteList function
{
	deleteList();
}
void board::movePiece(char *name,int position)//Given a pawn and a position to move it to it will move it.
{
	doubleNode * temp = findPiece(name);//Finds if the piece is already on the board
	position += temp->tileNumber();//Adds the location of the piece to how much it must move
	
	if(temp != NULL)//If the piece is already on the board then it deletes the piece from the board	
		temp->deletePosition();

	

	if(position == 1)//If we arrived where we want to go
	{
		head->goBackward()->movePiece(name);//We add the piece to the board	
	}else{//Otherwise it moves, decrementating
		movePiece(name,--position,head->goBackward()->goBackward());
	}
}

void board::movePiece(char * name,int position, doubleNode *& current)//Private move piece function
{
		if(position == 1)//If we are where we want to be
		{	
			current->movePiece(name);//Then the piece is added to that tile
//			cout<<"Adding Piece "<<name<<endl; Debuggin statement
		}else{
			movePiece(name,--position,current->goBackward());//Otherwise it keeps moving down the track
		}


}



doubleNode * board::getPosition(int position)//Given a position it returns the tile
{
	if(position == 1)//If we are there, returns heads
	{
		return head;
	}else{
		return getPosition(position-1,head->goForward());//Decrements the position value and moves on
	}		
}

doubleNode * board::getPosition(int position,doubleNode *& current)//Private version of functions above, it moves down the list until it finds the right tile
{
	if(position == 1)
	{
		return current;
	}else{
		return getPosition(position-1,current->goForward());
	}
}

doubleNode * board::findPiece(char * name)//Returns a tile found by looking for a pawn
{
	if(head)//If the list exists
	{
//	cout<<"Looking for "<<name<<endl; Debugging statement
		if(head->currentPiece() && strcmp(head->currentPiece(), name) == 0)//If we found the right tile it returns the tile(found by comparing names)
		{
			return head;
		}else{//Otherwise it keeps moving down the board
			return findPiece(name, head->goForward());
		}
	}else{
		return NULL;
	}

}

doubleNode* board::findPiece(char * name,doubleNode * current)//Same purpose of function above, but this one moves down the list until it finds the pawn
{
	if(head != current)//This keeps it from looping around the board in case the pawn isnt on the boardj
	{
		if(current->currentPiece() && strcmp(current->currentPiece(),name) == 0)//If the piece is found(found by comparing names)
		{
			return current;//Returns the current tile
		}else{
			return findPiece(name,current->goForward());//Else it keeps looking
		}
	}else{
//		cout<<"Did not find piece"<<endl; Debugging statement
		return NULL;//Returns NULL if the piece can not be found
	}

}


void board::createList(int size)//This creates the list of a given size
{
	if(size % 4 != 0)//Another check to see if the list is divisable by four
	{
		cout<<" *** \n Error Occured: Board size is not a multiple of four \n *** \n"<<endl;
		exit(EXIT_FAILURE);//Aborts the program
	}
	head = new doubleNode(size);//Creates a head node
	doubleNode * rear = new doubleNode(size-1);//Creates a rear pointer for the list

	head->connectFront(rear);//Connects the head and the rear
	rear->connectFront(head);//Connects the rear to the front
	//Since this is doubly linked they have to have their rear pointers connected too
	head->connectBack(rear);//Connects the back of the head to the rear
	rear->connectBack(head);//Connects the back to the rear to the head
	
	//Now that there is a list of size two it is much eaiser to attach more nodes

	createList(size-2,head,rear);//Attachs more nodes to the list
}

void board::createList(int size,doubleNode *& head,doubleNode *& rear)//Creates the board into the correct size
{
	if(size != 0)//If we have no finished creating the right sized board
	{
		doubleNode * current = new doubleNode(size);//Creates a new node

		rear->connectFront(current);//Attachs the front of the rear to the new node
		current->connectBack(rear);//Attachs the back of the current to the rear node

		current->connectFront(head);//Connects the front of current to head
		head->connectBack(current);//Connects the back to head to current

		createList(--size,head,current);//Moves on to the next node
	}
}

void board::displayBoard()//Public function for displaying the board
{
	if(head!= NULL)//If the list exists
	{
		if(head->currentPiece() != NULL)//If the current piece exists then it displays it
			head->display();
		head->showNumber();//Otherwise it just shows its number and then moves on
		displayBoard(head->goForward());
	}
}

void board::displayBoard(doubleNode * current)//Recurssive display method
{
	if(current != head)//If we have no reached the head yet
	{
		if(current->currentPiece() != NULL)//If there is a pawn here it displays it, otherwise it just displays the tile and moves on
			current->display();
		current->showNumber();
		displayBoard(current->goForward());
	}
}

void board::deleteList()//This functions deletes the game board by deleting the last node backwards
{
	if(head != NULL)//If there is no list, no need
	{
		deleteList(head->goForward());//Otherwise it sends a signal down the list to delete
		delete head;//When the rest are deleted it deletes the head	

	}

}

void board::deleteList(doubleNode *& current)//Recurssive deletion function
{
	if(current != head)//If we did not finish the loop yet
	{
		deleteList(current->goForward());//Sends a delete signal all the way down
		delete current;//Then deletes the tile
	}	
}

position::position()//Position constructor that set the name to NULL
{
	name = NULL;
}

position::~position()//Position destructor that deletes name and sets it NULL
{
	delete name;
	name = NULL;
}

position::position(int position)//Sets a tiles number
{
	number = position;
}

void position::deletePosition()//Function that does the same thing as the descurctor
{
	delete name;
	name = NULL;
}

char * position::currentPiece()//Returns the name of the tile
{
	return name;
}

int position::tileNumber()//If the tile exist it returns the tile number
{
	if(this != NULL)
{
		return number;
}else{
	return 0;
}
}

void position::display()//Displays the tile
{
		if(name[1] == 'R')//This if else takes the first character of the name(which indicates its color) and outputs its full name
		{
			cout<<"Red Piece ";
		}else if(name[1] == 'Y')
		{
			cout<<"Yelow Piece ";
		}else if(name[1] == 'G'){
			cout<<"Green Piece ";
		}else if(name[1] == 'B'){				
			cout<<"Blue Piece ";
		}else{//Default is arrows to make it obvious something went wrong
			cout<<"---> "<<name<<" ";
		}
		cout<<"is current at tile "<<number<<endl;

}

void position::showNumber()//outputs the number of the tile
{
	cout<<"This is tile "<<number<<endl;
}

bool board::emptyCheck(int position)//Checks if a position on the board is empty and returns a bool
{
//	cout<<"Checking sorry "<<position<<endl;
	if(head->tileNumber() == position)//If we want to look at head it checks it
	{
		return head->emptyCheck();
	}else{
		return emptyCheck(position,head->goForward());//Otherwise it moves on to the next node
	}

}

bool board::emptyCheck(int pos,doubleNode * current)//Looks for a tile and checks if its empty
{
	if(current == head)//If we have looped around to the end of the board
	{
		return false;//Didnt find the position so its not there
	}else if(current->tileNumber() == pos){//If we are at the tile to check
		return head->emptyCheck();//Checks if something is on the tile
	}else{
		return emptyCheck(pos,current->goForward());//Otherwise it moves forward
	}
}	
bool position::emptyCheck()//This checks if a tile is empty
{

	if(name == NULL)//If there is something in the name it can be assumed a pawn is there, otherwise nothing is there and the tile is empty
	{
		return false;
	}else{
		return true;
	}

}

void  position::movePiece(char  * newName)//Gives a new name to the tile
{
	delete name;//Just in case something is there
	name = new char[strlen(newName)+1];//We make a new char array and copy the new name into it
	strcpy(name,newName);
}


doubleNode *& doubleNode::operator++(int temp) //This operator can move the node forward
{

	return this->next;


}
doubleNode *& doubleNode::operator++() //So can this one, but in postfix
{

	return this->next;

}
doubleNode *& doubleNode::operator--(int temp) //Prefix moves the node forward
{

	return this->prev;

}
doubleNode *& doubleNode::operator--()//Postfix moves the node forward
{

	return this->prev;

}


doubleNode::~doubleNode()//Deletes a node by calling a rescurssive function and setting its pointers to null
{
	deletePosition();
	next = NULL;
	prev = NULL;
}

doubleNode::doubleNode(int number):position(number)//Kick starts the positions constructor
{

}

doubleNode::doubleNode()//Sets both pointers to null when creating a new node
{
	next = NULL;
	prev = NULL;
}

doubleNode *& doubleNode::goForward()//Returns forward
{
		return this->next;

}

doubleNode *& doubleNode::goBackward()//Returns backward
{
		return this->prev;
}

void doubleNode::connectFront(doubleNode *& toConnect)//Connects a node to the front
{
	this->next = toConnect;
}

void doubleNode::connectBack(doubleNode *& toConnect)//Connects a node to the back
{
	this->prev = toConnect;
}



