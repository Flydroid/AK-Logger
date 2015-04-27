#include "canbus.h"




canbus::canbus(){
	
	can.begin();
#ifdef MASTER
	broadcast.id = 0x0;
	broadcast.len = 0x1;
	broadcast.buf[0]=0x00
#endif
		
	

}


canbus::~canbus()
{
}


void canbus::write(CAN_message_t msg){
	if (can.write(msg) == 0){
		//Fehlermeldung Bus nicht schreibbar
	}
}

void canbus::read(CAN_message_t msg){
	if (can.read(msg) == 0){
		//Fehlermeldung: No Frame available
	}
}
