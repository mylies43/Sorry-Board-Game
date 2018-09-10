import java.util.Scanner;//Imports Scanner

public class LLLNode {
	
	protected static Scanner input = new Scanner(System.in);//Scanner for data input
	private LLLNode next;//Next pointer
	private int card;//This is the special instructions for the order
	
	LLLNode(int numb)//Sets the node equal to something
	{
		card = numb;
	}
	protected int getCard()//Gets the value of a card
	{
		return card;
	}

	protected LLLNode goForward()//Getter for the next pointer
	{
		return this.next;
	}
	protected void connectNode(LLLNode connect)//Connects a node after the current node
	{
		this.next = connect;
	}

	protected void deleteNode()
	{
		this.next = null;
	}

	LLLNode()//Constructor that makes everything null
	{
		next = null;
		card = 0;
	}
	public void display()//Displays the instructions
	{
		System.out.print(card);
	}
	
}


class listManager //This is the class that contains the linearly linked list itself
{
	protected LLLNode head = null;//Head node thats null

	public boolean emptyCheck()//Checks to see if the list is empty
	{
		
		if(head == null) {//If the head is empty it returns false, otherwise true
			return false;
		}else {
			return true;
		}
	}
	
	public int getFirst()//Gets the first node from the list and deletes it
	{
		if(head == null)//Returns 0 if the list is empty
		{
			return 0;
			
		}else{
			
			int numb = head.getCard();//Otherwise its gets the value of the first node
			head = head.goForward();//and moves the head forward one to delete the old head
			return numb;
		}
	}
	

	
	public void addNode(LLLNode toAdd)//Adds a node to the list
	{
		if(head == null)//Case 1, if head is empty sets the head to the toAdd
		{
			head = toAdd;
			
		}else if(head.goForward() == null){//If head is the only node adds the new node to the next node
			head.connectNode(toAdd);
		}else {
			addNode(head.goForward(),toAdd);//Otherwise traverse the list until it gets to a point it can add it
		}
	}
	
	private void addNode(LLLNode head,LLLNode toAdd)//Private method for adding nodes, traverse the list until it finds a spot
	{
		if(head.goForward() == null)//If at end of the list
		{
			head.connectNode(toAdd);//Adds the node
		}else {
			addNode(head.goForward(),toAdd);//Otherwise it keeps going
		}
	}

	public void display()//Displays everything
	{
		while(head != null)//Made it a loop just to keep it simple,loops though the loop until it gets the end, displays everything
		{
			head.display();
			System.out.print("\n \t");
			head = head.goForward();
		}
	}
	
	 //* Used as a test function to make sure everything worked
	/*public static void main(String[] args)
	{
		listManager test = new listManager();
		LLLNode toAdd = new LLLNode();
		toAdd.setInstruction();
		test.addNode(toAdd);
		
		LLLNode toAdd2 = new LLLNode();
		toAdd2.setInstruction();
		
		test.addNode(toAdd2);
		
		LLLNode toAdd3 = new LLLNode();
		toAdd3.setInstruction();
		
		test.addNode(toAdd3);
		test.display();
		//test.displayList();
	}*/

}