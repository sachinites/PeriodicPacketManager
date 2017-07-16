#include "ppm.h"
#include <stdio.h>


char LC_NO;

static void 
main_menu(){

	do{
		printf("***************************\n");
		printf("Enter Choice : ");
		printf("1. ppm_dump_outbound_db\n");
		int choice;
		scanf("%d", &choice);
		printf("\n");
		switch(choice){
			case 1:
				ppm_dump_outbound_db();
				break;
			default:
				;
		}
	} while(1);
}

int
main(int argc, char **argv){

		
	LC_NO = atoi(argv[1]);/*To be fetched from argv*/

	ppm_init(LC_NO);
		
	main_menu();
	
        return 0;
}

