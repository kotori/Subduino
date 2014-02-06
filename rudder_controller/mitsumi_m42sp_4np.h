/*
 * Mitsumi M42SP-4NP Stepper Motor Control Class
 *  Rated Voltage: 25vdc
 *  Rated Current/Phase: 259mA
 *  No. Phases: 4
 *  DC Coil Resistance: 7.5degree / phase
 *  Excitation Method: 2-2 phase (unipolar)
 *
 *  Reference:
 *   http://josafatisai.blogspot.co.uk/2013/04/wiring-mitsumi-stepper-m42sp-4np-with.html
 *   http://www.danielstolfi.com/recursos/M42SP-4.pdf
 */

#ifndef MITSUMI_M42SP_4NP_H_INC
#define MITSUMI_M42SP_4NP_H_INC

#define byte uint8_t

#include <Arduino.h>

class Mitsumi_M42SP_4NP {
public:
  Mitsumi_M42SP_4NP( byte coil1, byte coil2, byte coil3, byte coil4 );

  void phaseForward();
  void phaseReverse();

  byte _motorPin1; // Coil 1
  byte _motorPin2; // Coil 2
  byte _motorPin3; // Coil 3
  byte _motorPin4; // Coil 4
};

#endif // MITSUMI_M42SP_4NP_H_INC
