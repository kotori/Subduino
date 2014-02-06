
#include <Arduino.h>
#include "joystick.h"

joystick::joystick( byte x, byte y, int numButtons, ... ) {
  _xPin = x;
  _yPin = y;
  _xPos = -1;
  _yPos = -1;

  // Now setup our buttons from the variable list.
  va_list fncArgs;
  va_start( fncArgs, numButtons );
  for( int argCounter = 0; argCounter < numButtons; argCounter++ ) {
    _button[argCounter].pin = va_arg( fncArgs, int );
  }
  va_end( fncArgs );

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

void joystick::setXPos( long pos ) {
  _xPos = pos;
}

void joystick::setYPos( long pos ) {
  _yPos = pos;
}

int joystick::getButton( int id ) {
  return _button[id].pin;
}

void joystick::setButton( int id, int newPin ) {
  _button[id].pin = newPin;
}

boolean joystick::isButtonPressed( int id ) {
  // Get the state of the passed button.
  _button[id].state = digitalRead( _button[id].pin );

  // The Joystick buttons are floating HIGH, so a LOW voltage is actually a press.
  if( _button[id].state == LOW ) {
    return true;
  }
  else {
    return false;
  }
}

