/*
 * InputTask.c
 *
 *  Created on: Feb 6, 2014
 *      Author: Embedded Access Inc
 */

#include "main.h"
#include "tsi.h"

/*
 Lab 7 - defines 
#define SW1_EVENT 0x00000001
#define SW2_EVENT 0x00000002
 Lab 8 - defines 
#define ADC_TIMER_EVENT 0x00000004
 Add TSI 
#define TOUCH_EVENT 0x00000008
*/

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
	_lwtimer_create_periodic_queue(&period, BSP_ALARM_FREQUENCY/8,0);
	//period = 10Hz, 1/10th of a second expiry
	 	
	/* call adc_timer_isr with no parameters when timer expires */
	_lwtimer_add_timer_to_queue(&period, &timer, 0, adc_timer_isr, NULL);
	//_lwtimer_add_timer_to_queue(&period, &timer, 0, adc_timer_isr, 0);
	
	printf("\n Input task started \n"); 
	
	TSI_Start();
	
	while(1){		
		
		/* Lab 7 - wait for event bits indefinitely */
		_lwevent_wait_ticks(&lwevent_group, SW1_EVENT | SW2_EVENT | ADC_TIMER_EVENT
				| TOUCH1_EVENT | TOUCH2_EVENT | TOUCH3_EVENT | TOUCH4_EVENT, FALSE, 0);
		
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
		if(event_bits & (TOUCH1_EVENT | TOUCH2_EVENT | TOUCH3_EVENT | TOUCH4_EVENT))
		{
			msg = _msg_alloc_system(sizeof(*msg));
			if (msg != NULL ) {
				msg->HEADER.TARGET_QID = health_qid;
				msg->MESSAGE_TYPE = TOUCH_MESSAGE;
				if(event_bits & TOUCH1_EVENT)
					msg->DATA = 1;	
				else if(event_bits & TOUCH2_EVENT)
					msg->DATA = 2;
				else if(event_bits & TOUCH3_EVENT)
					msg->DATA = 3;
				else if(event_bits & TOUCH4_EVENT)
					msg->DATA = 4;
				else
					msg->DATA = 0; //ERROR 
				
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
}

void sw2_isr(void * param) {

	LWGPIO_STRUCT_PTR sw = (LWGPIO_STRUCT_PTR) param;

	lwgpio_int_clear_flag(sw);
	_lwevent_set(&lwevent_group, SW2_EVENT);	
}



#ifdef GAME_TASK

#include "demo.h"
#include "DemoIO.h"
#include "TSI.h"
#include <event.h>

#define LOG_LENGTH  30
char LastKeyPressed();
char KeyPressed();
void AddTouch(char key);
void WaitForTouch();
void WaitForRelease();
void create_sequence();
void GetHighScore();

volatile unsigned char sequence[LOG_LENGTH];
volatile unsigned char keylog[LOG_LENGTH];
volatile unsigned char keypressed;
char length;
char player_error=0;
unsigned char current_score;
unsigned char high_score;


/*
 * Task for running the memory game
 *
 * TODO: Add support for keeping track of high score
 */
void Game_Task(uint_32 data)
{
  int i;

  /* Initialize variables */
  char length=1;
  char lastkey;

  printf("Starting Game Task\n");

  GetHighScore();

  while(1)
  {
    //If mode is now touch, turn on all LED's to start with
    if(mode==TOUCH)
    {
      OutputAllOn();
    }

    //Wait for Game mode to be entered
    while(mode!=GAME)
    {
      _time_delay(500);
    }

    //Reset variables
    length=1;
    current_score=0;
    player_error=0;

    for(i=0;i<LOG_LENGTH;i++)
    {
      keylog[i]=0;
    }

    //Create random sequence
    create_sequence();

    //Toggle LED's to show entered game mode
    OutputAllOff();
    ToggleAllOutput(2);
    _time_delay(500);

    //While still in game mode and the player has not made a mistake...
    while(!player_error && mode==GAME)
    {
      /* Send out sequence to LED's */
      for(i=0;i<length;i++)
      {
        SetOutput((Output_t)sequence[i], ON);
        _time_delay(250);
        SetOutput((Output_t)sequence[i], OFF);
        _time_delay(200);
      }

      /* Now get user input */
      for(i=0;i<length;i++)
      {
        //Wait for TSI touch
        WaitForTouch();

        //Get the key pressed
        lastkey=LastKeyPressed();

        //Turn on that LED
        SetOutput((Output_t)lastkey, ON);

        //Wait for release of touch
        WaitForRelease();

        //Leave on LED slightly longer so user can see which LED they hit
        _time_delay(150);
        SetOutput((Output_t)lastkey, OFF);

        //If they hit the wrong key or no longer in Game mode, set player_error=1
        if(lastkey!=sequence[i] || mode!=GAME)
        {
          player_error=1;
          break;
        }
        else
        {
          //Updated score
          current_score=length;

          //Update high score if appropriate
          if(high_score<current_score)
          {
            high_score=current_score;
            write_demo_data();
          }
        }
      }

      //If the player was correct, toggle LED's
      if(!player_error)
      {
        ToggleAllOutput(2);
        _time_delay(200);
      }

      //Increase the number of LED lights to remember
      length++;

      //If reached maximum length, toggle 10 times and reset
      if(length==LOG_LENGTH)
      {
        ToggleAllOutput(10);
        length=1;
      }
    }

    //If player error occured and we are not now in touch mode, then toggle LED's 5 times
    if(mode!=TOUCH)
    {
      ToggleAllOutput(5);
    }
  }//End WHILE

}

/*
 * Wait for touch pad to be pressed or
 *  for game mode to be exited by push button
 */
void WaitForTouch()
{
  //Reset semaphore
  touch_sem.VALUE=0;

  //Wait for semaphore to post with a timeout of 1000 ticks (5 seconds)
  //Semaphore is posted if touch pad is touched, or demo put into Touch mode
  if(_lwsem_wait_ticks(&touch_sem,1000)!= MQX_OK)
  {
    printf("Waited too long for key press\n");
    player_error=1;
  }
  //If semaphore was posted because it is no longer game mode, also set player_error=1
  else if(mode!=GAME)
  {
    player_error=1;
  }
}

/*
 * Wait for touch pad to be un-pressed
 */
void WaitForRelease()
{
  while(keypressed!=0)
  {}
}

/*******************************************************************/
/*!
 * Return value of last key pressed
 * @return Number of the last button pressed
 */
char LastKeyPressed()
{
  return (char)keylog[0] & 0x0000000F;
}

/*******************************************************************/
/*!
 * Return 1 if key is currently being pressed. 0 if no key is being pressed
 */
char KeyPressed()
{
  return keypressed & 0x0000000F;
}

/*******************************************************************/
/*!
 *  Add Key Press to Key History
 *  @param key is the key to add to queue
 */
void AddTouch(char key)
{
  unsigned char i=LOG_LENGTH-1;

  /* Shift queue over by 1 */
  while(i>0)
  {
    keylog[i]=keylog[i-1];
    i--;
  }
  keylog[0]=key;
}

/*
 * Use RNG module to create a random sequence to light up
 */
void create_sequence()
{
  int i, value;

  //Turn on RNG module and configure RNG module
  SIM_SCGC3|=SIM_SCGC3_RNGB_MASK;
  RNG_CR|=RNG_CR_MASKDONE_MASK|RNG_CR_MASKERR_MASK|RNG_CR_AR_MASK;

  //Wait for random data to be generated
  while((RNG_SR & RNG_SR_SDN_MASK)==0)
  {}

  //Assigned random data to entire sequence
  for(i=0;i<LOG_LENGTH;i++)
  {
    //Wait for RNG FIFO to be full
    while((RNG_SR & RNG_SR_FIFO_LVL(0xF))==0)
    {}
    value=(RNG_OUT%4); //Get value
    sequence[i]=value;
  }
}

/*
 * Read flash memory to read off the previous high score
 */
void GetHighScore()
{
  unsigned int *DemoData = (unsigned int *)DEMO_DATA;
  int stored_data=*DemoData;

  //If no valid data, return
  if(stored_data == 0xFFFFFFFF)
  {
    high_score=0;
    return;
  }
  high_score=(stored_data&0xFF000000)>>24;

  /* Make sure high score is not higher than maximum possible high score */
  if(high_score>LOG_LENGTH)
    high_score=0;
}
*/
#endif
