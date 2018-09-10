#include "controlBoard.h"
int main()
{
	int exit = 1;
	controller test;
	//test.display();	
	while(!test.winCheck(1) && exit != 5)
	{
		exit = test.move(1);
			
	}

	return 0;

}
