/*! \file StateManager.h Implementation of the global statemanager.*/

#include "BlueToothEvent.h"
#include "LCDEvent.h"
#include "ButtonEvent.h"

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

/*! \class StateManager
Implements a statemanager for the LightRobot. All information will be centralized and processed here.
*/
class StateManager
{
  public:
  
  StateManager();
  StateManager(BlueToothEvent *bt_event,  LCDEvent * lcd_event_0, LCDEvent * lcd_event_1, ButtonEvent *button_event);
  ~StateManager(){}
  
  void manageState();
  
  private:
  
  enum State{
    init=0,
    remoteControl,
    manualControl
  };
  
  private:
  
  State m_state;
  
  BlueToothEvent *m_bt_event;
  LCDEvent *m_lcd_event_0;
  LCDEvent *m_lcd_event_1;
  ButtonEvent *m_button_event;
};

#endif
