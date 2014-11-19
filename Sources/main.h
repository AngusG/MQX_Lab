#ifndef __main_h_
#define __main_h_
#include <mqx.h>
#include <bsp.h>
#include <shell.h>
#define APPLICATION_HAS_SHELL

/* My includes */
#include <stdint.h>
#include <message.h>
#include <lwevent.h> //lab 7
#include <lwtimer.h> //lab 8
#include <klog.h> //lab10

/* Add legacy support (MQX 3.8 -> 4.1)*/ 
#include <psptypes_legacy.h>

/* Lab 7 - defines */
#define SW1_EVENT 0x00000001
#define SW2_EVENT 0x00000002
/* Lab 8 - defines */
#define ADC_TIMER_EVENT 0x00000004
/* Add TSI */
#define TOUCH1_EVENT 0x00000008 //bit 3
#define TOUCH2_EVENT 0x00000010 //bit 4
#define TOUCH3_EVENT 0x00000020 //bit 5
#define TOUCH4_EVENT 0x00000040 //bit 6

#define DEMO_DATA 0x0007F000

/* Sensor Struct */
typedef struct
{
  int_8 mma7660_x;
  int_8 mma7660_y;
  int_8 mma7660_z;
  uint_8 mma7660_status;
  int_8 pot;
  int_8 temp_int;
  int_8 temp_dec;
} SENSOR_DATA;

/* Mode enum */
typedef volatile enum {
   TOUCH=0,
   TILT,
   GAME,
   MAX_MODES
} DEMO_MODE;

/* Global Variables */
extern SENSOR_DATA Sensor;
extern DEMO_MODE mode;
extern LWSEM_STRUCT touch_sem;
extern char print_accel;
extern unsigned char current_score;
extern unsigned char high_score;

/*
uint_16  g16ElectrodeTouch[16] = {0};
uint_16  g16ElectrodeBaseline[16] = {0};
uint_32  g32DebounceCounter[16] = {DBOUNCE_COUNTS};*/


typedef enum {
	HEALTH_TASK=1,
	DISPLAY_TASK,
	ACCEL_TASK,
	TEMP_TASK,
	INPUT_TASK,
	UI_TASK,
	THEFT_TASK
} TASK_TEMPLATE_INDEX_T;

/* Task declarations */
extern void Health_task(uint32_t);
extern void Display_task(uint32_t);
extern void Accel_task(uint32_t);
extern void Temp_task(uint32_t);
extern void Input_task(uint32_t);
//extern void Can_task(uint32_t);
extern void Ui_task(uint32_t);
extern void Theft_task(uint32_t);

/* Task Handler declarations */
extern void Can_Task_Exit_Handler(void); 

typedef enum {
	TEMP_MESSAGE=1,
	ACCEL_MESSAGE, 
	//INPUT_MESSAGE, // Per Lab 5 requirements
	SW1_Message,
	SW2_Message,
	ADC_READ_MESSAGE,
	TOUCH_MESSAGE, 
	TIMER_MESSAGE, 
	ISR_MESSAGE, 
	HEALTH_MESSAGE, 
	UI_MESSAGE, 
	DISPLAY_MESSAGE
} APPLICATION_MESSAGE_TYPE_T;

typedef struct {
	MESSAGE_HEADER_STRUCT HEADER;
	APPLICATION_MESSAGE_TYPE_T MESSAGE_TYPE;
	uint32_t DATA;	
} APPLICATION_MESSAGE;


/* Enum for message queue IDs */
typedef enum {
	CAN_QUEUE,
	HEALTH_QUEUE,	
	DISPLAY_QUEUE,
	THEFT_QUEUE
} APPLICATION_QUEUE_T;

/*
typedef struct
{
  uint8_t mma7660_x;
  uint8_t mma7660_y;
  uint8_t mma7660_z;
  unsigned char mma7660_status;
  uint8_t pot;
  uint8_t temp_int;
  uint8_t temp_dec;
} SENSOR_DATA;*/


/* PPP device must be set manually and 
** must be different from the default IO channel (BSP_DEFAULT_IO_CHANNEL) 
*/
#define PPP_DEVICE      "ittyb:" 

/*
** Define PPP_DEVICE_DUN only when using PPP to communicate
** to Win9x Dial-Up Networking over a null-modem
** This is ignored if PPP_DEVICE is not #define'd
*/
#define PPP_DEVICE_DUN  1

/*
** Define the local and remote IP addresses for the PPP link
** These are ignored if PPP_DEVICE is not #define'd
*/
#define PPP_LOCADDR     IPADDR(192,168,0,216)
#define PPP_PEERADDR    IPADDR(192,168,0,217)

/*
** Define a default gateway
*/
#define GATE_ADDR       IPADDR(192,168,0,1)

#endif /* __main_h_ */

