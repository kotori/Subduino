
#include <Arduino.h>
#include "joystick.h"

joystick::joystick( byte x, byte y ) {
  _xPin = x;
  _yPin = y;
  _xPos = 0;
  _yPos = 0;
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

