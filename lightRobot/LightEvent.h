/*! \file LightEvent.h sets the light and color mode periodically*/

#include <Arduino.h>
#include "TimeEvent.h"
#include "SoftI2CMaster.h"

#ifndef LIGHT_EVENT_H
#define LIGHT_EVENT_H

#define SEND 1

/*! \class LightEvent
Sets the Light (Color, Brightnes, etc..) periodically.

*/
class LightEvent : public TimeEvent
{
  public:
  
  LightEvent();
  LightEvent(SoftI2CMaster * wire);
  ~LightEvent(){};
  
  /*! Callback which is executed periodically*/
  virtual void onTimeEvent();
  /*! Returns an internal state.*/
  virtual unsigned char getInternalState();
  /*! Sets an internal state.*/
  virtual void setInternalState(unsigned char state, bool update=false);
  /*! Executes a more complex (and time consuming) action.*/
  virtual void executeAction();
  
  void setBrightness(byte value);
  void setRed(byte value);
  void setGreen(byte value);
  void setBlue(byte value);
  void turnOn(bool value);
  
  enum State {
    init,
    shine,
    blink,
    random
  };
  
  private:
  
  /*! Sets the color accordin to the internal value of red, green and blue
  */
  void  setColor();
  
  /*! Maps the value from 0-3 to a value between 0-255
  */
  byte mapLightValue(byte value);
  
  /*! Turn the LED on or of*/
  
  void turnOn();
  
  public:
  /*! Initialises the LEDs (stops the standard script, etc.)*/
  void initLight();
  
  private:
  
  /*! Sends the data over I2C.
  */
  #if SEND
  SoftI2CMaster *m_wire;
  #endif
  
  /*! Determines if the LED should blink, shine, or change their color randomly
  */
  int m_state;
  
  /*! basically on or of
  */
  bool m_light_state;
  byte m_brightness;
  byte m_red;
  byte m_green;
  byte m_blue;
  
  int m_blink_counter;
};

#endif
