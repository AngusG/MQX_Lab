/*
 * DisplayTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"

void print_accelerometer_data();

/*TASK*-----------------------------------------------------
* 
* Task Name    : Display_task
* Comments     :
*    This is the Display task
*
*END*-----------------------------------------------------*/

extern SENSOR_DATA Sensor;

void Display_task(uint32_t initial_data)
{
	_queue_id my_qid;
	APPLICATION_MESSAGE *msg;
	int gotAccel = 0;
	int gotTouch = 0;
	int gotPot = 0;
	char * touch;
	
	/* Lab 5 variables */
	LWGPIO_STRUCT leds[4];
	uint32_t i;
	uint32_t func[4] = { BSP_LED1_MUX_GPIO, 
						 BSP_LED2_MUX_GPIO,
						 BSP_LED3_MUX_GPIO, 
						 BSP_LED4_MUX_GPIO };
	
	LWGPIO_PIN_ID pins[4] = { BSP_LED1, BSP_LED2, BSP_LED3, BSP_LED4 };
	
	touch = malloc(sizeof(char)*6);
	strcpy(touch,"0\n");
	
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
			//printf("Display task received message %d: %d\n", msg->MESSAGE_TYPE,msg->DATA);
			

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
							
				if(gotAccel){
					gotPot = 1;	
					printf("%d;",msg->DATA); /* output ADC potentiometer data directly to serial	*/	
					printf("%s",touch);					
				}								
				break;
				
			case ACCEL_MESSAGE:	
				
				gotAccel = 1;				
				print_accelerometer_data();
				
				break;
				
			case TOUCH_MESSAGE:
				
				gotTouch = 1;			
				
				if(1 == msg->DATA){					
					
					lwgpio_toggle_value(&leds[0]); //toggle orange LED
					strcpy(touch,"1\n");
					
					/*if(gotPot){
						//printf("T 1\n");
						gotPot = 0;		//We can now reset the pot since we finished the string
						gotAccel = 0;   //We can reset the accel since we finished the string
					}*/
				}
				else if(2 == msg->DATA){
					
						lwgpio_toggle_value(&leds[1]); //toggle yellow LED
						strcpy(touch,"2\n"); //printf("T 2\n");
						/*
						if(gotPot){
						gotPot = 0;		//We can now reset the pot since we finished the string
						gotAccel = 0;   //We can reset the accel since we finished the string
					}*/
				}
				else if(3 == msg->DATA){
					
						lwgpio_toggle_value(&leds[2]); //toggle green LED
						strcpy(touch,"3\n"); //printf("T 3\n");
						/*if(gotPot){
						gotPot = 0;		//We can now reset the pot since we finished the string
						gotAccel = 0;   //We can reset the accel since we finished the string
					}*/
				}
				else if(4 == msg->DATA){
					
						lwgpio_toggle_value(&leds[3]); //toggle blue LED
						strcpy(touch,"4\n"); //printf("T 4\n");
					/*if(gotPot){
						gotPot = 0;		//We can now reset the pot since we finished the string
						gotAccel = 0;   //We can reset the accel since we finished the string
					}*/
				}				
				break;			
			}
			if((!gotTouch) && (gotPot == 1) && (gotAccel == 1)){	/* If there was no touch, and we are ready to put the touch msg in the string */
				strcpy(touch,"0\n");//printf("T 0\n");
				gotPot = 0;		//We can now reset the pot since we finished the string
				gotAccel = 0;   //We can reset the accel since we finished the string
			}
			gotTouch = 0; //We are now finished with the touch, it should be reset				
			_msg_free(msg);
		}  
		else{
			lwgpio_toggle_value(&leds[2]); //toggle green LED
		}
	}
}
void print_accelerometer_data()
{
   //MMA7660 Sensor

   printf("%04d;", Sensor.mma7660_x*5 );
   printf("%04d;", Sensor.mma7660_y*5 );
   printf("%04d;", Sensor.mma7660_z*5 );
}
