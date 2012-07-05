
#include "BlueToothEvent.h"

 BlueToothEvent::BlueToothEvent():
 TimeEvent()
{
  //init data array
  
  m_data[velocity] = 0;
  m_data[direction] = 0;
  m_data[color] = 0;
  m_data[mode] = 0;
  
  processData(m_data);
  
  //Serial connection
  Serial.begin(9600);
}

void BlueToothEvent::onTimeEvent()
{	
	//Code to receive a single data word and store it in m_data field
        //Word consists of 5 chars:
        
        //[0] -> direction to drive [0-254]
        //[1] -> velocity to drive [0-254]
        //[2] -> desired color for the Light [0-254]
        //[3] -> internal mode (see responsible class)[0-254]
        //[5] -> termination value [255] is it necessary?
        
        if(Serial.available() >= DATA_WORD_LENGTH)
        {//minimum number of bytes must be available in the buffer
          while(Serial.available() > DATA_WORD_LENGTH)
            Serial.read();//clear buffer to last 4 bits
          
          m_data[velocity] = (unsigned char)Serial.read();
          m_data[direction] = (unsigned char)Serial.read();
          m_data[color] = (unsigned char)Serial.read();
          m_data[mode] = (unsigned char)Serial.read();
          
          processData(m_data);
          
        }
        
        
}

void BlueToothEvent::processData(unsigned char* data)
{
  m_data_packet.speed = data[velocity];
  m_data_packet.direction = data[direction];
  m_data_packet.color[0] = data[color] & B00000011;
  m_data_packet.color[1] = (data[color] & B00001100)>>2;
  m_data_packet.color[2] = (data[color] & B00110000)>>4;
  m_data_packet.color[3] = (data[color] & B11000000)>>6;
  m_data_packet.mode[0] = data[mode] & B00001111;
  m_data_packet.mode[1] = (data[mode] & B11110000)>>4;
}


BlueToothEvent::DataPacket BlueToothEvent::getDataPacket()
{
  return m_data_packet;
}

//unsigned char BlueToothEvent::getData(unsigned char field)
//{
//  if(field <= mode)
//    return m_data[field];
//  else
//    return 0;
//}

unsigned char BlueToothEvent::getInternalState()
{
  return m_data[mode];
}

void BlueToothEvent::setInternalState(unsigned char state, bool update)
{
  //nothing to do here!
}

void BlueToothEvent::executeAction()
{
	//nothing to do here!
}
