/*! \file BlueToothEvent.h checks periodically if new data over BT has been received.*/

#include <Arduino.h>
#include <OrangutanLCD.h>
#include "TimeEvent.h"

#ifndef BLUETOOTH_EVENT_H
#define BLUETOOTH_EVENT_H

#define DATA_WORD_LENGTH 4

/*! \class BlueToothEvent
retrieves and stores the received BT data.
*/
class BlueToothEvent : public TimeEvent
{
  public:
  
  BlueToothEvent();
  ~BlueToothEvent(){};
  
  /*! Callback which is executed periodically*/
  virtual void onTimeEvent();
  /*! Returns an internal state.*/
  virtual unsigned char getInternalState();
  /*! Sets an internal state.*/
  virtual void setInternalState(unsigned char state, bool update=false);
  /*! Executes a more complex (and time consuming) action.*/
  virtual void executeAction();
  
  unsigned char getData(unsigned char field);
  
  private:
  
  enum Data{
    direction=0,//direction to drive
    velocity,//desired velocity
    color,//desired color of the LEDs
    mode,//the different modes: remote, random, blink
  };
  
  unsigned char m_data[DATA_WORD_LENGTH];
  
};

#endif
