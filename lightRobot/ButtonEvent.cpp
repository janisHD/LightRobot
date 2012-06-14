
#include "ButtonEvent.h"

 ButtonEvent::ButtonEvent():
m_buttons_state(0),
m_button_pressed(false),
m_button_top(false),
m_button_middle(false),
m_button_bottom(false)
{
}

void ButtonEvent::onTimeEvent()
{
	m_buttons_state = buttons.getSingleDebouncedPress(TOP_BUTTON | MIDDLE_BUTTON | BOTTOM_BUTTON);
	
	if(m_buttons_state != 0)
	  m_button_pressed = true;
        else
          m_button_pressed = false;      
	

	if((m_buttons_state & TOP_BUTTON) == TOP_BUTTON)
	  m_button_top = true;
        else
          m_button_top = false;
          
	if((m_buttons_state & MIDDLE_BUTTON) == MIDDLE_BUTTON)
	  m_button_middle = true;
        else
          m_button_middle = false;
          
       	if((m_buttons_state & BOTTOM_BUTTON) == BOTTOM_BUTTON)
	  m_button_bottom = true;
        else
          m_button_bottom = false;        
}

int ButtonEvent::getInternalState()
{
  if(m_button_pressed)
  {
    m_button_pressed = false;
    return m_buttons_state;
  }
  return false;
}

bool ButtonEvent::isButtonTopPressed()
{
  if(m_button_top)
  {
    m_button_top = false;
    return true;
  }
  return false;
}

bool ButtonEvent::isButtonMiddlePressed()
{
  if(m_button_middle)
  {
    m_button_middle = false;
    return true;
  }
  return false;
}

bool ButtonEvent::isButtonBottomPressed()
{
  if(m_button_bottom)
  {
    m_button_bottom = false;
    return true;
  }
  return false;
}

void ButtonEvent::setInternalState(int state)
{
	//nothing to do here!
}

void ButtonEvent::executeAction()
{
	//nothing to do here!
}
