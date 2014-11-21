import serial
import re
from visual import *
import numpy
ser = serial.Serial(
	port='COM5',\
	baudrate=115200,\
	parity=serial.PARITY_NONE,\
	stopbits=serial.STOPBITS_ONE,\
	bytesize=serial.EIGHTBITS,\
		timeout=0)
		
		
print("connected to: " + ser.portstr)
display(title='K60 by group 2')
count=0
x=0
y=0
z=0
size=0
c=0
co=color.red
wallRoof = box(pos=(0,-50,0), size=(300,8,60), color=color.green)
values=[]
wallRoof.velocity=vector(0,0,0)
velocity=vector(1,1,1)
print (velocity)
line = ""
while True:
	for c in ser.read():
		
		line=line+chr(c)
		if (chr(c) == 'W'):
			values=re.split(';|W|\r|\n| ',line)
			if(count!=0):
				x=float(values[2])
				y=float(values[3])		
				z=float(values[4])
				size=float(values[5])
				c=float(values[6])
				
				if(c!=0):
					if (c==1):		
						co=color.red
					elif(c==2):
						co=color.yellow
					elif(c==3):
						co=color.green
					elif(c==4):		
						co=color.blue
						
				wallRoof.color=co
				wallRoof.width=size/10
				velocity=vector(0,0,0)
				wallRoof.pos=velocity
				if(abs(x)>95 ):
					
					wallRoof.rotate(angle=numpy.radians(45),axis=(1,0,0))
				elif(abs(y)>95):
					wallRoof.rotate(angle=numpy.radians(45),axis=(0,1,0))
				elif(abs(z)>95):	
					wallRoof.rotate(angle=numpy.radians(45),axis=(0,0,1))
				# else:	
					# velocity=vector(0,-50,0)
					# wallRoof.pos=velocity
					
				# wallRoof.pos=wallRoof.velocity
				# wallRoof.velocity=vector(0,0,0)
			
			count+=1
			print(line)
			line = ""
			break
    

ser.close()
