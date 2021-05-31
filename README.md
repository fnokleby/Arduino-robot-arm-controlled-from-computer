# Arduino arm controlled from pc running python script.

This project is a prototype robot arm and controller. The robot it self is made out of an old pizza box, and uses servos attached to an arduino. The arduino recives data over serial from a computer. The computer runs a python script and has a very rudimentary gui.  

## Parts
* SG-5010 Tower Pro Servo
* SKM-S2309s
* Arduino (I used an UNO)
* A computer capable of running a .py script.
* Usb cable.
* 12V power supply (Decent amperage, servos need quite a lot).
* A pizza box.
* Some extra cardboard for the construction, I used another pizza box.

## Images
Image number one:
![Image 2](https://i.imgur.com/aTVj5QT.jpg)

# TODO

## Done
- [x] Switch to json (Why didn't i think of this?)
- [x] Play thru all posiotions, with custom wait times between each one.
- [X] Better GUI. (I added an electron app that uses three.js)
- [x] More reliable communication between python and arduino.

## Not started
- [ ] Add a "grabber" of sorts to arm (if this is possible within the weight limit)
- [ ] Switches, LED's and other status indicating things (like 7 segment displays, button to go thru pre programmed program, and button to execute saved positions) to the pizza box.

## Next up
- [ ] Add last part of arm. 

## Work in progress
- [ ] 3d gui

## Back burner
  - [x] Save current position of arms, and move to that position. (Not on node gui)

## Known bugs

## Solved bugs
- [x] "Go through all" clears all saved positions, I have no clue why. REASON: I forgot the "break;" after the case containing the "Go through all" :)