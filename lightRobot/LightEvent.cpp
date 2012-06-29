
#include "LightEvent.h"

//TODO: change to pin 4 and 6 when used together with bt.
#define SDA_I2C 1
#define SCL_I2C 0
#define BLINK_DURATION 10
#define BLINK_ADRESS 0x09
#define STOP_SCRIPTS 'n'

 LightEvent::LightEvent():
 TimeEvent(),
 m_wire(SDA_I2C, SCL_I2C),
 m_state(init),
 m_light_state(false),
 m_brightness(0),
 m_red(0),
 m_green(0xff),
 m_blue(0),
 m_blink_counter(0)
{
  m_update = true;
}

void LightEvent::onTimeEvent()
{
  if(m_update)
  {//only if new data is available
    switch(m_state)
    {
      case init:
      {
        m_update = false;
        initLight();
        m_state = shine;
        break;
      }
      case shine:
      {
        setColor();
        m_update = false;//NOT before the switch
       break; 
      }
      case blink:
      {//Update is never cleared here, because it counts the calls and works as timer
      if(m_blink_counter == BLINK_DURATION)
      {//only if time is up NEVER clear update!
        m_blink_counter = 0;
        m_light_state = ~m_light_state;
        setColor();
        turnOn();
      } 
        break;
      }
      case random:
      {
        //nothing to do here
        break;
      }
      default:
      {
        //what to do?
      }
    }
  };
        
}

unsigned char LightEvent::getInternalState()
{
  return m_state;
}


void LightEvent::setInternalState(unsigned char state, bool update)
{
  m_state = (State)state;
  m_update = true;
}

void LightEvent::executeAction()
{
	//nothing to do here!
}

void LightEvent::initLight()
{
  m_wire.beginTransmission(BLINK_ADRESS);
  m_wire.send(STOP_SCRIPTS);
  m_wire.endTransmission();
}

void LightEvent::turnOn()
{
}

void LightEvent::setColor()
{
  m_wire.beginTransmission(BLINK_ADRESS);
  m_wire.send('n'); // c is fade to color
  m_wire.send(m_red); // value for red channel
  m_wire.send(m_green); // value for green channel
  m_wire.send(m_blue); // value for blue channel*/
  m_wire.endTransmission();
}
