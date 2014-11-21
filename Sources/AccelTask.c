#include "main.h"
#include <i2c.h>
#define I2C_ACCELEROMETER_ADDRESS (0x1d<<1) //MMA8541
#define I2C_DATA_SIZE 5
FILE_PTR fd;
unsigned char recv_buffer[I2C_DATA_SIZE];
void write_I2C(int i2c_device, unsigned char reg, unsigned char value);
void read_I2C(int i2c_device, int sensor, int length);
signed char convert_accel_data(signed char input);
void InitializeI2C();
void InitializeMMA8541();
SENSOR_DATA Sensor;
/*TASK*-----------------------------------------------------
* 
* Task Name : Accel_task
* Comments :
* This is the Accelerometer task
* From TWR-K60N512-UM User Manual v1.1
* Accelerometer:
* I2C SDA -> PTD9 = I2C0_SDA
* I2C SCL -> PTD8 = I2C0_SCL
* IRQ -> PTD10 = PTD10 
*
*END*-----------------------------------------------------*/
void Accel_task(uint32_t initial_data)
{
_queue_id health_qid;
APPLICATION_MESSAGE *msg;
/* initialize I2C driver */
InitializeI2C();
/* configure the MMA8541 */
InitializeMMA8541();
health_qid = _msgq_get_id(0, HEALTH_QUEUE);
while(1){
_time_delay(500);
/* read first five registers on MMA8541 */
read_I2C( I2C_ACCELEROMETER_ADDRESS, 0x00, 5 );
Sensor.mma8541_x = convert_accel_data( (uint8_t)recv_buffer[0] );
Sensor.mma8541_y = convert_accel_data( (uint8_t)recv_buffer[1] );
Sensor.mma8541_z = convert_accel_data( (uint8_t)recv_buffer[2] );
Sensor.mma8541_status = recv_buffer[3];
msg = _msg_alloc_system(sizeof(*msg));
if( msg != NULL){
msg->HEADER.TARGET_QID = health_qid;
msg->MESSAGE_TYPE = ACCEL_MESSAGE;
msg->DATA = 0;
_msgq_send(msg);
}
}
}
void InitializeI2C()
{
 /* Open the I2C driver, and assign a I2C device handler*/
 fd = fopen ("i2c0:", NULL);
 if (fd == NULL)
 {
 printf ("Failed to open the I2C driver!\n");
 _time_delay (200L);
 _mqx_exit (1L);
 }
 /* Set I2C into Master mode */
 ioctl (fd, IO_IOCTL_I2C_SET_MASTER_MODE, NULL);
}
void InitializeMMA8541()
{
 /* Configure the MMA8541 in standby mode*/
 /* Data rate = 6.25 Hz
 * ASLP_RATE0 = 12.5 Hz 
 */
 write_I2C( I2C_ACCELEROMETER_ADDRESS, 0x2A, 0x6E );
 /* Active mode in CTRL_REG1 */
 write_I2C( I2C_ACCELEROMETER_ADDRESS, 0x2A, 0x01 ); 
}
/* Function for writing data to I2C Sensor */
void write_I2C(int i2c_device_address, unsigned char reg, unsigned char value)
{
 unsigned char data[2];
 data[0]=reg; //Sensor register
 data[1]=value; //Byte of data to write to register
 /* Set the destination address */
 ioctl (fd, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS, &i2c_device_address);
 /* Write 2 bytes of data: the desired register and then the data */
 fwrite (&data, 1, 2, fd); //data to write, size of unit, # of bytes to write, I2C device handler
 fflush (fd);
 /* Send out stop */
 ioctl (fd, IO_IOCTL_I2C_STOP, NULL);
}
/* Function for reading data from I2C. Data placed in recv_buffer */
void read_I2C(int i2c_device_address, int sensor, int length)
{
 int n = length;
 /* the starting register for the particular sensor requested */
 unsigned char reg=sensor;
 /* set the I2C destination address */
 ioctl( fd, IO_IOCTL_I2C_SET_DESTINATION_ADDRESS,&i2c_device_address );
 /* tell the QE96 which sensor data to get */
 fwrite( &reg, 1, 1, fd); //data to write, size of unit, # of bytes to write, I2C device handler
 /* wait for completion */
 fflush( fd );
 /* do a repeated start to avoid giving up control */
 ioctl( fd, IO_IOCTL_I2C_REPEATED_START, NULL );
 /* set how many bytes to read */
 ioctl( fd, IO_IOCTL_I2C_SET_RX_REQUEST, &n );
 /*
 * read n bytes of data and put it into the recv_buffer
 * buffer to read data into, size of unit, # of bytes to read, I2C 
device handler
 */
 fread( &recv_buffer, 1, n, fd );
 /* wait for completion */
 fflush( fd );
 /* send out stop */
 ioctl( fd, IO_IOCTL_I2C_STOP, NULL );
