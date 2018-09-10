/*
David Wolak
3/16/18
CPL Sorry! Project

This function contains all the definitions for everything found in Positiontracker.h. It is a array of linked list that keep track of where each players node is. Each list is exactly 3 long because the player can only have 3 nodes.
*/


#include "PositionTracker.h"

tracker::tracker()//Creats the tracker by starting off with a null array and length of 0
{
	array = NULL;
	length = 0;
}

tracker::~tracker()//Deletes the tracker using a for loop
{
	for(int i = 0;i<length;i++)
	{
		array[i].deleteList();//Deletes each list at a time
	}
	delete [] array;//Deletes the array
	array = NULL;//Sets the array to null
}


linkedlist * linkedlist::operator +(node *& toAdd)//THis operator can add a node to a list
{
	this->addNode(toAdd);
	return this;
}

linkedlist * linkedlist::operator-(node *& del)//This operator deletes a node from a list
{
		this->deleteNode(del);
		return this;
}

void linkedlist::deleteNode(node *& del)//Deletes a node
{
	if(head)//IF the list exists
	{	
		if(head == del)//IF the nodes are equal(operator is overloaded)
		{
			if(head->goForward())//If ther exists a node after head it sets equal to that one and deletes head
			{
			node * temp = head;
			head = head->goForward();
			delete temp;
			temp = NULL;
			}else{
				delete head;
			}
		}else{//Else it moves down the list looking for the node to delete

			deleteNode(head->goForward(),del);
		}
	}
}

void linkedlist::deleteNode(node *& current,node *& del)//Recurssive function to delete a node
{
	if(current)//If the node exits
	{
		if(current->goForward() == del)//Checks to see if the next node is the one to delete
		{	
			if(current->goForward())//IF it is and a node exists after this one 
			{
				node * temp = current->goForward();//Creates a temp temp that is the one to delete, sets current to go to temps next
				current->goForward() = temp->goForward();
				delete temp;//Deletes temp and sets it to null
				temp = NULL;
			}
		}else{//If it did not find the node it keeps going down the list
			deleteNode(current->goForward(), del);
		}
	}
}

void linkedlist::addNode(node *& toAdd)//Adds a node to the list
{

	if(head)//If head exists it moves down the list til it finds a spot to add the node into
	{
		addNode(head->goForward(),toAdd);
	}else{//Otherwise it just makes head the new node
		head = toAdd;
	}

}

void linkedlist::addNode(node *& current,node *& toAdd)//Resurssive adds a node to the list
{

	if(current)//If the node exists it keeps going, always add to the end
	{
		addNode(current->goForward(),toAdd);
	}else{//If we reached the end then the null is made a new node
		current = toAdd;
	}
	
}
bool tracker::winCheck(int color,int win)//Starts a win check for a specific color
{

return array[color].winCheck(win);

}

bool linkedlist::winCheck(int win)//Win check for the list
{

	if(head->position() == win)//If the first pawn is at the win condition it returns true
	{
	
		return true;
	
	}else{//Otherwise it checks the other pawns
		return winCheck(head->goForward(),win);
	}

}

bool linkedlist::winCheck(node *& current,int win)//Recurssive function to check for a winning pawn
{
if(current)//If the node exists 
{
	if(current->position() == win)//If the pawn is the win condition it wins
	{
		return true;
	}else{
		return winCheck(current->goForward(),win);//Otherwise it moves down the list
	}

}else{//If it reached the end of the list it lost
	return false;
}


}

bool node::operator==(const node * compare)const//Overloaded operator to see if two nodes are equal
{
	if(compare->position() == this->position())//IF there position is the same they are considered equal
	{
		return true;
	}else{
		return false;	
	}


}

int node::position()const//Returns thes position of the nodes pawn
{
	return this->pawn->getPosition();
}



void tracker::createTracker(int size,int sizeBoard)//Creates a tracker for size amount of players, sizeBoard is used to calculation winning conditions
{

	array = new linkedlist[size+1];//Creates array with the correct amount of players
	length = size;//Sets the length of the array to the amount of playrew
	for(int i = 0;i<size;i++)//Goes to each list and creates a list each
	{
		array[i].createList(i+1,sizeBoard);
	}
}

void tracker::movePiece(int color,int piece,int position)//Calls the edit item for the correct color and piece
{
	array[color-1].editItem(piece,position);

}


void tracker::display()//Displays all lists and pawns
{
	try{//This try is here to catch a case where is displays a pawn that doesnt exist

		if(length == 0)//If there are no players it throws the error
		{
			throw 20;
		}else{


			for(int i = 0;i<length;i++)//Loops thourgh each player and says their name and displays their list
			{
				cout<<"Player ";
				switch(i){
					case 0:
						cout<<"Green: "<<endl;
						break;
					case 1:
						cout<<"Yellow: "<<endl;	
						break;

					case 2:
						cout<<"Red: "<<endl;
						break;

					case 3:
						cout<<"Blue: "<<endl;
						break;
				}
				array[i].displayList();
			}
		}
	}catch(int e){
		cout<<"Error: Trying to display non-existant pawns"<<endl;
	}

}





node::node()//creates a node by setting the pawn and next to null
{

	pawn = NULL;

	next = NULL;

}

void node::editPosition(int piece,int pos)//Edits the position of a pawn
{
	pawn->editPosition(pos);
}

node::node(int color,int size)//Creates a node of color color, size is used for home calculations
{
	switch(color)//The switch statement is to create the right type of pawn since dynamic downcasting is used 
	{
		case 1:
			pawn = new greenPiece(size);
			break;
		case 2:
			pawn = new yellowPiece(size);
			break;
		case 3:
			pawn = new redPiece(size);
			break;
		case 4: 
			pawn = new bluePiece(size);
			break;
		default:
			cout<<"Ooops! There can only be four players! Something went wrong"<<endl;
			break;
	}
	next = NULL;


}

node::~node()//Deletes a node
{
	delete pawn;
	pawn = NULL;
}

node *& node::goForward()//Gets the next node
{
	return this->next;
}

void node::connectPiece(node *& current,node *& toAdd)//Connects a node in front of the current one
{
	current->next = toAdd;
	toAdd->next = NULL;
}

void node::displayNode(int number)//Displays a specific pawn
{
	pawn->displayPiece(number);

}

linkedlist::linkedlist()//Constructor for the linked list
{
	head = NULL;
}

linkedlist::~linkedlist()//Dsecrutor for the linked list
{
//	deleteList();
}


void linkedlist::editItem(int piece,int pos)//Edits a specific item and changes its recorded position
{

	if(head)//If the list exists
	{
		if(piece == 1)//If this is the piece want want it edits it
		{
			head->editPosition(piece,pos);
		}else{//Otherwise it decrements piece and moves on
			editItem(head->goForward(),piece-1,pos);
		}
	}

}

void linkedlist::editItem(node *& current, int piece, int pos)//Resursive function to edit items
{
	if(current)//If the node exits
	{
		if(piece == 1)//IF we are where we want it edits the piece with the new position
		{
		//	cout<<"EDITING ITEM"<<endl;
			current->editPosition(piece,pos);
		}else{//Otherwise it moves onto decrementing piece
			editItem(current->goForward(),piece-1,pos);
		}
	}
}

void linkedlist::createList(int color,int size)//Creates a list for color.
{
	if(color >0 && color<5)//The colors can only be 1-4 so this checks for that
	{
		boardSize = size;//Sets the board size
		head = new node(color,size);//Creates a head for the list
		createList(head,color,2,size);//Creates the rest of the list


	}else{
		cout<<"Error occured while creating game piece"<<endl;

	}
}
void linkedlist::deleteList()//Starts the deletion of the list and then deletes itself
{
	if(head)
	{
		deleteList(head->goForward());
		delete head;
		head = NULL;
	}


}


void linkedlist::deleteList(node *& current)//Recurssive function for deleting the list
{
	if(current)
	{
		deleteList(current->goForward());
		delete current;
		current = NULL;
	}

}



void linkedlist::createList(node *& current,int color,int counter,int size)//Creates a list for color, counter to used to create a certain amount of nodes,and size is used for home calculations
{

	if(counter != 0)//If counter is not 0 we need to keep making nodes of color
	{
		node * toAdd = new node(color,size);
		current->connectPiece(current,toAdd);
		createList(current->goForward(),color,counter-1,size);//Moves on to create the next node and decrements counter
	}	


}


void linkedlist::displayList()//Displays the list
{
	if(head != NULL)//If the list is empty no point in displaying it
	{
		head->displayNode(3);//Displays the node
		displayList(head->goForward(),2);//Moves on
	}
}

void linkedlist::displayList(node *& current,int number)//Resurssively displays the list
{
	if(number != 0)//If we havent reached the end yet
	{
		current->displayNode(number);//Display the node and move on
		displayList(current->goForward(),number -1 );
	}

}

piece::~piece()//Descrutor for piece
{

}

greenPiece::greenPiece(int size)//Greenpieces constructor
{
	home = 0;//Green starts at 0 ALWAYS winning will be if it reaches the end of the board
	position = 0;
}

greenPiece::~greenPiece()//Green pieces descructor
{

}

yellowPiece::yellowPiece(int size)//Yellow pieces constructor
{
	home = (size/4);//Yellow always starts 1/4 of the way in the board, win is 1/4+5
	position = home;
}

yellowPiece::~yellowPiece()//Yellow Pieces descructor
{

}

redPiece::redPiece(int size)//Red pieces constructor
{
	home = (size/2);//Red starts at the middle of the board ALWAYS, win is 1/2+5
	position = home;
}

redPiece::~redPiece()//Red Pieces descructor
{

}

bluePiece::bluePiece(int size)//Blue pieces constructor
{
	home = (size/4)*3;//Blue starts at 3/4 into the board and wins at 3/4+5;
	position = home;
}

bluePiece::~bluePiece()//Blue pieces decructor
{

}


void greenPiece::displayPiece(int number)//Displays for a green pawn
{
	cout<<"Green pawn "<<number<<" is at tile "<<position<<endl;
}

void yellowPiece::displayPiece(int number)//Display for a yellow pawn
{
	cout<<"Yellow pawn "<<number<<" is at tile "<<position<<endl;
}


void redPiece::displayPiece(int number)//Display for a red pawn
{
	cout<<"Red pawn "<<number<<" is at tile "<<position<<endl;
}

void bluePiece::displayPiece(int number)//Display for a blue pawn
{
	cout<<"Blue pawn "<<number<<" is at tile "<<position<<endl;
}

int greenPiece::getPosition()//Getter for the position value
{
	return position;
}


int yellowPiece::getPosition()//Getter for the position value

{
	return position;
}


int redPiece::getPosition()//Getter for the position value

{
	return position;
}


int bluePiece::getPosition()//Getter for the position value

{
	return position;
}

void greenPiece::editPosition(int newP)//Replaces the old position with a new one
{
	position = newP;
}


void yellowPiece::editPosition(int newP)//Replaces the old position with a new one

{
	position = newP;
}

void redPiece::editPosition(int newP)//Replaces the old position with a new one

{
	position = newP;
}


void bluePiece::editPosition(int newP)//Replaces the old position with a new one

{
	position = newP;
}














