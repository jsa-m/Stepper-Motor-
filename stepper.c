/*******************************************************************
/* file name : stepper.c 
/*******************************************************************
/* description    : Basic functions to work with the 28BYJ-48 – 5V 
/*                  Stepper Motor and the ULN2003 Stepper Motor 
/*                  Driver
/* programmer     : Joaquin Sopena 
/* lenguage       : ANSI C 
/* date           : November 14, 2020
/********************************************************************/

#include "Arduino.h"

/******************************************************************************/
/*                        Local variables                                     */
/******************************************************************************/

const unsigned int sequence4Step[] = { B0011, B0110, B1100, B1001 };
//switch on one inductor each step, precision 0.1757º/step
const unsigned int sequence8Step[] = { B0001, B0011, B0010, B0110, B0100, B1100, B1000, B1001 };
//switch on two inductor each step, precision 0.0878º/step
const unsigned int pinMotor1 = 8; //IN1 ULN2003 Stepper Motor Driver
const unsigned int pinMotor2 = 9; //IN2 ULN2003 Stepper Motor Driver
const unsigned int pinMotor3 = 10; //IN3 ULN2003 Stepper Motor Driver
const unsigned int pinMotor4 = 11; //IN4 ULN2003 Stepper Motor Driver

int next_phase_seq = 0;
signed int turns = 0;
int current_step = 0; 

/******************************************************************************/
/*                       Functions                                            */
/******************************************************************************/

void turn (int numSteps, int dir)
{
  /* Sequences to rotate the stepper motor forward if RPM or degress are positive 
     or backwards if ROM or degrees are negative, with one inductor each step, 
     numSteps = 4, or two inductors each step, numSteps = 8 */ 
  
  if(numSteps == 4)
  {
    digitalWrite(pinMotor1, bitRead(sequence4Step[next_phase_seq], 0));
    digitalWrite(pinMotor2, bitRead(sequence4Step[next_phase_seq], 1));
    digitalWrite(pinMotor3, bitRead(sequence4Step[next_phase_seq], 2));
    digitalWrite(pinMotor4, bitRead(sequence4Step[next_phase_seq], 3)); 
    if(dir >= 0)
    {
      next_phase_seq = next_phase_seq + 1;
      if(next_phase_seq > 3)
      {
        next_phase_seq = 0;
      }
      if(current_step > 2047)
      {
        turns = turns + 1;
        current_step = 0;
      } 
    }
    if(dir < 0 )
    {
      next_phase_seq = next_phase_seq - 1;
      if(next_phase_seq < 0)
      {
        next_phase_seq = 3;
      }
      if(current_step > 2047)
      {
        turns = turns - 1;
        current_step = 0;
      } 
    }
    current_step = current_step + 1;
  }

  if(numSteps == 8)
  {
    digitalWrite(pinMotor1, bitRead(sequence8Step[next_phase_seq], 0));
    digitalWrite(pinMotor2, bitRead(sequence8Step[next_phase_seq], 1));
    digitalWrite(pinMotor3, bitRead(sequence8Step[next_phase_seq], 2));
    digitalWrite(pinMotor4, bitRead(sequence8Step[next_phase_seq], 3)); 
    if(dir >= 0)
    {
      next_phase_seq = next_phase_seq + 1;
      if(next_phase_seq > 7)
      {
        next_phase_seq = 0;
      }
      if(current_step > 4095)
      {
        turns = turns + 1;
        current_step = 0;
      } 
    }
    if(dir < 0)
    {
      next_phase_seq = next_phase_seq - 1;
      if(next_phase_seq < 0)
      {
        next_phase_seq = 7;
      }
      if(current_step > 4095)
      {
        turns = turns - 1;
        current_step = 0;
      }
    }
    current_step = current_step + 1;
  } 
}

unsigned long step_width(float RPM, int numSteps)
{
   /* Depending on the number of inductors active and the desired 
      RPM obtain the step_with in microseconds necessary to obtain
      the RPM */ 

  float step_time = 0;
  float abs_rpm = 0;
  if(RPM < 0)
  {
    abs_rpm = -RPM;
  }
  else
  {
    abs_rpm = RPM;
  }
  if(numSteps == 4){
    step_time = 29296.875/abs_rpm;
  }
  else if(numSteps == 8)
  {
    step_time = 14648.4375/abs_rpm;
  }
  return (unsigned long)step_time;
}

int degrees_to_steps(int degree, int numSteps)
{
  /* Converts degrees to steps depending on the 
     running mode (4 or 8 steps) */ 
  float steps = 0;
  if(numSteps == 4)
  {
    steps = 5.68888*degree;
  }
  if(numSteps == 8)
  {
    steps = 11.37777*degree;
  }
  return (int)steps;
}

signed int num_turns()
  /* Returns the current turns of the stepper*/ 
{
  return turns;
}

int num_steps()
  /* Returns the current steps of the stepper*/ 
{
  return current_step;
}

 
