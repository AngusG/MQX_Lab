/*
 * TheftTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"


/*TASK*-----------------------------------------------------
* 
* Task Name    :Theft_task
* Comments     :
*    This is the Theft task
*
*END*-----------------------------------------------------*/

void Theft_task(uint32_t initial_data)
{
	_queue_id my_qid;
	APPLICATION_MESSAGE * msg;
	
	printf("\n Theft: Hello World \n"); 
	
	my_qid = _msgq_open(THEFT_QUEUE, 0);
		
	while(1){
		msg = _msgq_receive(my_qid, 0);
		printf("Theft task received message %d\n", msg->MESSAGE_TYPE);
		// _time_delay(1000);
		//_sched_yield();
	}	
	_task_block();
}
