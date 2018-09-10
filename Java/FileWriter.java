/*
 * David Wolak
 * 3/16/18
 * 
 * This function has the classes needed to write into the file, it gets the inputs from the user.
 */

import java.io.PrintWriter;
import java.util.InputMismatchException;
import java.util.Objects;
import java.util.Scanner;//Imports Scanner
import java.io.*;

public class FileWriter {//This class gets input from the user and then writes it into the file
	
		private listManager cards;//Linked list used to store the chance cards before writing them to the file
		private static String filename = "settings.txt";//Holds the name of the file its writing to
		
		protected static Scanner input = new Scanner(System.in);//Scanner for data input
		private static PrintWriter write = null;//Printer Wrinter for file output
		
		FileWriter(){//Constructor sets up cards as a listManager(linked list) and sets up write
			cards = new listManager();
		 try {//Used to make sure Printe Writer doesnt error out
			 
			 write = new PrintWriter(filename);
			
		  } catch (FileNotFoundException ex) {
			  
			  System.out.println("*** \n Error: File Not Found \n *** \n");
			  
		  }
		}
		
		public void boardSize()//Gets input from the user about how big the board should be
		{
			int number = 0;//Used for input
		
			System.out.println("The size of the game board must be evenly divisble by 4");//Sets up the rules
			System.out.println("It must be larger then 4 but no larger then 80");
				
		do {	//Do while keeps asking for input while the answer is invalid
			try {
				
				System.out.print("Enter the size of the board: ");//Prompts
				number = input.nextInt();//Gets the input from the user
				
				if(((number%4) != 0) || (number > 80 || number <1))//If the input is not valid
					System.out.println("That is a invalid board size, try again");//Error message
				
			}catch(InputMismatchException e){//If a bad input is given it throws a error
				
				System.out.print("*** \n Error: Invalid input detected Try again \n ***\n");
			}
		}while((number%4) != 0);//The board has to be divisible by 4 to exit the loop
				System.out.print("Valid Board Size of "+number+" accepted \n");//Shows the number was accepted
				write.println(number);//Writes it to the file
				
				
		
		}
		
		public void playerAmt() {//This function gets the amount of players
			int players = 0;
			
				System.out.println("The only valid amount of players is 1-4");//Sets up rules
			do {	//Do while until the input is valid
				try {
					System.out.print("How many players: ");
					players = input.nextInt();//Gets the input from the user
					
					if(players > 4 || players < 1)//Checks to see if the input is not valid
						System.out.print("That is a invalid amount of players \n");//Error message
					
				}catch(InputMismatchException e){//If the wrong input is used it displays a error message and goes again
					
					System.out.print("*** \n Error: Invalid input detected Try again \n ***\n");
				}
			}while(players > 4 || players < 1);
			
					System.out.print("Valid Board Size of "+players+" accepted \n");//Show user it was accepted
					write.println(players);//Writes it to file
				
				
					
			
			}
		
		public void chanceCards()//This function writes the chances card into a linked list and then writes the linked list to a file
		{
			String answer = null;//Holds user input
			String yes = "Y";//These two are used to make things simpler
			String no = "N";
			
			int card = 0;
			
			System.out.println("The rules for chance cards are that they must be between 1-12, if you want to enter a sorry card enter 20");
		do {//This do while keeps going until the user is done inputting cards, no limits on the amount
			do {//This goes until a valid card number is put in
			try {
				System.out.print("Enter a chance card: ");
				card = input.nextInt();//Gets the input from the user
				
				if((card > 12 && card != 20) || card < 1)//If the input is not valid
					System.out.print("That is a invalid card \n");//Error message
				
			}catch(InputMismatchException e){//If the wrong input is used it displays a error message and goes again
				
				System.out.print("*** \n Error: Invalid input detected Try again \n ***\n");
			}
			}while((card > 12 && card != 20) || card < 1);
			
			LLLNode toAdd = new LLLNode(card);//Adds that card to a linked list for storage
			cards.addNode(toAdd);//Adds that node to list
			
			do {//This is used to see if the user wants to enter more cards
				
				
			System.out.print("Would you like to enter another card(Y/N)");
			answer = input.next();
			
			if(Objects.equals(answer, yes) && Objects.equals(answer, no))//If the answer does not equal Y or N it errors and goes asks again
				System.out.println("Invalid Answer: Try again");
			
			}while(Objects.equals(answer, yes) && Objects.equals(answer, no));
			
				
			}while(Objects.equals(answer, yes));//Does the big loop until the user is done
			System.out.println("Writing Chance cards to file");
			
			while(cards.emptyCheck())//Keeps going until the list is empty
			{
				int temp = cards.getFirst();//Gets the first card in the list
				write.print(temp);//Writes the card into the file followed by a space
				write.print(" ");
			}
			
			
		}
		
		protected void closeFile()//Closes the file so it writes out of ram into the file
		{
			write.close();
		}
		public static void main(String[] args) {
			
			FileWriter file = new FileWriter();//Creates a new file writer
			file.boardSize();//Gets the board size and writes it
			file.playerAmt();//Gets the player amount and writes it
			file.chanceCards();//Gets all the card and writes it
			file.closeFile();//Closes the file
	
			
			
		}
		
	
	
}
