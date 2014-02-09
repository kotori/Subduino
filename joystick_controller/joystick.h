/*
 * joystick.h
 */

#ifndef JOYSTICK_H_INC
#define JOYSTICK_H_INC

#include <Arduino.h>

#define NUM_BUTTONS 4
#define BUTTON_BOUNCE_DELAY 50
#define JOY_STICK_ADJUSTMENT_MOD 102300

#define uint8_t byte

struct joystick_button {
  int pin;
  int state;
  int prevState;
  long lastPressed;
};

class joystick {
public:
  joystick( byte xAxisPin, byte yAxisPin, int numButtons, ... );

  byte getXPin();
  byte getYPin();

  void getPos( long &xPos, long &yPos );

  long getXPos();
  long getYPos();

  long getXPrevPos();
  long getYPrevPos();

  void setXPos( long pos );
  void setYPos( long pos );

  void setXPrevPos( long pos );
  void setYPrevPos( long pos );

  int getButton( int id );
  void setButton( int id, int newPin );

  boolean isButtonPressed( int id );

  void pollAxis();

private:
  byte _xPin;
  byte _yPin;

  long _xPos;
  long _xPrevPos;
  long _yPos;
  long _yPrevPos;

  joystick_button _button[NUM_BUTTONS];
};

#endif // JOYSTICK_H_INC

