MQX_Lab - K60N512 MQX Project
=======

This is an MQX 4.1 Project built with CodeWarrior 10.6 for the PK60N512VMD100 TWR Card. An Embedded Access MQX lab given below was used as the base for this project. 

http://www.freescale.com/webapp/sps/site/training_information.jsp?code=WBT_MQX_RTOS_COURSE&fsrch=1&sr=1&pageNum=1

The MQX app incorporates input from the TSI capacitive touch pads, potentiometer, accelerometer (MMA7660), and switches. 

A Python application running on another computer reads serial data from the K60 and shows a 3D rectangle whose size, position and colour corresponds to the user input on the board.
The “controls” are as follows: 
<ul> To increase the size of the rectangle, rotate the potentiometer clockwise </ul>
<ul> To change the position, rotate the board to the desired position </ul>
<ul> To alter the colour of the rectangle, press the LED corresponding to the desired colour of the 
rectangle </ul>


