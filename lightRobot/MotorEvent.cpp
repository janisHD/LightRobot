
#include "MotorEvent.h"

#define SPEED_TRANS_FAKTOR 2
#define SPEED_MAX 255

#define SPEED_TRANS_MOTOR_PERCENT_FAKTOR 0.1921
#define SPEED_TRANS_MOTOR_PERCENT_ADD 50

#define DIRECTION_TRANS_FAKTOR 1.41732



 MotorEvent::MotorEvent():
 TimeEvent(),
 m_speed(0),
 m_speed_external(0),
 m_direction(PI/4),
 m_speed_motor_left(0),
 m_speed_motor_right(0)
{
  
}

void MotorEvent::onTimeEvent()
{	
  m_motors.setSpeeds(m_speed_motor_right, m_speed_motor_left);
}

void MotorEvent::stopMotors()
{
  setDirection(0);
  setSpeed(0);
}

char MotorEvent::getSpeed()
{
  return m_speed_external;
}

unsigned char MotorEvent::getSpeedMotorLeft()
{
  return  (unsigned char)(SPEED_TRANS_MOTOR_PERCENT_FAKTOR*m_speed_motor_left + SPEED_TRANS_MOTOR_PERCENT_ADD);
}
unsigned char MotorEvent::getSpeedMotorRight()
{
  return (unsigned char)(SPEED_TRANS_MOTOR_PERCENT_FAKTOR*m_speed_motor_right + SPEED_TRANS_MOTOR_PERCENT_ADD);
}

void MotorEvent::setSpeed(char speed)
{
  m_speed_external = speed;
  speed = SPEED_TRANS_FAKTOR*speed;
  if(speed > SPEED_MAX)
    m_speed = SPEED_MAX;
  else if(speed < (-SPEED_MAX))
    m_speed = (-SPEED_MAX);
  else
    m_speed = speed;
    
    calcMotorSpeed();
}

void MotorEvent::alterSpeed(char value)
{
  setSpeed(m_speed_external + value);
}

void MotorEvent::calcMotorSpeed()
{
  int temp_motor_speed = sin(m_direction)*m_speed;
  
  if(temp_motor_speed > SPEED_MAX || temp_motor_speed < (-SPEED_MAX))
    temp_motor_speed = SPEED_MAX * ((temp_motor_speed > 0)-(temp_motor_speed < 0));//simple signum
  
  m_speed_motor_left = temp_motor_speed;
  
  temp_motor_speed = cos(m_direction)*m_speed;
  
  if(temp_motor_speed > SPEED_MAX || temp_motor_speed < (-SPEED_MAX))
    temp_motor_speed = SPEED_MAX * ((temp_motor_speed > 0)-(temp_motor_speed < 0));
    
  m_speed_motor_right = temp_motor_speed;
}
  

char MotorEvent::getDirection()
{
  return m_direction;
}
void MotorEvent::setDirection(char direction)
{
  m_direction = radians(DIRECTION_TRANS_FAKTOR * direction) + PI/4;
  calcMotorSpeed();
}

unsigned char MotorEvent::getInternalState()
{
  return m_speed;
}

void MotorEvent::setInternalState(unsigned char state, bool update)
{
  //nothing to do here!
}

void MotorEvent::executeAction()
{
	//nothing to do here!
}
