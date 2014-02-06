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

#include "globals.h"
#include "mitsumi_m42sp_4np.h"

// Mitsumi Stepper motor class constructor.
Mitsumi_M42SP_4NP::Mitsumi_M42SP_4NP( byte coil1, byte coil2, byte coil3, byte coil4 ) {
  _motorPin1 = coil1;
  _motorPin2 = coil2;
  _motorPin3 = coil3;
  _motorPin4 = coil4;

  pinMode( coil1, OUTPUT );
  pinMode( coil2, OUTPUT );
  pinMode( coil3, OUTPUT );
  pinMode( coil4, OUTPUT );
}

void Mitsumi_M42SP_4NP::phaseForward() {
  digitalWrite( _motorPin1, HIGH ); // 1
  digitalWrite( _motorPin2, LOW );
  digitalWrite( _motorPin3, LOW );
  digitalWrite( _motorPin4, HIGH ); // 2
  delay( STEPPER_DELAY_TIME );

  digitalWrite( _motorPin1, HIGH ); // 2
  digitalWrite( _motorPin2, LOW );
  digitalWrite( _motorPin3, HIGH ); // 1
  digitalWrite( _motorPin4, LOW );
  delay( STEPPER_DELAY_TIME );

  digitalWrite( _motorPin1, LOW );
  digitalWrite( _motorPin2, HIGH ); // 1
  digitalWrite( _motorPin3, HIGH ); // 2
  digitalWrite( _motorPin4, LOW );
  delay( STEPPER_DELAY_TIME );

  digitalWrite( _motorPin1, LOW );
  digitalWrite( _motorPin2, HIGH ); // 2
  digitalWrite( _motorPin3, LOW );
  digitalWrite( _motorPin4, HIGH ); // 1
  delay( STEPPER_DELAY_TIME );
}

void Mitsumi_M42SP_4NP::phaseReverse() {
  //
}
