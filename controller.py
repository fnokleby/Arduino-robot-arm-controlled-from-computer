# Importing Libraries
import serial
import tkinter as tk
import time

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)

def test_arm():
    print("Sending command...")
    arduino.write(bytes('1', 'utf-8'))
    print('Command sent!')

def reset_arm():
    print("Sending command...")
    speed = str(speedSlider.get())
    arduino.write(bytes('2*90' , 'utf-8'))
    print('Command sent!')

def send_arm_to_pos():
    base = str(baseSlider.get())
    arm1 = str(arm1Slider.get())
    speed = str(speedSlider.get())
    fullCommand = '3:' + base + '-' + arm1 + '*' + speed
    print(fullCommand)
    arduino.write(bytes(fullCommand, 'utf-8'))

root = tk.Tk()
root.geometry('500x500')
frame = tk.Frame(root)
frame.pack()

# set window title
root.wm_title("Robot controll")

testButton = tk.Button(frame, text="Test arm", command=test_arm)
testButton.grid(column=0, row = 1)

returnButton = tk.Button(frame, text="Return arm to 0", command=reset_arm)
returnButton.grid(column=1, row = 1)

posButton = tk.Button(frame, text="Send arm to cords", command=send_arm_to_pos)
posButton.grid(column=2, row = 1)

baseSlider = tk.Scale(frame, from_=0, to=180, orient="horizontal", label="Base servo", )
baseSlider.grid(column=0, row = 2)

arm1Slider = tk.Scale(frame, from_=0, to=85, orient="horizontal", label="Arm 1", )
arm1Slider.grid(column=1, row = 2)

arm2Slider = tk.Scale(frame, from_=0, to=85, orient="horizontal", label="Arm 2", )
arm2Slider.grid(column=2, row = 2)

speedSlider = tk.Scale(frame, from_=1, to=100, orient="horizontal", label="Speed (%)", )
speedSlider.grid(column=3, row = 2)

# show window
root.mainloop()

#while True:
    #num = input("Enter a number: ") # Taking input from user
    #arduino.write(bytes(num, 'utf-8'))