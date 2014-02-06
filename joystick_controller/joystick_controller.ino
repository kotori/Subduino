/*
 * joystick_controller.ino
 *  Provides the means to control the ROV from a distant location
 *  using a converted PC gamepad joystick and a wireless serial adapter
 *  for sending commands to the remote buoy down to the ROV.
 */

#include <Arduino.h>
#include <SPI.h>

#include <stdarg.h>

#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

#include "joystick.h"

const int JOY_X_AXIS_PIN = A0;
const int JOY_Y_AXIS_PIN = A1;

const int JOY_BUTTON1_PIN = 10;
const int JOY_BUTTON2_PIN = 11;
const int JOY_BUTTON3_PIN = 12;
const int JOY_BUTTON4_PIN = 13;

const int MIRF_CE_PIN = 7;
const int MIRF_CSN_PIN = 8;

const int SERIAL_BAUDRATE = 11520;
const int MAIN_LOOP_DELAY = 10;

joystick *joy;

void setup() {
  Serial.begin( SERIAL_BAUDRATE );

  /*
   * Create a new joystick object instance.
   * Takes the following args:
   *   joystick x axis pin
   *   joystick y axis pin
   *   number of joystick buttons
   *   each button pin (comma seperated)
   */
  joy = new joystick( JOY_X_AXIS_PIN, JOY_Y_AXIS_PIN, NUM_BUTTONS, 
	JOY_BUTTON1_PIN, JOY_BUTTON2_PIN, JOY_BUTTON3_PIN, JOY_BUTTON4_PIN );

  /*
   * Mirf Configuration
   */
  Mirf.cePin = MIRF_CE_PIN;
  Mirf.csnPin = MIRF_CSN_PIN;
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  // Set Mirf receiving address.
  Mirf.setRADDR( (byte *) "commr" );
  Mirf.payload = sizeof( unsigned long );

  // Write config and power up receiver.
  Mirf.config();

  Serial.println("Receiver Powered!");
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



