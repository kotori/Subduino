#include <Arduino.h>

#include "motor.h"

motor::motor( int m_e, int m_c1, int m_c2 ) {
  _motorEnablePin = m_e;
  _motorControlPin1 = m_c1;
  _motorControlPin2 = m_c2;

  pinMode( _motorEnablePin, OUTPUT );
  pinMode( _motorControlPin1, OUTPUT );
  pinMode( _motorControlPin2, OUTPUT );
}

void motor::moveForward() {
  digitalWrite( _motorEnablePin, HIGH );
  digitalWrite( _motorControlPin1, HIGH );
  digitalWrite( _motorControlPin2, LOW );
}

void motor::moveReverse() {
  digitalWrite( _motorEnablePin, HIGH );
  digitalWrite( _motorControlPin1, LOW );
  digitalWrite( _motorControlPin2, HIGH );
}
