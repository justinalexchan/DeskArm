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

def on_press(key):
    movFile = open("movements.txt", "a") #Automation feature in development
    if key == keyboard.Key.esc:
        return False  # stop listener
        movFile.close()

    try:
        k = key.char  # single-char keys
        movFile.write(k)
        s.write(k.encode())
    except:
        if key == keyboard.Key.delete:
            movFile = open("movements.txt", "w")
        else:
            print("Invalid Input!")

    

while newLine != 0:
        x = s.read()        # read one byte
        c = x.decode()      # convert byte type to str
        text += c
        if(c=="\n"):
            print(text)
            newLine-=1

listener = keyboard.Listener(on_press=on_press)
listener.start()  # start to listen on a separate thread
listener.join()  # remove if main thread is polling self.keys
        

print("Closing: " + s.name)
s.close()
