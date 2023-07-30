# Final Project: Digital Safe

## Instructions (From memory): 
- Create a program using C++ using the Arduino Uno and its various components.
- Make it practical and uniquely yours.

## Final Design:

<p align="center">
<img width="800" src="https://github.com/matthewantonis-georgiancollege/IOT_COMP1045/assets/122380719/49def426-fda2-4f15-9345-886fc656487d">
<p/>

Link to the design in TinkerCAD: [LINK](https://www.tinkercad.com/things/4HcGyqs16G0?sharecode=ohGSKfeaeGRYHQX-cUbdTRMAE0nOObObA9wXjxrvxVI)

## Intended purpose of the Project:
This digital safe project is designed to simulate a secure, password-protected safe that can store a virtual "bank balance" representing money held in the safe. The project uses an Arduino microcontroller, an LCD screen, a keypad, and a servo motor to simulate the functionality of a real safe.

## To operate the safe: 
- Begin by entering the appropriate numbers or letters on the Keypad to both set and unlock it. 
- The maximum amount of Numbers and characters in a password is 4. 
- Press the "#" key to confirm your input.
- Next, select from the available options by choosing A, B, or C.
  - These correspond to the actions of depositing, withdrawing, or logging off, respectively.
- When making a deposit or withdrawal, use the numbers on the Keypad to indicate the desired amount.
  - The maximum amount that can be deposited or withdrawn is $999,999,999.
  - It's important to note that you won't be able to withdraw an amount greater than the cash currently held in the safe.
- When using "C" the logoff option. The servo will turn simulating the locking of the safe.
- The LCD will then allow you to unlock it by reentering your previously set password.
- Once again, confirm your selection by pressing the "#" key.
- The program will continue to run in a loop until you manually stop the simulation, ensuring uninterrupted operation of the safe.

## Notes: 
- Created in TinkerCAD.

### Assignment Due Date: ~ Late April 2023
### Mark Received: ~95%
- Instructor stated I only lost points on creativity 
