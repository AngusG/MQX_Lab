/*
 * TempTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"


/*TASK*-----------------------------------------------------
* 
* Task Name    : Temp_task
* Comments     :
*    This is the Temperature task
*
*END*-----------------------------------------------------*/

void Temp_task(uint32_t initial_data)
{
	_queue_id  health_qid;
	APPLICATION_MESSAGE * msg;
		
	printf("\n Temp task started\n"); 
	
	_task_block(); // Per Lab 5 requirements
	
	health_qid = _msgq_get_id(0, HEALTH_QUEUE);
	while(1){
		
		_time_delay(5000);
		msg = _msg_alloc_system(sizeof(*msg));
		if( msg != NULL){
			msg->HEADER.TARGET_QID = health_qid;
			msg->MESSAGE_TYPE = TEMP_MESSAGE;
			msg->DATA = 0;
			
			_msgq_send(msg);
		}	
	}   
  // _task_block();
}
