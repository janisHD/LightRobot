/*Main file for the LightRobot project on the arduino part*/

#include <TimedAction.h>
#include <Wire.h>
#include <OrangutanPushbuttons.h>
#include <OrangutanLCD.h>
#include "ButtonEvent.h"

#define SLOW_ACTION 100
#define MIDDLE_ACTION 25
#define FAST_ACTION 10
#define FASTER_ACTION 5

ButtonEvent button_event;
TimedAction button_action = TimedAction(MIDDLE_ACTION, buttonEvent);

OrangutanLCD lcd_display;
bool test = false;

void buttonEvent(){
  button_event.onTimeEvent();
}

void setup()
{
  
  lcd_display.clear();
}

void loop()
{
  button_action.check();
  
  lcd_display.print("no");
  lcd_display.gotoXY(0,1);
  lcd_display.print(button_event.getInternalState());
  lcd_display.print(TOP_BUTTON);
  lcd_display.gotoXY(0,0);
if(button_event.isButtonTopPressed())
{
    lcd_display.print("top");
    delay(1000);
    lcd_display.clear();
}
if(button_event.isButtonMiddlePressed())
{
    lcd_display.print("middle");
    delay(1000);
    lcd_display.clear();
}
if(button_event.isButtonBottomPressed())
{
    lcd_display.print("bottom");
    delay(1000);
    lcd_display.clear();
}

    
  lcd_display.gotoXY(0,0);
    
  //delay(1000);
}

