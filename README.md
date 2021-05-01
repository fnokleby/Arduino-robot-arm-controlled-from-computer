# Arduino arm controlled from pc running python script.

This project is a prototype robot arm and controller. The robot it self is made out of an old pizza box, and uses servos attached to an arduino. The arduino recives data over serial from a computer. The computer runs a python script and has a very rudimentary gui.  

## Parts
* SG-5010 Tower Pro Servo
* SKM-S2309s
* Arduino (I used an UNO)
* A computer capable of running a .py script.
* Usb cable.
* 12V power supply (Decent amperage, servos need quite a lot at times).
* A pizza box.
* Some extra cardboard for the construction, I used another pizza box.

## Images
Image number one:
![Image 2](https://i.imgur.com/aTVj5QT.jpg)

## TODO

- [x] Switch to json (Why didn't i think of this?)
- [ ] Save current position of arms, and move to that position.
- [ ] Play thru all posiotions, with custom wait times between each one.
- [ ] Better GUI.
- [x] More reliable communication between python and arduino.
- [ ] Add last part of arm. 
- [ ] Add a "grabber" of sorts to arm (if this is possible within the weight limit)
- [ ] Switches, LED's and other status indicating things (like 7 segment displays, button to go thru pre programmed program, and button to execute saved positions) to the pizza box.