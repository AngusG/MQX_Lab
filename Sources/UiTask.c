/*
 * UiTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"

/*TASK*-----------------------------------------------------
* 
* Task Name    : Ui_task
* Comments     :
*    This is the User Interface task
*
*END*-----------------------------------------------------*/

void Ui_task(uint32_t initial_data)
{
	uint32_t numCanTasks, i;
	char c;
	_task_id ids[10] = {0};
	
	printf("\n Ui: Hello World \n"); 
	
	while(1){	
		
		printf("\n>");
		c = fgetc(stdin);
		
		switch(c){
			
		case 'c':
			printf("\n Enter a number of CAN Tasks to create [1-10]: \n"); 
			
			while(!(scanf("%d", &numCanTasks))){
				printf("Try Again. Enter a number from 1-10: \n");
			}
			if(numCanTasks > 10)
				numCanTasks = 10;
			
			for(i=0; i<numCanTasks; i++){
				
				ids[i] = _task_create(0, CAN_TASK, i);				
				if (ids[i] == MQX_NULL_TASK_ID)
				      printf ("\nCould not create Can_task\n");
				else
					printf("\nCreated task 0x%08x", ids[i]);
			}
			break;
			
		case 'd':		
			
			for(i=0; i<10; i++){ //for(all tasks)
				
				if(ids[i]){
					
					printf ("\n Destroying task 0x%08x \n", ids[i]);
					_task_destroy(ids[i]);
					ids[i] = 0;
				}
			}
			break;	
			
		case 'a':
				for (i=0; i<10; i++) {
					if (ids[i]) {
						printf("\nAborting task 0x%08x \n", ids[i]);
						_task_abort(ids[i]);
						ids[i] =0;
					}
				}
				break;
				
		case 'r':
				for (i=0; i<10; i++) {
					if (ids[i]) {
						printf("\nRestarting task 0x%08x", ids[i]);
						_task_restart(ids[i],&i, FALSE);
					}
				}
				break;		
			
			
		case 'h':
			printf("\nc- create can tasks");
			printf("\na- abort can tasks");
			printf("\nd- destroy can tasks");
			printf("\nr- restart can tasks");
			printf("\nh- help");
			break;			
		
		default:
				printf("Invalid selection!\n");
				break;
		}
		
	}
   
   _task_block();
}
