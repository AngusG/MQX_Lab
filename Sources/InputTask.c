/*
 * InputTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"

/* Lab 7 - defines */
#define SW1_EVENT 0x00000001
#define SW2_EVENT 0x00000002
/* Lab 8 - defines */
#define ADC_TIMER_EVENT 0x00000004

/* Lab 6 - Interrupts - Prototypes/Declarations */
void init_switch(LWGPIO_STRUCT_PTR sw,
		LWGPIO_PIN_ID pin,
		uint32_t mux,
		INT_ISR_FPTR sw_isr
		);

void sw1_isr(void * param);
void sw2_isr(void * param);
void adc_timer_isr(void); //Lab 8

/* Lab 7 - Global LW Event structure */
LWEVENT_STRUCT lwevent_group;
/* Note:
 * 
 * Can do this because we only make a single instance.
 * If multiple instances, declare LWEVENT_STRUCT within 
 * the task. 
 * 
 * */

extern const LWADC_INIT_STRUCT BSP_DEFAULT_LWADC_MODULE;

/*TASK*-----------------------------------------------------
* 
* Task Name    : Input_task
* Comments     :
*    This is the Input task
*
*END*-----------------------------------------------------*/

void Input_task(uint32_t initial_data)
{
	//int NUM=1;// this is used for dividing 
	_queue_id health_qid;
	uint32_t event_bits;
	APPLICATION_MESSAGE *msg;
	
	/* Lab 5 variables */
	LWGPIO_STRUCT sw1, sw2;
//	LWGPIO_VALUE sw1_value, sw2_value;
//	LWGPIO_VALUE sw1_last_value = LWGPIO_VALUE_HIGH,
//				 sw2_last_value = LWGPIO_VALUE_HIGH; // retain the previous value of each switch
	
	/* Lab 8 vars */
	LWTIMER_PERIOD_STRUCT period;
	LWTIMER_STRUCT timer;
	
	/* Lab 9 vars */
	LWADC_STRUCT adc1_pot;
	LWADC_VALUE voltage;
	
	init_switch(&sw1, BSP_SW1, BSP_SW1_MUX_GPIO, sw1_isr);
	init_switch(&sw2, BSP_SW2, BSP_SW2_MUX_GPIO, sw2_isr);	
	
	/* Lab 9 init adc */
	_lwadc_init(&BSP_DEFAULT_LWADC_MODULE);
	_lwadc_init_input(&adc1_pot,BSP_ADC_POTENTIOMETER);
	_lwadc_set_attribute(&adc1_pot, LWADC_NUMERATOR, 12000);
	
	health_qid = _msgq_get_id(0, HEALTH_QUEUE);
	
	/* Lab 7 - init LW event */
	_lwevent_create(&lwevent_group,LWEVENT_AUTO_CLEAR);
	
	/* Lab 8 - init */
	_lwtimer_create_periodic_queue(&period, BSP_ALARM_FREQUENCY/10,0);
	//period = 10Hz, 1/10th of a second expiry
	 	
	/* call adc_timer_isr with no parameters when timer expires */
	_lwtimer_add_timer_to_queue(&period, &timer, 0, adc_timer_isr, NULL);
	
	printf("\n Input task started \n"); 
	
	while(1){		
		
		/* Lab 7 - wait for event bits indefinitely */
		_lwevent_wait_ticks(&lwevent_group, SW1_EVENT | SW2_EVENT | ADC_TIMER_EVENT, FALSE, 0);
		
		/* Lab 7 - input task needs to know which bit was set */
		event_bits = _lwevent_get_signalled();
		
		if (event_bits & ADC_TIMER_EVENT) {
			if(_lwadc_read(&adc1_pot, &voltage)){	
				
				msg = _msg_alloc_system(sizeof(*msg));
				
				if (msg != NULL ) {
					msg->HEADER.TARGET_QID = health_qid;
					msg->MESSAGE_TYPE = ADC_READ_MESSAGE;
					msg->DATA = voltage;
					_msgq_send(msg);
				}
			}
		}	
		
		if(event_bits & SW1_EVENT){
			//_lwevent_clear(&lwevent_group, SW1_EVENT);
			msg = _msg_alloc_system(sizeof(*msg));			
			if (msg != NULL ) {
				msg->HEADER.TARGET_QID = health_qid;
				msg->MESSAGE_TYPE = SW1_Message;
				msg->DATA = 0;
				
				_msgq_send(msg);
			}
		}		
		if(event_bits & SW2_EVENT){
			msg = _msg_alloc_system(sizeof(*msg));
			if (msg != NULL ) {
				msg->HEADER.TARGET_QID = health_qid;
				msg->MESSAGE_TYPE = SW2_Message;
				msg->DATA = 0;
				
				_msgq_send(msg);
			}
		}	
		_time_delay(100); 			
	}    
}
/* Called every 1/10s when timer expires */
void adc_timer_isr(void){
	
	_lwevent_set(&lwevent_group, ADC_TIMER_EVENT); //Set event bit
}


void init_switch(LWGPIO_STRUCT_PTR sw,
		LWGPIO_PIN_ID pin,
		uint32_t mux,
		INT_ISR_FPTR sw_isr
		)
{
	/* Initialize input pins */
	lwgpio_init( sw, pin, LWGPIO_DIR_INPUT, LWGPIO_VALUE_NOCHANGE );
	
	/* Set functionality/pin muxing  */
	lwgpio_set_functionality( sw, mux );
	
	/* Pull up push button lines so that they are not floating, since switch drives to gnd */
	lwgpio_set_attribute( sw, LWGPIO_ATTR_PULL_UP, LWGPIO_AVAL_ENABLE );
	
	/* Initialize an interrupt */
	lwgpio_int_init( sw, LWGPIO_INT_MODE_FALLING);
	
	/* Install the switch specific ISR */
	_int_install_isr( lwgpio_int_get_vector(sw), sw_isr, sw);
	
	/* Enabling an ISR in the GPIO device */
	lwgpio_int_enable( sw, TRUE);
	
	/* 4 = main priority, 0 = sub level priority */
	_bsp_int_init( lwgpio_int_get_vector(sw), 4, 0, TRUE);
}

void sw1_isr(void * param) {

	LWGPIO_STRUCT_PTR sw = (LWGPIO_STRUCT_PTR) param;
	//APPLICATION_MESSAGE *msg;

	lwgpio_int_clear_flag(sw);
	
	/* Lab 7 - shorten ISR */
	_lwevent_set(&lwevent_group, SW1_EVENT);
	

	/*
	msg = _msg_alloc_system(sizeof(*msg));	
	if (msg != NULL ) {
		msg->HEADER.TARGET_QID =_msgq_get_id(0, HEALTH_QUEUE);
		msg->MESSAGE_TYPE = SW1_Message;
		msg->DATA = 0;

		_msgq_send(msg);
	}*/
}

void sw2_isr(void * param) {

	LWGPIO_STRUCT_PTR sw = (LWGPIO_STRUCT_PTR) param;

	lwgpio_int_clear_flag(sw);
	_lwevent_set(&lwevent_group, SW2_EVENT);	
}



