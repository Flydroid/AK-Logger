


#ifndef CANBUS_H
#define CANBUS_H

/*
Klasse für die CAN-BUS Kommunikation
Hier wird die CAN-BUS Funktionalität und die Logik für Master und Messmodule implemnetiert
*/

#include "..\lib/FlexCAN/FlexCAN.h"

class canbus
{
public:

	canbus();
	bool write(CAN_message_t msg);
	bool read(CAN_message_t msg);
	FlexCAN can;
	CAN_message_t broadcast; //Startbefehl für die Messmodule
	CAN_message_t errorlog;
};

#endif // !CANBUS_H
