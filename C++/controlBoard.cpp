/*
David Wolak 
3/16/18
CPL Sorry! Project

This file holds the function definitions for everything in the control.h, everything here puts all the parts together. It moves the pawns, gets player inputs, draws cards, and updates the score. It also is reponsible for seeing if someone has won.
*/

#include <cstdio>
#include "controlBoard.h"

controller::controller()//Al the controller needs to do is open the file and read from it to start going
{
	
	readFile();
	
}


void controller::readFile()//Reads the player amount, board size, and the chance cards
{

	int input = 0;//Used as a temp input

	ifstream inFile;
	inFile.open("settings.txt");

	if(inFile.is_open())//If the file opens
	{
		



		inFile >> sizeBoard;//The first line is the board size
		if((sizeBoard < 4) || (sizeBoard > 80) || (sizeBoard%4 != 0))//If the board size is divisable by 4, bigger then 4, and smaller then 81 then it is valid
		{
			cout<<"***"<<endl;//If one of the critiea for the board side is wrong it errors and aborts the program
			cout<<"Critical Error: Settings file contains invalid board size"<<endl;
			cout<<"Aborting Program"<<endl;
			cout<<"***"<<endl;
			exit(1);//Aborts the program
		}else{//If the board size is valid then it creates the board
			gameBoard.createList(sizeBoard);
		}

inFile >>  playerAmt;//Next it gets the amount of players
		if(playerAmt > 4 || playerAmt < 1)//Only 1-4 players is allowed(yes one person is on purpose)
		{
			cout<<"***"<<endl;//If the amount of players is invalid it errors and aborts
			cout<<"Critical Error: Settings file contains invalid amount of players"<<endl;
			cout<<"Aborting Program"<<endl;
			cout<<"***"<<endl;
			exit(1);//Aborts the program
		}else{//Otherwise it makes a positoin tracker for that amount of players	
			positions.createTracker(playerAmt,sizeBoard);
		}

		while(inFile >> input)//This loop is for reading in the chance cards
		{
			cout<<input<<endl;
			if(input < 1 || (input > 12 && input !=20))//The cards have to be either 20(meaning sorry card) or between 1-12 or else it will abort
			{
				cout<<"***"<<endl;
				cout<<"Critical Error: Settings file contains invalid chance card"<<endl;
				cout<<"Aborting Program"<<endl;
				cout<<"***"<<endl;
				exit(1);//Aborts the program
			}else{//If the card amount is valid it inputs it into the tree used to hold the chance cards,
				if(input == 20)//If its 20 it makes it a sorry card
				{
					cards.insert(20,true);
				}else{
					cards.insert(input,false);			

				}

			}	


		}

	}else{//If no file is detected it aborts the set up
		cout<<"***"<<endl;
		cout<<"Crtical Error: No settings file detected"<<endl;
		cout<<"***"<<endl;
		exit(1);//Aborts the program
	}





}

int controller::menu()//Displays a menu and gets a valid input that it returns
{
	int answer = 0;
	do{
		cout<<"1. Roll Dice and move"<<endl;
		cout<<"2. Display Board"<<endl;
		cout<<"3. Display Scores"<<endl;
		cout<<"4. Skip Turn"<<endl;
		cout<<"5. Quit"<<endl;
		try{//Throws a int if the answer is invalid
			cin>>answer;
			if(answer > 5 || answer < 1)
				throw 10;
		}catch(int e){
			cout<<"***"<<endl;
			cout<<"Error: Invalid input try again"<<endl;
			cout<<"***"<<endl;
		}
	}while(answer > 5 || answer < 1);

	return answer;
}
int controller::operator-(int color)//Overloaded operator allows a color to be moved
{
	return this->move(color);
}


int controller::operator+(int color)
{

	return this->move(color);

}

ostream & operator << (ostream &out,tracker & positions)//These two overloaded operators can output the scores or the board depending on what is being attched
{
	positions.display();
	return out;
}

ostream & operator <<(ostream &out,board & gameBoard)
{
	gameBoard.displayBoard();
	return out;
}

int controller::move(int color)//This actually moves a color around the board
{
	int choice = 0;//Used to hold what the user wants to do
	int dice = 0;//Is used to hold a dice value
	char answer;//Used to hold players input
	int answerI = 0;//Is also used as a input from the players

	cout<<"Current Player: ";//This switch statement displays who is currently playing
	switch(color){
		case 1:
			cout<<"Green"<<endl;
			break;
		case 2:
			cout<<"Yellow"<<endl;
			break;
		case 3:
			cout<<"Red"<<endl;
			break;
		case 4:
			cout<<"Blue"<<endl;
			break;
	}	

	do{//This do while will keep going until the player wants to do something other then abort

		choice = menu();
		if(choice == 2)
		{
			displayBoard();	
		}else if(choice == 3){
			displayScore();
		}

	}while(choice == 2 || choice == 3);

	if(choice == 4)//If player wants to skip there turn this run exiting the program
	{
		cout<<"Skipping your turn!"<<endl;
		return 0 ;
	}else if(choice == 5){//If the player wants to quit the game this runs which quits the program
		return 5;

	}else{//If the player doesnt want to quit then they must want to move
		dice = (rand()%6)+1;//Rolls the dice
		cout<<"You rolled a "<<dice<<endl;//Shows player what they rolled
		cout<<"Would you like to move that far?(Y/N)"<<endl;//Players have a option of if they want to move or if they want to skip there turn. 
		do{//This loop gets the answer to do you want to move

			try{//Catches invalid answers and gives a error messae
				cout<<"If you would like to do this type Y, otherwise type N:";

				cin>>answer;
				answer = toupper(answer);
				if(answer != 'Y' && answer != 'N')
				{
					throw 10;
				}
				cin.clear();
			}catch(int e){
				cout<<"***"<<endl;
				cout<<"Error: Invalid input detected"<<endl;
				cout<<"***"<<endl;
			}
		}while(answer != 'Y' && answer != 'N');//Unless the answer is Y or N the loop will contuine

		if(answer == 'Y')//If they want to move 
		{
			cout<<"What pawn would you like to move?Input answer as a number from 1 to 3:"<<endl;
			do{//Gets a input form the player about what pawn they want to move
				try{
					cin>>answerI;
					if(answerI > 5 || answerI < 1)//If the answer is invalid it throws a int which causes a error message to display
						throw 20;
				}catch(int e){
					cout<<"***"<<endl;
					cout<<"Error: Number is out of range try again"<<endl;
					cout<<"***"<<endl;
				}
			}while(answerI > 3 || answerI < 1);//Keeps going until a good answer is given	
			movePiece(color,answerI,dice);//This acutally move the piece with the right color, pawn, and with the amount to move	
		}else{//If the player doesnt want to move	
			cout<<"Looks like your going to skip your turn then"<<endl;
		}


	}
	return 0;
}

int controller::drawCard()//This function draws a card and actually moves the pawn
{

	int card = cards.drawTop();//Gets a card from the top of the deck
	int amount = 0;
	switch(card)//Amount stores the value of move much the player is going to move since different cards move different amounts
	{
		case 1:
			amount = 1;
			break;
		case 2:
			amount = 2;
			break;
		case 3:
			amount = 3;
			break;
		case 4:
			amount = -4;
			break;
		case 5:
			amount = 5;
			break;
		case 6:
			amount = -6;
			break;
		case 7://Requires more steps ugh
			amount = 7;
			break;
		case 8:
			amount = 8;
			break;
		case 9:
			amount = -9;
			break;
		case 10:
			amount = 10;
			break;
		case 11:
			amount = 11;
			break;
		case 12:
			amount = 12;
			break;
		case 20://Sorry card!
			amount = 0;
			break;
	}

	return amount;
}


bool controller::winCheck(int color)//Checks if a color has won, to win you have to get a pawn to one pawn before your home
{

	int home = 0;//Stores the home value fo the color
	int winCon = 0;//Holds where the pawn needs to be to win
	bool win;//Stores if they won

	home = homeCalculation(color);//Gets the home of the piece
	if(home == 0)//If the home is zero instead of win condition being -1 it has to be set to the number
	{
		winCon = sizeBoard - 1;
	}else{
		winCon = home - 1;
	}
	win = positions.winCheck(color-1,winCon);//Gives the score tracker the info to check if it won

	return win;

}


void controller::displayScore()//Wrapper to display the scores
{
	positions.display();
}


void controller::displayBoard()//Wrapper to display the board and everyones positions
{
	gameBoard.displayBoard();
}

int controller::homeCalculation(int color)//Calculations the home value, this is done to prevent security issue with getting private data members
{
	switch(color)
	{
		case 1://Just does the calculations for each color for where their home should be. Then returns that calculated value
			return 0;
		case 2:
			return sizeBoard/4;
		case 3:
			return sizeBoard/2;
		case 4:
			return ((sizeBoard/2)+(sizeBoard/1));
		default:
			return 0;
	}
}

int controller::colorGetter(char color)//Given a char with the color it can return a int, this is because the score tracker users char arrays to organize everything while the rest uses ints so this lets the two pieces function together easier
{
	if(color == 'G')
	{
		return 1;
	}else if(color == 'Y'){
		return 2;
	}else if(color == 'R'){
		return 3;
	}else if(color == 'B'){
		return 4;
	}else{
		return 0;
	}
}

int controller::pawnGetter(char pawn)//Does the same thing as color getter for the reason reasons but with pawns
{
	if(pawn == '1')
	{
		return 1;
	}else if(pawn == '2'){
		return 2;
	}else if(pawn == '3'){
		return 3;
	}else 
		return 0;
}


void controller::movePiece(int color, int pawn,int amount)//This is the biggest function, it acutally moves the pawns and draws the cards 
{
	char name[2];//Which pawn is used

	int card = 0;//Which if any card is drawn

	snprintf(name,2,"%d",pawn);//Converts a int into a char
	switch(color)
	{
		case 1:
			name[1] = 'G';
			break;
		case 2:
			name[1] = 'Y';
			break;
		case 3:
			name[1] = 'R';
			break;	

		case 4:
			name[1] = 'B';
			break;



	}
	name[2] = '\0';//snprintf doesnt null terminate so it has to be done manually

	doubleNode * temp;//The place the piece is going to go
	doubleNode * currentPiece;//The place the node is currently at
	currentPiece = gameBoard.findPiece(name);//Finds the node that is about to be moved

	int pos = 0;//Gets the position of the nodes
	if(currentPiece)//If the piece is on the board it gets its current position
		pos = currentPiece->tileNumber();

	if(currentPiece->tileNumber() == homeCalculation(color))//If the piece is still on its home tile
	{
		if(amount != 1 && amount != 2)//The player needs to have rolled a one or two in order to move out of home
		{
			cout<<"You need to roll a one or two to move out of spawn not a "<<amount<<"!"<<endl;//If a 1 or 2 hasnt been rolled then the player isnt allowed to move from home and the function exits
			return;
		}	
	}



	if((pos%10-1) == 0)//If the current position is going to be on a draw card slot it does it, the -1 is so that the chance cards can never be on the pawns homes. They could be sent back one spot into a instant win
	{
		card = drawCard();//Draws a card from the deck
		cout<<"You landed on a chance card! You draw a card from the deck....."<<endl;
		cout<<"Its a "<<card<<"!"<<endl;
		if(card == 20){//this means its a sorry card
			cout<<"Sorry! "<<name[1]<<color<<" you just got kicked off!"<<endl;
			gameBoard.movePiece(NULL,currentPiece->tileNumber());//Clears the pawn off the board
			positions.movePiece(color,pawn,0);//Moves the pawn back to 0 on the score tracker
			return;//Exits the function
		}else{//just moving it around
			amount += card;//Otherwise it recalculates how far the pawn is going to move
		}
	}


	int newMove = pos+amount+1;//Calculates how far the pawn is going to move from its current slot
	while(newMove < 0)//If it goes back past slot 1 it recalcualtes where it will land
	{
		newMove += sizeBoard;
	}
	temp = gameBoard.getPosition(newMove);//Gets the tile of where the player is going to move


	if(temp->currentPiece() != NULL)//is SOMETHING there
	{
		char * name2 = new char[strlen(temp->currentPiece())];//If something is there it gets the name of the pawn there
		strcpy(name2,temp->currentPiece());	

		if(name[1] != name2[1]){//If this is not a players piece it will kick off the other players pawn


			gameBoard.movePiece(name,amount+pos);//Moves the current players pawn there

			int color2 = colorGetter(name2[1]);//Gets the color of the player who got kicked off
			int pawn2 = pawnGetter(name2[0]);//Gets the pawn number of the player who got kicked off

			cout<<"Sorry! "<<name2[1]<<color2<<" you got just kicked off!"<<endl;
			
			int move = amount+pos;//Figures out how much to move
			while(move < 0)//Same as above, its possible to go negative
			{
				move += sizeBoard;
			}


			gameBoard.movePiece(name,move);//Moves the new person onto the tile
			positions.movePiece(color,pawn,move);//Updates current players positions

			positions.movePiece(color2,pawn2,0);//Updates Sorry! persons positions



			gameBoard.movePiece(name,amount+pos);
			positions.movePiece(color,pawn,pos+amount);

		}else{//If players piece wants to move to a tile where they already are
			cout<<"You already have a piece there!"<<endl;
		}
	}else{//If nothing is there it just moves the pawn and updates the score tracker
		
		gameBoard.movePiece(name,newMove);
		positions.movePiece(color,pawn,newMove);

	}



}



/*
void controller::display()//Wrapper to display all the posistions
{
	positions.display();
}*/





