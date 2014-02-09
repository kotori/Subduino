
#include <Arduino.h>
#include <stdarg.h>

#include "joystick.h"

joystick::joystick( byte xAxisPin, byte yAxisPin, int numButtons, ... ) {
  _xPin = xAxisPin;
  _yPin = yAxisPin;

  _xPos = 0;
  _xPrevPos = 0;
  _yPos = 0;
  _yPrevPos = 0;

  // Now setup our buttons from the variable list.
  va_list fncArgs;
  va_start( fncArgs, numButtons );

  // For every increment upto numButtons set a pin value.
  for( int argCounter = 0; argCounter < numButtons; argCounter++ ) {
    _button[argCounter].pin = va_arg( fncArgs, int );
    _button[argCounter].state = LOW;
    _button[argCounter].prevState = LOW;
    _button[argCounter].lastPressed = 0;
  }
  va_end( fncArgs );
}

void joystick::getPos( long &xPos, long &yPos ) {
  xPos = _xPos;
  yPos = _yPos;
}

byte joystick::getXPin() {
  return _xPin;
}

byte joystick::getYPin() {
  return _yPin;
}

long joystick::getXPos() {
  return _xPos;
}

long joystick::getYPos() {
  return _yPos;
}

long joystick::getXPrevPos() {
  return _xPrevPos;
}

long joystick::getYPrevPos() {
  return _yPrevPos;
}

void joystick::setXPos( long pos ) {
  _xPos = pos;
}

void joystick::setYPos( long pos ) {
  _yPos = pos;
}

void joystick::setXPrevPos( long pos ) {
  _xPrevPos = pos;
}

void joystick::setYPrevPos( long pos ) {
  _yPrevPos = pos;
}

int joystick::getButton( int id ) {
  return _button[id].pin;
}

void joystick::setButton( int id, int newPin ) {
  _button[id].pin = newPin;
}

/*
 *  Returns true or false depending on the state of the button.
 *   TODO!
 *    Should have some sort of a debounce check built in.
 */
boolean joystick::isButtonPressed( int id ) {
  // Set the initial value of the reading as bad.
  boolean goodReading = false;

  // Get the state of the passed button.
  //_button[id].state = digitalRead( _button[id].pin );
  int reading = digitalRead( _button[id].pin );

  if( reading != _button[id].prevState ) {
    // Reset the button's debounce timer.
    _button[id].lastPressed = millis();
  }

  /*
   * Only proceed if the time between the last button press is greater
   *  then the bounce delay global. This should help ensure that button
   *  mashing will not cause odd behavior.
   */
  if( ( millis() - _button[id].lastPressed ) > BUTTON_BOUNCE_DELAY ) {
    if( reading != _button[id].state ) {
      _button[id].state = reading;
      // ONLY toggle the button when a LOW signal is received.
      if( _button[id].state == LOW ) {
        goodReading = true;
      }
    }
  }
  _button[id].prevState = reading;
  return goodReading;
}

