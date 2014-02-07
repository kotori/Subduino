#include <Arduino.h>
#include <Wire.h>

#include "globals.h"
#include "motor.h"

const int NUM_MOTORS = 2;
const int MAIN_LOOP_DELAY = 100;

const int MOTOR_1_ENABLE_PIN = 6;
const int MOTOR_1_CONTROL1_PIN = 7;
const int MOTOR_1_CONTROL2_PIN = 8;

const int MOTOR_2_ENABLE_PIN = 3;
const int MOTOR_2_CONTROL1_PIN = 2;
const int MOTOR_2_CONTROL2_PIN = 4;

motor *motorPool[NUM_MOTORS];

void setup() {
  motorPool[0] = new motor(
    MOTOR_1_ENABLE_PIN, MOTOR_1_CONTROL1_PIN, MOTOR_1_CONTROL2_PIN );
  motorPool[1] = new motor(
    MOTOR_2_ENABLE_PIN, MOTOR_2_CONTROL1_PIN, MOTOR_2_CONTROL2_PIN );

  // Start the I2C interface.
  Wire.begin( I2C_THRUST_CONTROLLER );
}

void loop() {
  //
  delay( MAIN_LOOP_DELAY );
}
