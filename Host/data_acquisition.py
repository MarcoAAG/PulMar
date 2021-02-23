import serial
import numpy as np
import matplotlib.pyplot as plt

port = serial.Serial('/dev/ttyUSB0')
i=0
while(1):
    raw_data = port.readline()
    data = raw_data.decode("utf-8")
    data_dec = int(data,16)
    # print(data_dec)
    i+=1
    plt.scatter(i,int(data_dec))
    # plt.plot(i,data_dec)
    plt.draw()
    plt.pause(0.1)


plt.show()
port.close()

