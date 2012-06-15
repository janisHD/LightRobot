/*Main file for the LightRobot project on the arduino part*/

#include <TimedAction.h>
#include <Wire.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanLCD.h>
#include "ButtonEvent.h"
#include "LCDEvent.h"
#include "BlueToothEvent.h"
#include "StateManager.h"

#define SLOW_ACTION 150
#define MIDDLE_ACTION 25
#define FAST_ACTION 10
#define FASTER_ACTION 5

ButtonEvent button_event;
TimedAction button_action = TimedAction(MIDDLE_ACTION, buttonEvent);
LCDEvent lcd_event_0;
TimedAction lcd_action_0 = TimedAction(SLOW_ACTION, lcdEvent0);
LCDEvent lcd_event_1(1);
TimedAction lcd_action_1 = TimedAction(SLOW_ACTION, lcdEvent1);
BlueToothEvent bt_event;
TimedAction bt_action = TimedAction(FAST_ACTION, btEvent);

void buttonEvent(){
  button_event.onTimeEvent();
}

void lcdEvent0(){
  lcd_event_0.onTimeEvent();
}

void lcdEvent1(){
  lcd_event_1.onTimeEvent();
}

void btEvent(){
  bt_event.onTimeEvent();
}

StateManager state_manager(&bt_event, &lcd_event_0, &lcd_event_1, &button_event);

void setup()
{  
  lcd_event_0.setInternalState(LCDEvent::clear, true);
  lcd_event_0.onTimeEvent();
  lcd_event_1.setInternalState(LCDEvent::clear, true);
  lcd_event_1.onTimeEvent();
}

void loop()
{
  button_action.check();
  lcd_action_0.check();
  lcd_action_1.check();
  bt_action.check();
  
  state_manager.manageState();
  
  
}

