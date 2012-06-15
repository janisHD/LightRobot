
#include "BlueToothEvent.h"

 BlueToothEvent::BlueToothEvent():
 TimeEvent()
{
  m_data = {0,0,0,0};
}

void BlueToothEvent::onTimeEvent()
{	
	//Code to receive a single data word and store it in m_data field
        //Word consists of 5 chars:
        //[0] -> direction to drive [0-254]
        //[1] -> velocity to drive [0-254]
        //[2] -> desired color for the Light [0-254]
        //[3] -> internal mode (see responsible class)[0-254]
        //[5] -> termination value [255]
        
        //ONLY STUB CODE:
        m_data = {10,100, 50, 1};
}

void BlueToothEvent::saveReceivedData()
{
  m_internal_mode = m_data[mode];
  m_direction = m_data[direction];
  m_velocity = m_data[velocity];
  m_light = m_data[light];
}


int BlueToothEvent::getInternalState()
{
  return m_internal_mode;
}

int BlueToothEvent::getDirection()
{
  return m_direction;
}

int BlueToothEvent::getVelocity()
{
  return m_velocity;
}

int BlueToothEvent::getColor()
{
  return m_color;
}

void BlueToothEvent::setInternalState(int state, bool update)
{
  //nothing to do here!
}

void BlueToothEvent::executeAction()
{
	//nothing to do here!
}
