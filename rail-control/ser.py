import serial

ser = serial.Serial('/dev/ttyUSB0',115200)

ser.write("L10000")

#while 1 :
#    print(ser.readline())
