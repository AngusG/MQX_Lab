/*
 * DisplayTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"


/*TASK*-----------------------------------------------------
* 
* Task Name    : Display_task
* Comments     :
*    This is the Display task
*
*END*-----------------------------------------------------*/


void Display_task(uint32_t initial_data)
{
	_queue_id my_qid;
	APPLICATION_MESSAGE *msg;
	
	/* Lab 5 variables */
	LWGPIO_STRUCT leds[4];
	uint32_t i;
	uint32_t func[4] = { BSP_LED1_MUX_GPIO, 
						 BSP_LED2_MUX_GPIO,
						 BSP_LED3_MUX_GPIO, 
						 BSP_LED4_MUX_GPIO };
	
	LWGPIO_PIN_ID pins[4] = { BSP_LED1, BSP_LED2, BSP_LED3, BSP_LED4 };
	
	printf("\n Display task started\n"); 
	
	my_qid = _msgq_open(DISPLAY_QUEUE, 0);	
	
	/* Initialize leds*/
	for(i=0;i<4;i++){
		lwgpio_init( &leds[i], pins[i], LWGPIO_DIR_OUTPUT, LWGPIO_VALUE_HIGH);
		lwgpio_set_functionality( &leds[i], func[i]);
	}	
	
	
	while(1){
		
		msg = _msgq_receive(my_qid, 1000); // returns null if no message after 1000ms
		
		if (msg != NULL ) {
			printf("Display task received message %d: %d\n", msg->MESSAGE_TYPE,msg->DATA);

			switch (msg->MESSAGE_TYPE) {
			
			case SW1_Message:
				lwgpio_set_value(&leds[0], LWGPIO_VALUE_LOW); // Orange -ON
				break;
			case SW2_Message:
				//lwgpio_set_value(&leds[1], msg->DATA);
				lwgpio_set_value(&leds[0], LWGPIO_VALUE_HIGH); // Orange -off
				lwgpio_set_value(&leds[1], LWGPIO_VALUE_HIGH); // Yellow -off
				lwgpio_set_value(&leds[3], LWGPIO_VALUE_HIGH); // Blue -off
				break;
			
			case ADC_READ_MESSAGE:
				/*
				if(msg->DATA<600){
					lwgpio_toggle_value(&leds[2]);					
				}
				else {
					// Toggle blue LED
					lwgpio_toggle_value(&leds[3]);
				}*/
				break;
				
			case TOUCH_MESSAGE:
				
				if(1 == msg->DATA)
					lwgpio_toggle_value(&leds[0]); //toggle orange LED
				else if(2 == msg->DATA)
					lwgpio_toggle_value(&leds[1]); //toggle yellow LED
				else if(3 == msg->DATA)
					lwgpio_toggle_value(&leds[2]); //toggle green LED
				else if(4 == msg->DATA)
					lwgpio_toggle_value(&leds[3]); //toggle blue LED
				
				break;
			
			}			
			_msg_free(msg);
		}  
		else{
			lwgpio_toggle_value(&leds[2]); //toggle green LED
		}
	}
}
