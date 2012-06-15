
#include "BlueToothEvent.h"

 BlueToothEvent::BlueToothEvent():
 TimeEvent()
{
  //init data array
  m_data[mode] = 0;
  m_data[velocity] = 0;
  m_data[direction] = 0;
  m_data[color] = 0;
}

void BlueToothEvent::onTimeEvent()
{	
	//Code to receive a single data word and store it in m_data field
        //Word consists of 5 chars:
        //[0] -> direction to drive [0-254]
        //[1] -> velocity to drive [0-254]
        //[2] -> desired color for the Light [0-254]
        //[3] -> internal mode (see responsible class)[0-254]
        //[5] -> termination value [255] is it necessary?
        
        //ONLY STUB CODE:
        m_data[mode] = 0;
        m_data[velocity] = 0;
        m_data[direction] = 0;
        m_data[color] = 0;
}

unsigned char BlueToothEvent::getData(unsigned char field)
{
  if(field <= mode)
    return m_data[field];
  else
    return 0;
}

unsigned char BlueToothEvent::getInternalState()
{
  return m_data[mode];
}

void BlueToothEvent::setInternalState(unsigned char state, bool update)
{
  //nothing to do here!
}

void BlueToothEvent::executeAction()
{
	//nothing to do here!
}
