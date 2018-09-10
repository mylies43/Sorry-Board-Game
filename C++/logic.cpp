/*
David Wolak
3/16/18
CPL Sorry! Project

This file holds all the function definitions for everything defined in logic.h, its all about 
everyone favorite topic. AVL trees! Yes! Thats all this file is, AVL trees.The AVL tree is used to 
hold a stack of chance cards. Its a bit silly since you end up with the same reapeating pattern 
but whatever this was a requirement. So the repeating cards is a behavior that is intended not a glitch.

*/

#include "logic.h"

AVLTree::AVLTree()//Constructor that just sets root to null
{
	root = NULL;
}

AVLTree::~AVLTree()//Descurtor that starts deleting the tree then deletes the root last
{

	deleteTree(root);
	delete root;
	root = NULL;
}

AVLTree::AVLTree(AVLTree *& toCopy)//Copy constructor that copies the tree to a new one
{
	toCopy->root = new treeNode(this->root);
	copy(this->root->goLeft(),toCopy->root->goLeft());
	copy(this->root->goRight(),toCopy->root->goRight());
}

void AVLTree::copy(treeNode *& current,treeNode *& toCopy)//Function to copy over trees
{
	if(current)//Long as the current tree has a node it will copy over the data and then send the copy function to left and right
	{
		toCopy = new treeNode(current);
		copy(current->goLeft(),current->goLeft());
		copy(current->goRight(),current->goRight());
	}


}


int AVLTree::drawTop()//This function draws from the top of the deck deletes the root and insert the card back in
{
	int draw;//Holds the card drawn
	bool sorry;//Holds if the card is a sorry card
	if(root)//If the root exists at all
	{
		sorry = root->isSorry();//Checks if the root is sorry
		draw = root->getCard();//Gets what card it is

		//cout<<"deleting root"<<endl; Debugging statement
		root = deleteNode(root,draw);//Deletes the root
		//cout<<"New Root: "<<root->getCard()<<endl; Debugging Statement
		//cout<<"Root Deleted adding in "<<draw<<endl;		Debugging statement
		insert(draw,sorry);//Inserts a the card that was just taken back into the root
		if(sorry)//If the card drawn was a sorry card then it gives out a 20, otherwise its whatever card was drawn
		{
			return 20;
		}else{
			return draw;
		}

	}else{//If theres no root, it just returns 0
		return 0;
	}
}

void AVLTree::deleteSmallest(treeNode *& current)//This function recurssively finds then deletes the smallest node in the tree
{
	if(current->goLeft())//IF there is still something on the left keep going
	{
		deleteSmallest(current->goLeft());
	}else{	
		//cout<<"DELETING : "<<current->getCard()<<endl; Debugging statement 
		delete current;//Deletes the node
		current = NULL;//Sets it to null
	}
}

int AVLTree::getheight(treeNode * current)//This recurssive gets the nodes heights and is my less efficent program
{
	if(current)//If the node exits
	{
		int left = 0;//Holds the lefts height
		int right = 0;//Holds the rights height

		left = getheight(current->goLeft());//Runs get height on the left subtree
		right = getheight(current->goRight());//Runs get hieght on the right subtree, these two mean that this function is run ALOT

		current->changeHeight(((left>right)? left : right)+1);//Updates the height to whatever the higher subtree is and then adds one to it
		return current->height();//Returns the new hight
	}else{
		return 0;//If we reach the end it returns a 0, signalling the end of the tree
	}	
}

treeNode::treeNode(treeNode *& copy)//Copys a the data into a new node
{
	copy = this;	
}

treeNode *& AVLTree::deleteNode(treeNode *& current,int key)//Deletes a node given a key(card value)
{
	if(key < current->getCard())//If the key is less then the current card it goes left
	{
		current->goLeft() = deleteNode(current->goLeft(),key);
	}else if(key > current->getCard()){//If its more it goes right

		current->goRight() = deleteNode(current->goRight(),key);	

	}else{//Otherwise we have arrived at the righ node



		if(current->goLeft() != NULL && current != root)//If there is just one child to the right it sets current as that chila this realistcally not happen
		{

		current = current->goLeft();

		}else if(current->goLeft() == NULL && current->goRight() == NULL){//If there is no childern it just deletes current and makes it null before returning null
		
		delete current;
		current = NULL;	
		return current;

		}else{//If there are two childern it finds and deletes the IOS.
			
			treeNode * temp = findSmallest(root->goLeft());//Finds the IOS
		

			current->setCard(temp->getCard(),temp->isSorry());//Sets the current card to whatever the IOS was

			deleteNode(root->goLeft(),temp->getCard());//Deletes the IOS
//			cout<<"Current is now "<<current->getCard()<<endl; Debugging statement
		}
	}
	current->changeHeight(1+(max(getheight(current->goLeft()),getheight(current->goRight()))));//Updates the height to be whatever height was taller + 1

//	cout<<"-----Delete Exiting: "<<current->getCard()<<endl; debugging statement
	return current;
}


treeNode *& AVLTree::findSmallest(treeNode *& current)//Finds and returns the IOS
{

	if(current->goRight())//If we can do right more we do, otherwise we return the node
	{
		return findSmallest(current->goRight());
	}else{
//		cout<<"Smallest found: "<<current->getCard()<<endl; Debugging statement
		return current;
	}

}

void AVLTree::deleteTree(treeNode *& current)//Deletes the tree 
{
	if(current)//If there is a node it sends a deletion signal down the left and right branches before deleting itself
	{
		deleteTree(current->goLeft());
		deleteTree(current->goRight());
		delete current;
		current = NULL;
	}
}

void AVLTree::display()//Displays the tree, not used in program. Just for debugging
{
	if(root)
	{
		cout<<"Card: "<<root->getCard()<<" is root at height "<<root->height()<<endl;
		if(root->isSorry())
		{
			//	cout<<" Is a sorry card"<<endl; I decided there was a point to this since this is a debugging function
		}else{
			//	cout<<" is not a sorry card"<<endl;
		}
		display(root->goLeft());
		//cout<<"Moving up a layer and to the right "<<endl; Debugging
		display(root->goRight());
	}

}
void AVLTree::display(treeNode * current)//Recurssive display, same as above
{
	if(current && current != root)
	{
		cout<<"Card: "<<current->getCard()<<" at height "<<current->height()<<endl;
		if(current->isSorry())
		{
			//		cout<<" Is a sorry card"<<endl;
		}else{
			//		cout<<" is not a sorry card"<<endl;
		}
		display(current->goLeft());
		display(current->goRight());
	}

}

int AVLTree::balance(treeNode * current)//This gets the balance of the node
{
	int balance = 0;
	if(current)//If the node exists
	{
		balance = current->goLeft()->height();
		balance -= current->goRight()->height();//The balance is the height of the left subtree minus the height of the right. Ideally this is 0

	}
	//cout<<"***Balance Returning ->"<<balance<<endl; debugging statement
	return balance;
}

void AVLTree::insert(int numb,bool sorry)//Public function for inserting a node into the tree
{
	//cout<<"-----"<<endl;
	treeNode * toAdd = new treeNode;//Creates a new node, loads it up with a number and if its sorry
	toAdd->setCard(numb,sorry);
	if(root)//IF the root exists it sends it down the resurssive insert otherwise it just makes the root the new new node
	{
		root = insert(root,toAdd);
	}else{
		root = toAdd;
		root->changeHeight(1);
	}
}

treeNode *& AVLTree::rRotate(treeNode *& current,treeNode *& temp)//This right rotates the tree, temp is currents left node, done like this because it needs to be returned and a local value cant be returned
{
	if(temp == NULL || current == NULL)//if both nodes are somehow null it exits the program
	{
		return current;
	}
	//cout<<"Right rotate"<<endl; Debugging statement
	treeNode * temp2 = temp->goRight();//creates a new node for temps right

	temp->goRight() = current;//Makes current temps right, so current becomes its own left right node
	current->goLeft() = temp2;//Makes currents left its old right

	current->changeHeight(1+(max(getheight(current->goLeft()),getheight(current->goRight()))));//Updates the height of the node

	temp->changeHeight(1+(max(getheight(temp->goLeft()),getheight(temp->goRight()))));//Chances temps height too



	return temp;//The currents left becomes the new current

}

treeNode *& AVLTree::lRotate(treeNode *& current,treeNode *& temp)//Left rotates a node, temp is currents right node
{
	//cout<<"Left Rotate"<<endl; debugging statement
	if(temp == NULL || current == NULL)//If something happens and both nodes are null it leaves
	{
		return current;
	}
	treeNode * temp2 = temp->goLeft();//Gets currents right left

	temp->goLeft() = current;//Sets currents right left to itself
	current->goRight() = temp2;//Sets currents right to its old right left

	current->changeHeight(1+(max(getheight(current->goLeft()),getheight(current->goRight()))));//Updates currents and temps hieght
	temp->changeHeight(1+(max(getheight(temp->goLeft()),getheight(temp->goRight()))));



	return temp;//The currents right becomes the new right

}


treeNode *& AVLTree::insert(treeNode *& current, treeNode *& toAdd)//Recurssive insets a new node
{
	int key = toAdd->getCard();
	int curKey = current->getCard();

	if(current == NULL)//First its a standard BST insert
	{	//found the spot I wanted
		current = toAdd;
		return toAdd;
	}

	//Otherwise look for where the key goes
	if(key < curKey)
	{
		current->goLeft() = insert(current->goLeft(),toAdd);
	}else if(key > curKey){
		current->goRight() = insert(current->goRight(),toAdd);
	}else{//if the keys are equal no equal keys in my good BST!!!!!!!!!
		return current;
	}

	//gotta update the height
	current->changeHeight(1+(max(getheight(current->goLeft()),getheight(current->goRight()))));


	int bal = balance(current);//Now the magic starts

	//Gets the balance of the right and left subtree
	int leftKey = current->goLeft()->getCard();
	int rightKey = current->goRight()->getCard();
	//cout<<"Insert Balance: "<<bal<<" Left Key: "<<leftKey<<" Right Key: "<<rightKey<<endl; debugging statement
	if(bal > 1 && key < leftKey)//If the current node is off balance and key is less then left key it right rotates
	{
		treeNode * temp = current->goLeft();
		return rRotate(current,temp);

	}	

	//right right
	if(bal < -1 && key > rightKey)//If its off balanced the otherway it left rotates
	{
		treeNode * temp = current->goRight();
		return lRotate(current,temp);
	}
	//left right
	if(bal > 1 && key > leftKey)//If balance is > 1 and left key is less then the current key it first left rotates then right rotates
	{
		treeNode * temp = current->goLeft()->goRight();
		current->goLeft() = lRotate(current->goLeft(),temp);
		temp = current->goLeft();
		return rRotate(current,temp);
	}

	//right left
	if(bal < -1 && key < rightKey)// if the balance is less then one and the key is less then the right key is does a right left rotae
	{
		treeNode * temp = current->goRight()->goLeft();
		current->goRight() = rRotate(current->goRight(),temp);
		temp = current->goRight();	
		return lRotate(current,temp);
	}

	return current;

}


treeNode *& treeNode::goRight()//Getter that gets the right node
{
//	if(this)
		return right;
}

treeNode *& treeNode::goLeft()//Getter that gets the left node
{
//	if(this)
		return left;
}


void treeNode::connectRight(treeNode *& toAdd)//Connects a node to the right
{
	this->right = toAdd;
}
void treeNode::connectLeft(treeNode *& toAdd)//Connects a node to the right
{
	this->left = toAdd;
}

int treeNode::height()//Getter for the height of the tree
{
	if(this){
		return tall;
	}else{
		return 0;
	}
}

void treeNode::changeHeight(int newH)//Setter for height of a node
{
	tall = newH;
}



treeNode::treeNode()
{
	left = NULL;
	right=  NULL;
}

treeNode::~treeNode()
{
	left = NULL;
	right = NULL;
}




card::card()
{
	sorry = false;
}

void card::setCard(int copyNumber, bool copySorry)
{
	number = copyNumber;
	sorry = copySorry;

}

int card::getCard()
{
	if(this){
		return number;
	}else{
		return 0;
	}
}

bool card::isSorry()
{
	return sorry;
}


