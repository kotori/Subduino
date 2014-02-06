/* Subduino - Arduino Submarine Sketch
 *  TODO!
 *   As the mitsumi library is actually going to be
 *   controlled on a slave chip, its code should be
 *   removed from this sketch shortly.
 */

// I2C Mapping:
// PC1 - PCINT17, SDA [PIN17]
// PC0 - PCINT16, SCL [PIN16]

#include <Arduino.h>
#include <Wire.h>

#include "globals.h"

const int LOOP_DELAY_TIME = 100;
const int SERIAL_BAUDRATE = 9600;

int queuedAction = CMD_STANDBY;
int currCMD = CMD_STANDBY;
boolean haveNewCmd = false;

void sendCmd( int msg, int member ) {
  Wire.beginTransmission( member );
  Wire.write( msg );
  Wire.endTransmission();
}

// Perform an action based upon the passed command.
// This can be gathering sensor data or sending an action
// to one of the slave I2C devices.
void doLogic( int cmd ) {

  #if defined(DEBUGGING_MODE) && DEBUGGING_MODE > 0
    Serial.print( "Processing Command: " );
    Serial.println( cmd );
  #endif

  switch( cmd ) {
    case CMD_STANDBY:
      // Do nothing.
      break;

    case CMD_MOVE_FORWARD:
      // Send the signal to the thruster slave to
      //  drive the motors forward.
      sendCmd( cmd, I2C_THRUST_CONTROLLER );
      break;

    case CMD_MOVE_REVERSE:
      // Send the signal to the thruster slave to
      //  drive the motors in reverse.
      sendCmd( cmd, I2C_THRUST_CONTROLLER );
      break;

    case CMD_ROTATE_UPWARDS:
      sendCmd( cmd, I2C_STEPPER_CONTROLLER );
      break;

    case CMD_ROTATE_DOWNWARDS:
      sendCmd( cmd, I2C_STEPPER_CONTROLLER );
      break;

    case CMD_ROTATE_LEFT:
      sendCmd( cmd, I2C_STEPPER_CONTROLLER );
      break;

    case CMD_ROTATE_RIGHT:
      sendCmd( cmd, I2C_STEPPER_CONTROLLER );
      break;

  }
  haveNewCmd = false;
}

void setup() {

  // Start the serial interface at the specified baudrate.
  Serial.begin( SERIAL_BAUDRATE );

  // Join the I2C bus with the master designation.
  Wire.begin( I2C_MASTER );
}

void loop() {

  // TODO!
  //  Query the I2C sensor array slave for
  //   updated information.

  // Only execute this function if we
  //  have a new command to process.
  if( haveNewCmd ) {
    doLogic( queuedAction );
  }

  delay( LOOP_DELAY_TIME );
}

