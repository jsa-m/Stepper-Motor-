# Stepper-Motor-
This project provides functions to drive a 5V stepper motor (28BYJ-48) with the ULN2003 
Stepper Motor Driver and an Arduino Uno.

## The 28BYJ-48
The stepper motor it’s a DC motor that can control the angular position of the rotor without closed feedback loop control. It’s a hybrid stepper motor that has 4 phases and a stride angle of 5.625º/32 which provides an accuracy of 0.1758º per step.

## The ULN2003
It’s an IC with seven Darlington pair that provides the current to energize the inductors of the stepper, when the corresponding input of the Darlington has a high signal provided by the microcontroller. 

## Operation modes.
### Full Step:
If we switch on two inductors at a time in sequence the stepper will provide full torque and 0.1758º per step. 
### Half Step:
In this mode there are on or two inductors at a time it provides an accuracy of half of the step 0.0878º/step, although the torque will decrease when only one indicator is activated.
### Functions:
Turn -> Rotate the stepper motor forward if RPM or degrees are positive or backwards if ROM or degrees are negative, with one inductor each step, numSteps = 4, or two inductors each step, numSteps = 8.
step_width -> Depending on the number of inductors active and the desired RPM obtain the step_with in microseconds necessary to obtain the RPM.
degrees_to_steps -> Converts degrees to steps depending on the running mode (4 or 8 steps).
num_turns -> Returns the current turns of the stepper.
num_steps -> Returns the current steps of the stepper.
The Stepper_Motor.ino provides an example of application with this functions, the stepper will give 4 turns at 12 rpm clockwise, 4 turns at 5 rpm counter clockwise, a 180º degrees turn and a 90º degree turn. 
