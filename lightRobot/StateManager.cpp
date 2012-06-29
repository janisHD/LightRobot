
#include "StateManager.h"

 StateManager::StateManager():
 m_state(init),
 m_old_state(remoteControl),
 m_update_lcd(true),
 m_motor_event(NULL),
 m_bt_event(NULL),
 m_lcd_event_0(NULL),
 m_lcd_event_1(NULL),
 m_button_event(NULL)
{
}

StateManager::StateManager(MotorEvent *motor_event, BlueToothEvent *bt_event, LCDEvent * lcd_event_0, LCDEvent * lcd_event_1, ButtonEvent *button_event):
 m_state(init),
 m_old_state(remoteControl),
 m_update_lcd(true),
 m_motor_event(motor_event),
m_bt_event(bt_event),
m_lcd_event_0(lcd_event_0),
m_lcd_event_1(lcd_event_1),
m_button_event(button_event)
{
}

void StateManager::manageState()
{
  if(m_state != m_old_state)
     {//on state change
       m_update_lcd = true;//On state change -> update lcd
       m_motor_event->stopMotors();
       m_old_state = m_state;
     }
   switch (m_state)
   {
     case init:
     {
       if(m_update_lcd)
       {
         m_lcd_event_0->setInternalState(LCDEvent::init);
         m_lcd_event_1->setInternalState(LCDEvent::init_options);
         m_update_lcd = false;
       }
       
       if(m_button_event->isButtonAClicked())
         m_state = remoteControl;
       if(m_button_event->isButtonBClicked())
         m_state = manualControl;
       
       break;
     }
     case remoteControl:
     {
       if(m_update_lcd)
       {
         m_lcd_event_0->setInternalState(LCDEvent::remoteControl);
         m_lcd_event_1->setInternalState(LCDEvent::init_options);
         m_update_lcd = false;
       }
       if(m_button_event->isButtonBClicked())
         m_state = manualControl;
       break;
     }
     case manualControl:
     {
      if(m_update_lcd)
       {
         m_lcd_event_0->setInternalState(LCDEvent::manualControl);
         m_lcd_event_1->setInternalState(LCDEvent::freePaint);
         m_lcd_event_1->setFreePaintString("ML  MR  ");
         m_update_lcd = false;
       }
       if(m_button_event->isButtonBClicked())
       {//middle Button increases speed
         m_motor_event->alterSpeed(20);
         m_lcd_event_1->setFreePaintString(String("ML") + String(m_motor_event->getSpeedMotorLeft() + String("MR") + String(m_motor_event->getSpeedMotorRight())));
       }
       
       if(m_button_event->isButtonAClicked())
         m_state = remoteControl;
       break;
     }
     default:
     {
       break;
     }
   };
}



