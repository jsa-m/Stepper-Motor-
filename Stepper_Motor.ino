/*******************************************************************
/* file name : stepper.c 
/*******************************************************************
/* description    : Example to test stepper.c function
/* programmer     : Joaquin Sopena 
/* lenguage       : ANSI C 
/* date           : November 14, 2020
/********************************************************************/
#include "stepper.h"

float RPM = 12.0;               //Desired RPM for the initial stepper motor (Limited to 12 RPM)
unsigned long t;                //Delay between steps to obtain the desired RPM       
int numSteps = 8;               // 4 or 8 operation mode
int phase = 0;                  
unsigned long counter = 0;
int total_turns = 0;
int deg_step = 0;
int step_counter = 0;




void setup() 
{
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  t = step_width(RPM, numSteps); //Initial speed
}

void loop() 
{
  total_turns = num_turns();
  //Serial.println(total_turns);
  if(phase == 0){
    if(total_turns < 4)
    {
      turn(numSteps, RPM);              //4 turns clockwise 12 RPM 
    }
    else{
      phase = 1;
      RPM = -5;
      t = step_width(RPM, numSteps);
    }
  }

  if(phase == 1)
  {
    if(total_turns > 0)
    {
      turn(numSteps, RPM);             //4 turns counter clockwise 5 RPM 
    }
    else{
      phase = 2;
      RPM = 7;
      t = step_width(RPM, numSteps);
      deg_step = degrees_to_steps(180, numSteps);
    }
  }
    if(phase == 2){
      if(step_counter <= deg_step){
        turn(numSteps, deg_step);             //Turn 180 degrees at 7 RPM
        step_counter = step_counter + 1;
      }
      else{
        phase = 3;
        RPM = -2;
        t = step_width(RPM, numSteps);
        deg_step = degrees_to_steps(90, numSteps);    //Turn -90º at 2 RPM
        step_counter = 0;
      }
    }
    if(phase == 3){
      if(step_counter <= deg_step){
        turn(numSteps, RPM);
        step_counter = step_counter + 1;
        }
      else{
        
      }
    }
    delay_micros(t);
  }


void delay_micros(unsigned long period)
{
  counter = micros() + period;
  while(micros() < counter)
  {
    
  }
}
