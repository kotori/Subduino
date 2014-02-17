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
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

#include "globals.h"
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
const int CE_PIN = 9;
const int CSN_PIN = 10;

const int SERIAL_BAUDRATE = 9600;
const int POLLING_INTERVAL = 60; // Control's the rate at which polling takes place.
long previousMillis = 0;        // will store last time joystick was polled.

joystick *joy;
/*
 * Stores the current joystick button presses.
 * [0] = button #1
 * [1] = button #2
 * [2] = button #3
 * [3] = button #4
 */
boolean buttons[4];

// 0 - x axis
// 1 - y axis
// 2 - button1
// 3 - button2
// 4 - button3
// 5 - button4
int dataPacket[WIRELESS_PACKET_SIZE];
int prevPacket[WIRELESS_PACKET_SIZE];

boolean sendUpdate;

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

  for( int i=0; i<NUM_BUTTONS; i++ ) {
    buttons[i] = false;
  }

  sendUpdate = false;

  /*
   * Set the SPI Driver.
   */
  Mirf.spi = &MirfHardwareSpi;
  
  /*
   * Setup pins / SPI.
   */
  Mirf.init();
  
  /*
   * Configure reciving address.
   */
  Mirf.setRADDR( (byte *)"recv1" );
  
  /*
   * Set the payload length to sizeof(unsigned long) the
   * return type of millis().
   *
   * NB: payload on client and server must be the same.
   */
  Mirf.payload = 6;
  
  
  /*
   * Write channel and payload config then power up reciver.
   */
  Mirf.channel = 10;

  Mirf.config();

  #ifdef DEBUGGING_MODE
    // Initialize serial interface for debugging.
    Serial.begin( SERIAL_BAUDRATE );

    // Read and print RF_SETUP
    byte rf_setup = 0;
    Mirf.readRegister( RF_SETUP, &rf_setup, sizeof(rf_setup) );
    Serial.print( "rf_setup = " );
    Serial.println( rf_setup, BIN );

    Serial.println("Receiver Powered!");
  #endif
}

void sendWirelessUpdate() {

  Mirf.setTADDR((byte *)"tran1");

  dataPacket[Mirf.payload];

  Mirf.send( (byte *) &dataPacket );
  
  while( Mirf.isSending() ) {
    // Block while we are sending the command.
  }
  #ifdef DEBUGGING_MODE
    Serial.print( "Sent update @ " );
    Serial.println( millis() );
  #endif
}

void doLogic() {

  for( int count = 0; count < WIRELESS_PACKET_SIZE; count++ ) {
    // Setup the previous packet for comparison.
    prevPacket[count] = dataPacket[count];
  }

  // Build the new packet.
  dataPacket[0] = joy->getXPos();
  dataPacket[1] = joy->getYPos();
  dataPacket[2] = buttons[0];
  dataPacket[3] = buttons[1];
  dataPacket[4] = buttons[2];
  dataPacket[5] = buttons[3];

  // We only need to flag for a wireless update if something has changed.
  for( int count = 0; count < WIRELESS_PACKET_SIZE; count++ ) {
    if( dataPacket[count] != prevPacket[count] ) {
      sendUpdate = true;
    }
  }
  
}

void loop() {
  sendUpdate = false;
  unsigned long currentMillis = millis();
 
  if( currentMillis - previousMillis > POLLING_INTERVAL ) {
    // Store the current x and y axis positions.
    joy->pollAxis();

    /*
     * Iterate through the joystick buttons and check if any are pressed.
     */
    for( int counter = 0; counter < NUM_BUTTONS; counter++ ) {
      buttons[counter] = false;
      if( joy->isButtonPressed( counter ) == true ) {
        // Set the flag to tell the logic engine this is pressed.
        buttons[counter] = true;

        #ifdef DEBUGGING_MODE
          Serial.print( "Button: " );
          Serial.print( counter );
          Serial.println( " pressed!" );
        #endif
      }
    }
  }

  doLogic();

  if( sendUpdate == true ) {
    sendWirelessUpdate();
  }

}


