import serial

ser = serial.Serial(
    port='COM5',\
    baudrate=115200,\
    parity=serial.PARITY_NONE,\
    stopbits=serial.STOPBITS_ONE,\
    bytesize=serial.EIGHTBITS,\
        timeout=0)
		
		
print("connected to: " + ser.portstr)
count=1	
line = ""
while True:
    for c in ser.read():
        #print(chr(c))
        line=line+chr(c)
        if (chr(c) == '\n'):
            print( line)
            line = ""
            break
# while True:
	
    # for line in ser.read():

        # print(str(count) + str(': ') + chr(line) )
        # count = count+1		



# while True:
    # line=ser.readline()
    # if(len(line)!=0):
        # print(line)
    

ser.close()