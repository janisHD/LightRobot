
#include "LightEvent.h"

//TODO: change to pin PD2 (4 on the LCD Port) and PD4 (6 ont the LCD Port) when used together with bt.
#define BT_AVAILABLE 1


#if BT_AVAILABLE
  #define SDA_I2C 2
  #define SCL_I2C 4
#else
  #define SDA_I2C 1
  #define SCL_I2C 0
#endif

#define BLINK_DURATION 10
#define BLINK_ADRESS 0x09
#define STOP_SCRIPTS 'o'
#define SET_COLOR 'n'

 LightEvent::LightEvent():
 TimeEvent(),
 #if SEND
  m_wire(new SoftI2CMaster(SDA_I2C, SCL_I2C)),
#endif
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

LightEvent::LightEvent(SoftI2CMaster *wire):
TimeEvent(),
 #if SEND
  m_wire(wire),
#endif
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
 #if SEND
 //   delay(1000);
  m_wire->beginTransmission(BLINK_ADRESS);
  m_wire->send(STOP_SCRIPTS);
  m_wire->endTransmission();
  delay(100);
  m_wire->beginTransmission(BLINK_ADRESS);
  m_wire->send(SET_COLOR);
  m_wire->send(0x01);
  m_wire->send(0x01);
  m_wire->send(0xff);
  m_wire->endTransmission();
 // delay(1000);
 /* m_wire->beginTransmission(BLINK_ADRESS);
  m_wire->send('n');
  m_wire->send(0x01);
  m_wire->send(0x01);
  m_wire->send(0xff);
  m_wire->endTransmission();*/
 #endif
}

void LightEvent::setRed(byte value)
{
  m_red = value;
  m_update = true;
}

void LightEvent::setGreen(byte value)
{
  m_green = value;
  m_update = true;
}

void LightEvent::setBlue(byte value)
{
  m_blue = value;
  m_update = true;
}

void LightEvent::turnOn()
{
}

void LightEvent::setColor()
{
  #if SEND
  m_wire->beginTransmission(BLINK_ADRESS);
  m_wire->send(SET_COLOR); // c is fade to color
  m_wire->send(m_red); // value for red channel
  m_wire->send(m_green); // value for green channel
  m_wire->send(m_blue); // value for blue channel*/
  m_wire->endTransmission();
  #endif
}
