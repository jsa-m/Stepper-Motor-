/*******************************************************************
/* file name : stepper.h 
/*******************************************************************
/* description    : Basic functions to work with the 28BYJ-48 – 5V 
/*                  Stepper Motor and the ULN2003 Stepper Motor 
/*                  Driver
/* programmer     : Joaquin Sopena 
/* lenguage       : ANSI C 
/* date           : November 14, 2020
/********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************/
/*                        Exported functions                                  */
/******************************************************************************/

void turn(int numSteps, int dir);

unsigned long step_width(float RPM, int numSteps);

int degrees_to_steps(int degree, int numSteps);

signed int num_turns(void);

int num_steps(void);

#ifdef __cplusplus
}
#endif
