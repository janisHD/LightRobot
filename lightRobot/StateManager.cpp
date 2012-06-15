
#include "StateManager.h"

 StateManager::StateManager():
 m_bt_event(NULL),
 m_lcd_event_0(NULL),
 m_lcd_event_1(NULL),
 m_button_event(NULL)
{
}

StateManager::StateManager(BlueToothEvent *bt_event, LCDEvent * lcd_event_0, LCDEvent * lcd_event_1, ButtonEvent *button_event):
m_bt_event(bt_event),
m_lcd_event_0(lcd_event_0),
m_lcd_event_1(lcd_event_1),
m_button_event(button_event)
{
}

void StateManager::manageState()
{
   switch (m_state)
   {
     case init:
     {
       m_lcd_event_0->setInternalState(LCDEvent::init);
       m_lcd_event_1->setInternalState(LCDEvent::init_options);
       
       if(m_button_event->isButtonBottomPressed())
         m_state = remoteControl;
       if(m_button_event->isButtonMiddlePressed())
         m_state = manualControl;
       
       break;
     }
     case remoteControl:
     {
       m_lcd_event_0->setInternalState(LCDEvent::remoteControl);
       break;
     }
     case manualControl:
     {
       m_lcd_event_0->setInternalState(LCDEvent::manualControl);
       break;
     }
     default:
     {
       break;
     }
   };
}




