/*
 * joystick_controller.ino
 *  Provides the means to control the ROV from a distant location
 *  using a converted PC gamepad joystick and a wireless serial adapter
 *  for sending commands to the remote buoy down to the ROV.
 *
 * Pin mapping for nRF24L01+ to Arduino:
 *   Arduino pins     nRF radio pins
 *   GND (-)		1
 *   3v3 (+)		2
 *   D9	(CE)		3
 *   D10 (CSN)	 	4
 *   D13 (SCK)	 	5
 *   D11 (MOSI)		6
 *   D12 (MISO)		7
 */

#include <Arduino.h>
#include <SPI.h>

#include "globals.h"
#include "Mirf.h" // Ref: https://github.com/aaronds/arduino-nrf24l01
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"

#include "joystick.h"

// Joystick axis pins.
const int JOY_X_AXIS_PIN = A0;
const int JOY_Y_AXIS_PIN = A1;

// Joystick button pins.
const int JOY_BUTTON1_PIN = 8;
const int JOY_BUTTON2_PIN = 7;
const int JOY_BUTTON3_PIN = 6;
const int JOY_BUTTON4_PIN = 5;

// Mirf library pins.
const int MIRF_CE_PIN = 9;
const int MIRF_CSN_PIN = 10;

const int SERIAL_BAUDRATE = 9600;
const int MAIN_LOOP_DELAY = 10;

joystick *joy;

void setup() {
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

  // Set Mirf transmit address.
  Mirf.setTADDR((byte *)"comms");

 /*
  * Set the payload length to sizeof(unsigned long) the
  * return type of millis().
  *
  * Note: payload on client and server must be the same.
  */
  Mirf.payload = 1;

  // Write channel and payload config then power up receiver.
  Mirf.config();

  // Set 1MHz data rate - this increases the range slightly
  Mirf.configRegister( RF_SETUP, 0x06 );

#ifdef DEBUGGING_MODE
  // Initialize serial interface for debugging.
  Serial.begin( SERIAL_BAUDRATE );

  Serial.println("Receiver Powered!");
#endif
}

void sendWirelessCmd( byte cmd ) {
  Mirf.send( (byte *) &cmd );

#ifdef DEBUGGING_MODE
  Serial.print( "Sending: " );
  Serial.println( cmd );
#endif  

  // Do nothing while the command is being transmitted.
  while( Mirf.isSending() ) {
    //
  }
}

void loop() {
  unsigned long data;

  // Store the current x and y axis positions.
  joy->pollAxis();

  /*
   * Iterate through the joystick buttons and check if any are pressed.
   */
  for( int counter = 0; counter < NUM_BUTTONS; counter++ ) {
    if( joy->isButtonPressed( counter ) == true ) {

#ifdef DEBUGGING_MODE
      Serial.print( "Button: " );
      Serial.print( counter );
      Serial.println( " pressed!" );
#endif

      // A button matching 'counter' has been pressed!
      // Perform some ACTION!
      
      // TODO!
      //  commandToSend = SOME_ACTION;
      Mirf.send( (byte*)  &data );
    }
  }

  delay( MAIN_LOOP_DELAY );
}


