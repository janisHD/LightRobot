
#include "MotorEvent.h"

#define SPEED_TRANS_FAKTOR 2
#define SPEED_MAX 255

#define SPEED_TRANS_MOTOR_PERCENT_FAKTOR 0.1921
#define SPEED_TRANS_MOTOR_PERCENT_ADD 50

#define DIRECTION_TRANS_FAKTOR 1.41732

#define WHEEL_DISTANCE 100 //about 100mm
#define SPEED_FACTOR 900/255 //255 means full speed, its about 900mm/s
#define TURN_MULTIPLICATOR 5 //Factor with which the received turn rate is multiplied (to cover a greater range)
#define TURN_VALUE 127*5 // This value minus the received defines the turn radius 
#define TURN_MIN (5) //Radius smaller than this lets the wheel start to turn backwards



 MotorEvent::MotorEvent():
 TimeEvent(),
 m_speed(0),
 m_speed_external(0),
 m_direction(0),
 m_speed_motor_left(0),
 m_speed_motor_right(0),
 m_update_motors(false)
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

short MotorEvent::getSpeedMotorLeft()
{
  return  m_speed_motor_left;
}
short MotorEvent::getSpeedMotorRight()
{
  return m_speed_motor_right;
}

void MotorEvent::setSpeed(short speed)
{
  short temp_speed = 0;
  
  m_speed_external = speed;
  temp_speed = SPEED_TRANS_FAKTOR*speed;
  m_speed = restrictSpeed(temp_speed);
  calcMotorSpeed();
}

short MotorEvent::restrictSpeed(short speed)
{
  if(speed > SPEED_MAX)
    return SPEED_MAX;
  else if(speed < (-SPEED_MAX))
    return (-SPEED_MAX);
  else
    return speed;
}

void MotorEvent::alterSpeed(char value)
{
  if(m_update_motors)
  {
    m_update_motors = false;
    setSpeed(m_speed_external + value);
  }
}

void MotorEvent::calcMotorSpeed()
{
  short left_wheel = 0;
  short right_wheel = 0;
  short direction = m_direction;
  short radius = m_direction; //interpretet as an radius to turn
  short speed = m_speed;
  
  if(direction == 0)
  {//Move straight forward without turning
    left_wheel = speed;
    right_wheel = left_wheel;
  }
  else if(direction == TURN_VALUE)
  {//turn on spot
    left_wheel = speed;
    right_wheel = -speed;
  }
    else if(direction == -TURN_VALUE)
  {//turn on spot
    left_wheel = -speed;
    right_wheel = speed;
  }
  else
  {//if direction is negative (radius is then also negative) the left wheel will be slowed, else the right wheel
    left_wheel = speed + (WHEEL_DISTANCE*speed)/(2*radius);
    right_wheel = speed - (WHEEL_DISTANCE*speed)/(2*radius);
  }
  /*else if(direction < 0)
  {//Leftmotor is inner wheel, direction is negative
    left_wheel = speed + (WHEEL_DISTANCE*speed)/(2*radius);
    right_wheel = speed - (WHEEL_DISTANCE*speed)/(2*radius);
  }
  else if(direction > 0)
  {//rightmotor is inner wheel
    left_wheel = speed + (WHEEL_DISTANCE*speed)/(2*radius);
    right_wheel = speed - (WHEEL_DISTANCE*speed)/(2*radius);
  }*/
  
  //m_speed_motor_left = (-1)*restrictSpeed(left_wheel);
  //m_speed_motor_right = (-1)*restrictSpeed(right_wheel);
  m_speed_motor_left = restrictSpeed(left_wheel);
  m_speed_motor_right = restrictSpeed(right_wheel);
  m_update_motors = true;
  
  /*short temp_motor_speed = sin(m_direction)*m_speed;
  
  if(temp_motor_speed > SPEED_MAX || temp_motor_speed < (-SPEED_MAX))
    temp_motor_speed = SPEED_MAX * ((temp_motor_speed > 0)-(temp_motor_speed < 0));//simple signum
  
  m_speed_motor_left = temp_motor_speed;
  
  temp_motor_speed = cos(m_direction)*m_speed;
  
  if(temp_motor_speed > SPEED_MAX || temp_motor_speed < (-SPEED_MAX))
    temp_motor_speed = SPEED_MAX * ((temp_motor_speed > 0)-(temp_motor_speed < 0));
    
  m_speed_motor_right = temp_motor_speed;*/
}
  

short MotorEvent::getDirection()
{
  return m_direction;
}
void MotorEvent::setDirection(short direction)
{//comes as [-127, 127], goes as [-1260, 1260]
  if(direction >= -TURN_MIN && direction <= TURN_MIN)
  {//this means do not turn at all
    m_direction = 0;
  }
  else if (direction == -127 || direction == 127)
  {
    if(direction > 0)
     m_direction = TURN_VALUE;
    else
     m_direction = -TURN_VALUE;
  }
  else
  {
    if(direction >= 0)
     m_direction = TURN_VALUE - direction * TURN_MULTIPLICATOR - 10;
    else
     m_direction = (-TURN_VALUE) - (direction * TURN_MULTIPLICATOR + 10);
  }
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
