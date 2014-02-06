#ifndef JOYSTICK_H_INC
#define JOYSTICK_H_INC

#include <Arduino.h>

const int NUM_BUTTONS =	4;
#define uint8_t byte

class joystick {
public:
  joystick( byte x, byte y, int numButtons, ... );

  byte getXPin();
  byte getYPin();

  long getXPos();
  long getYPos();

  void setXPos( long pos );
  void setYPos( long pos );

  int getButton( int id );
  void setButton( int id, int pin );

  boolean isPressed( int id );

private:
  byte _xPin;
  byte _yPin;

  long _xPos;
  long _yPos;

  int _button[NUM_BUTTONS];
};

#endif // JOYSTICK_H_INC
