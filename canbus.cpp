#include "canbus.h"




canbus::canbus(){
	
	can.begin();
	broadcast.id = 0x0;
	broadcast.buf[0] = 0x00;
	broadcast.len = sizeof(broadcast.buf);


		
	

}


canbus::~canbus()
{
}





void canbus::write(CAN_message_t msg){
	if (can.write(msg) == 0){
		//Fehlermeldung Bus nicht schreibbar
	}
}

int canbus::read(CAN_message_t msg){
	if (can.read(msg) == 0){
		//Fehlermeldung: No Frame available
		return 0;
	}

}
