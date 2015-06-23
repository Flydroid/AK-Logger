#include "canbus.h"
#include "config.h"

canbus::canbus(){

	can.begin();
	broadcast.id = 0x0;
	broadcast.buf[0] = 0x00;
	broadcast.len = sizeof(broadcast.buf);
}

void canbus::write(CAN_message_t msg){
	if (can.write(msg) == 0){
#ifdef DEBUGING
		Serial.println("Massage not send");
#endif
	}
}

bool canbus::read(CAN_message_t msg){
	if (can.available())
	{


		if (can.read(msg) == 0){

			return false;
		}
		return true;
	}
	else
	{
		return false;
	}
}
