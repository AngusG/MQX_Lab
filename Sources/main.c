/****************************************************************************
* 
*   This file contains MQX only stationery code.
*
****************************************************************************/
#include "main.h"


#if !BSPCFG_ENABLE_IO_SUBSYSTEM
#error This application requires BSPCFG_ENABLE_IO_SUBSYSTEM defined non-zero in user_config.h. Please recompile BSP with this option.
#endif


#ifndef BSP_DEFAULT_IO_CHANNEL_DEFINED
#error This application requires BSP_DEFAULT_IO_CHANNEL to be not NULL. Please set corresponding BSPCFG_ENABLE_TTYx to non-zero in user_config.h and recompile BSP with this option.
#endif

/** Priority
 * 
 * High - IO, Low level communication
 * Med  - Communication protocols
 * Low  - User Interface, House keeping tasks 
 * 
 * Do not leave gaps b/w priorities!
 * Interrupts take priority over all tasks
 * Highest priority task at 8 
 * 
 */

TASK_TEMPLATE_STRUCT MQX_template_list[] = 
{ 
/*  Task number, 	Entry point, 	Stack, Pri, String, 		Auto? */
   {HEALTH_TASK,   	Health_task,   	1500,  9,   "Health_task", 	MQX_AUTO_START_TASK},
   {DISPLAY_TASK,   Display_task,   1500,  11,   "Display_task", MQX_AUTO_START_TASK},
   {ACCEL_TASK,   	Accel_task,   	1500,  10,   "Accel_task", 	MQX_AUTO_START_TASK},
   {TEMP_TASK,   	Temp_task,   	1500,  10,   "Temp_task", 	MQX_AUTO_START_TASK},
   {INPUT_TASK,   	Input_task,   	1500,  10,   "Input_task", 	MQX_AUTO_START_TASK},
   //{CAN_TASK,   	Can_task,   	1500,  10,   "Can_task", 	0},
   {UI_TASK,   		Ui_task,   		1500,  12,   "Ui_task", 	MQX_AUTO_START_TASK},
   {THEFT_TASK,   	Theft_task,   	1500,  10,   "Theft_task", 	MQX_AUTO_START_TASK},
   {0,           	0,           	0,     0,   0,      		0,                 }
};

/**
 * Stack: bytes
 * Pri: 0 = highest
 * String: name (used in TAD), some API calls
 * Attributes: Can be or'd together, ex MQX_AUTO_START_TASK | MQX_FLOATING_POINT_TASK | MQX_TIME_SLICE_TASK
 * Param: Pass a parameter to the ENTRY function. ( port_num, entry mode, ...)
 * Time Slice: measured in ticks by default, set 0 for default
 */

/** The scheduler is called whenever: 
 * 
 * The active task yields control by calling sched_yield()
 * 
 * The active task calls a blocking MQX function
 * 
 * An interrupts occurs
 * 
 * A timeslice occurs (Round Robin)
 * 
 * A higher priority task becomes ready
 * 
 */

/**
 * _task_id = _task_create(processor_number, template_index, parameter) 
 * Can have multiple instances of the same task
 * 
 * _task_destroy() - Terminate - frees all resources.
 * _task_abort() - calls exit handler
 * _task_restart()
 * 
 */
 

/* EOF */
