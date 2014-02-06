#ifndef JOYSTICK_H_INC
#define JOYSTICK_H_INC

#include <Arduino.h>

#define uint8_t byte

class joystick {
public:
  joystick( byte x, byte y );

  byte getXPin();
  byte getYPin();

  long getXPos();
  long getYPos();

  void setXPos( long pos );
  void setYPos( long pos );

private:
  byte _xPin;
  byte _yPin;
  long _xPos;
  long _yPos;
};

#endif // JOYSTICK_H_INC
