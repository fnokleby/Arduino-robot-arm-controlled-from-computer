# Importing Libraries
import serial
import tkinter as tk
import time

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)

def write_slogan():
    print("Tkinter is easy to use!")

root = tk.Tk()
frame = tk.Frame(root)
frame.pack()

# set window title
root.wm_title("Robot controll")

slogan = tk.Button(frame,
                   text="Hello",
                   command=write_slogan)
slogan.pack(side=tk.LEFT)

# show window
root.mainloop()

#while True:
    #num = input("Enter a number: ") # Taking input from user
    #arduino.write(bytes(num, 'utf-8'))