#ifndef JOYSTICK_H_INC
#define JOYSTICK_H_INC

#include <Arduino.h>

#define NUM_BUTTONS 4
#define BUTTON_BOUNCE_DELAY 50

#define uint8_t byte

struct joystick_button {
  long lastPress;
  int pin;
  int state;
};

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
  void setButton( int id, int newPin );

  boolean isPressed( int id );

private:
  byte _xPin;
  byte _yPin;

  long _xPos;
  long _yPos;

  joystick_button _button[NUM_BUTTONS];
};

#endif // JOYSTICK_H_INC

