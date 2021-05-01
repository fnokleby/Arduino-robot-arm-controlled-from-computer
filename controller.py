# Importing Libraries
import serial
import tkinter as tk
import time
import json

arduino = serial.Serial(port='COM4', baudrate=115200, timeout=.1)

def sendJson(num , baseDegrees = None, arm1Degrees = None, delay = "10"):
    tempDict = {
        "action": num,
        "baseDegrees": baseDegrees,
        "arm1Degrees": arm1Degrees,
        "speed": delay
    }
    jsonData = json.dumps(tempDict)
    print(jsonData)

    print("Sending JSON...")
    arduino.write(bytes(jsonData, 'utf-8'))
    print('JSON sent!')

def test_arm():
    sendJson(1, None, None, 10)

def reset_arm():
    sendJson(2, None, None, 10)

def send_arm_to_pos():
    base = str(baseSlider.get())
    arm1 = str(arm1Slider.get())
    delay = str(speedSlider.get())
    sendJson(3, base, arm1, delay)

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

baseSlider = tk.Scale(frame, from_=1, to=180, orient="horizontal", label="Base servo", )
baseSlider.grid(column=0, row = 2)

arm1Slider = tk.Scale(frame, from_=1, to=85, orient="horizontal", label="Arm 1", )
arm1Slider.grid(column=1, row = 2)

arm2Slider = tk.Scale(frame, from_=1, to=85, orient="horizontal", label="N/A", )
arm2Slider.grid(column=2, row = 2)

speedSlider = tk.Scale(frame, from_=1, to=50, orient="horizontal", label="Servo Delay (ms)", )
speedSlider.set(10)
speedSlider.grid(column=3, row = 2)

# show window
root.mainloop()

#while True:
    #num = input("Enter a number: ") # Taking input from user
    #arduino.write(bytes(num, 'utf-8'))