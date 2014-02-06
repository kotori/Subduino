
#include <Arduino.h>
#include <Wire.h>

#include "globals.h"
#include "mitsumi_m42sp_4np.h"

#define MAIN_LOOP_DELAY 100
#define NUM_STEPPERS 2

int queuedAction = CMD_STANDBY;
boolean queueChanged = false;

Mitsumi_M42SP_4NP *stepper[NUM_STEPPERS];

void receiveEvent( int numBytes ) {

  while( Wire.available() )
  {
    queuedAction = Wire.read();
    queueChanged = true;
  }

}

void processQueuedCmd( int cmd ) {
  switch( cmd ) {
    case CMD_ROTATE_UPWARDS:
      stepper[HORIZONTAL_STEPPER]->phaseForward();
      break;

    case CMD_ROTATE_DOWNWARDS:
      stepper[HORIZONTAL_STEPPER]->phaseReverse();
      break;

    case CMD_ROTATE_LEFT:
      stepper[VERTICAL_STEPPER]->phaseForward();
      break;

    case CMD_ROTATE_RIGHT:
      stepper[VERTICAL_STEPPER]->phaseReverse();
      break;
  }
}

void setup() {
  Wire.begin( I2C_STEPPER_CONTROLLER );

  stepper[HORIZONTAL_STEPPER] = new Mitsumi_M42SP_4NP(
	STEPPER_1_C1, STEPPER_1_C2, STEPPER_1_C3, STEPPER_1_C4 );

  stepper[VERTICAL_STEPPER] = new Mitsumi_M42SP_4NP(
	STEPPER_2_C1, STEPPER_2_C2, STEPPER_2_C3, STEPPER_2_C4 );

  Wire.onReceive( receiveEvent ); // register event

}

void loop() {

  if( queueChanged == true ) {
    processQueuedCmd( queuedAction );
    queueChanged = false;
  }

  delay( MAIN_LOOP_DELAY );
}

