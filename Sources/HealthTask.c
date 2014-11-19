/*
 * HealthTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"


/*TASK*-----------------------------------------------------
* 
* Task Name    : Health_task
* Comments     :
*    This is the Health task
*
*END*-----------------------------------------------------*/

void Health_task(uint32_t initial_data)
{
	_queue_id my_qid, display_qid;
	APPLICATION_MESSAGE * msg;
	
	printf("\n Health task started\n"); 
	
	 _klog_create(2*1024,0); //2048 Byte buffer, stop logging when full
	
	 _klog_control(KLOG_ENABLED | KLOG_CONTEXT_ENABLED |
			 	   KLOG_FUNCTIONS_ENABLED | KLOG_TIME_FUNCTIONS | KLOG_EVENT_FUNCTIONS |
			 	   //KLOG_TASK_QUALIFIED	  | 
			 	   //KLOG_NAME_FUNCTIONS 	  ,
			 	   //KLOG_INTERRUPTS_ENABLED, 
			 	   KLOG_INTERRUPT_FUNCTIONS,
			 	   TRUE ); //Enable kernel logging	 
	 
	_klog_enable_logging_task(_task_get_id()); /* Only tasks that enable klog can log */	
	_msgpool_create_system(sizeof(*msg), 10, 0, 0);	
	
	my_qid = _msgq_open(HEALTH_QUEUE, 0); /* Open message queue for health task */
	display_qid = _msgq_get_id(0, DISPLAY_QUEUE);	
	
	//printf("\n Health: Hello World\n"); 
	while(1){		
		msg = _msgq_receive(my_qid, 0);		
		//printf("Health task received a message\n");
		msg->HEADER.TARGET_QID = display_qid;
		
		_msgq_send(msg);
		
		//_time_delay(1000);
		//_sched_yield(); // Task puts itself at the end of the ready-to-run queue (for its priority)
	}
   
   _task_block();
}
