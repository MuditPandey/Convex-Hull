#include <iostream>
#include "comp_geo.h"

using namespace std;
int main() 
{
 	
	printf("\t\t\tCHOOSE AN ALGORITHM\n\n\n\n");
	printf("\t\t\t1.\tGraham Scan\n\t\t\t2.\tAndrew\n\t\t\t3.\tJarvis\n\n\n\t\t\t");
	int choice;
	scanf("%d",&choice);
	switch(choice){
		case 1: printf("\n\n\t\tEnter Number Of Points   -   ");
				comp_geo::Graham_scan();
		break;
		case 2: printf("\n\n\t\tEnter Number Of Points   -   ");
				comp_geo::Andrew_hull();
		break;
		case 3: printf("\n\n\t\tEnter Number Of Points   -   ");
				comp_geo::Jarvis_march();
		break;
		default: printf("\n\n\t\t\tWrong Choice :X");
					return 0;
	}
	
}
