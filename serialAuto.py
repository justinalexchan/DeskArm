from serial import Serial
from pynput import keyboard
import serial
import math
import time

s = serial.Serial("COM4", 115200)

print("Opening: " + s.name)

s.write(b'1')     
newLine = 2
text = ""

while newLine != 0:
        x = s.read()        # read one byte
        c = x.decode()      # convert byte type to str
        text += c
        if(c=="\n"):
            print(text)
            newLine-=1


def readFile():
    inFile = open("movements.txt", "r")
    movements = inFile.readline()
    for i in movements:
        s.write(i.encode())
        time.sleep(0.02)
    inFile.close()

readFile()