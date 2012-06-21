/*! \file MotorEvent.h sets periodically new velocities for the motors.*/

#include <Arduino.h>
#include <OrangutanMotors.h>

#include "TimeEvent.h"

#ifndef MOTOR_EVENT_H
#define MOTOR_EVENT_H

/*! \class MotorEvent
controls the motors, uses the 3pi api.
*/
class MotorEvent : public TimeEvent
{
  public:
  
  MotorEvent();
  ~MotorEvent(){};
  
  /*! Callback which is executed periodically*/
  virtual void onTimeEvent();
  /*! Returns an internal state.*/
  virtual unsigned char getInternalState();
  /*! Sets an internal state.*/
  virtual void setInternalState(unsigned char state, bool update=false);
  /*! Executes a more complex (and time consuming) action.*/
  virtual void executeAction();
  
  
  void stopMotors();
  
  /*! Set the speed with a value range from [-127, 127]. This will be converted to a range from [-255, 255]*/
  void setSpeed(char speed);
  
  /*! Adds the value (can be negative) to the current speed value*/
  void alterSpeed(char value);
  
  void setDirection(char direction);
  
  char getSpeed();
  
  /*In a Range between [0,99] 0 -> max backward...*/
  unsigned char getSpeedMotorLeft();
  
  unsigned char getSpeedMotorRight();
  
  char getDirection();
  
  private:
  
  void calcMotorSpeed();
  
  private:
  
  OrangutanMotors m_motors;
  
  /*! The speed of the robot [-255, 255]
  */
  int m_speed;
  
  /*! The corresponding external value [-127, 127]
  */
  char m_speed_external;
  /*! The driving direction (or turn rate) in radians [-PI, +PI]
  */
  float m_direction;
  
  /*! The speed for the left motor [-255, 255]*/
  int m_speed_motor_left;
  /*! The speed for the right motor [-255, 255]*/
  int m_speed_motor_right;
};

#endif
