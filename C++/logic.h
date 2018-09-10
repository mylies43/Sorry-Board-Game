/*
   David Wolak
   3/16/18
   CPL Sorry! Project

   This is the header function for card,treenode, and AVLTree. Its all about AVLTrees in here.

 */

#include <iostream>
#include <algorithm>
#include <string.h>
#include <stdlib.h>
using namespace std;

class card//This class deals with the card and how they function
{
	public:
		card();//Just sets sorry to false 
		void setCard(int number,bool sorry);//Sets card
		int getCard();//Gets card number
		bool isSorry();//Checks if it is a sorry card

	private:
		int number;//Holds the number on the card
		bool sorry;//Holds if its a sorry card or not
};



class treeNode:public card//Class for the nodes on the AVL tree
{
	public:
		treeNode();//Creates the nodes
		treeNode(treeNode *& copy);//Copies the nodes
		~treeNode();//Deletes the nodes

		void connectLeft(treeNode *& toAdd);//Connects a node to the left
		void connectRight(treeNode *& toAdd);//Connects a node to right 
		treeNode *& goLeft();//Goes left
		treeNode *& goRight();	//Goes right

		int height();//Gets the height of the node
		void changeHeight(int newHeight);//Sets the height of the node

	private:

		treeNode * left;//Pointer to the left
		treeNode * right;//Pointer to the right
		int tall;//Holds the heigh of the node

};



class AVLTree//This class is acutal AVL Tree
{
	public:
		AVLTree();//Creates the tree
		AVLTree(AVLTree *&);//Copies the tree
		~AVLTree();//Deletes the tree

		void insert(int numb,bool sorry);//Creates and inserts a node into the tree
		int drawTop();//Gets a card from the top of the tree
		void display();//Displays the whole tree, debugging uses mostly
	private:
		void deleteTree(treeNode *& current);//Recurssive function for deleting the tree
		void copy(treeNode *&,treeNode *&);//Rescurssive function for coping the tree

		int height(treeNode * current);//Updates the hieght of all the nodes in the tree
		int diff(treeNode * current);//Figures out the difference in heights

		int getheight(treeNode * current);//Gets the height of a node
		int balance(treeNode * current);//Gets the balance factor for a node
		void deleteSmallest(treeNode *& current);//Deletes the smallest node of a subtree
		treeNode *& deleteNode(treeNode *& current,int key);//Deletes a specific node
		treeNode *& findSmallest(treeNode *& current);//Finds and returns the smallest node 

		treeNode *& rRotate(treeNode *& current,treeNode *& temp);//Right rotates a node
		treeNode *& lRotate(treeNode *& current,treeNode *& temp);//Left rotatea a node 
		treeNode *& removeRoot(treeNode *& newRoot);//Removes the root from the tree
		treeNode *& findLargest(treeNode *& current);//Finds and returns the largest node it can find

		treeNode *& insert(treeNode *& current,treeNode *& toAdd);//Recurrsive call for inserting into the tree

		void display(treeNode * current);//Resurssive call for displaying

		treeNode * root;//Root of the tree

};
