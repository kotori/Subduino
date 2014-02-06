// joystick_controller.ino
//  Provides the means to control the ROV from a distant location
//  using a converted PC gamepad joystick and a wireless serial adapter
//  for sending commands to the remote buoy down to the ROV.

#include <Arduino.h>
#include <Wire.h>

#include "joystick.h"

#define JOY_X_AXIS_PIN A0
#define JOY_Y_AXIS_PIN A1

const int SERIAL_BAUDRATE = 11520;
const int MAIN_LOOP_DELAY = 10;

joystick *joy;

void setup() {
  Serial.begin( SERIAL_BAUDRATE );
  joy = new joystick( JOY_X_AXIS_PIN, JOY_Y_AXIS_PIN );
  //
}

void loop() {

  int x, y;

  x = analogRead( joy->getXPin() );
  y = analogRead( joy->getYPin() );

  if( x ) {
    joy->setXPos( 102300 / x - 100 );
  }
  else {
    joy->setXPos( -1 );
  }

  if( y ) {
    joy->setYPos( 102300 / y - 100 );
  }
  else {
    joy->setYPos( -1 );
  }

  delay( MAIN_LOOP_DELAY );

}
