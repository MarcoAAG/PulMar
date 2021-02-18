import serial

port = serial.Serial('/dev/ttyUSB0')
while(1):
    data = port.readline()
    print(chr(data[0]))
    
port.close()

