
#ifndef MOTOR_H_INC
#define MOTOR_H_INC

class motor {
public:
  motor( int m_e, int m_c1, int m_c2 );

  void moveForward();
  void moveReverse();

private:
  int _motorEnablePin;
  int _motorControlPin1;
  int _motorControlPin2;
};

#endif // MOTOR_H_INC
