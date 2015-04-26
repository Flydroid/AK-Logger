#include "FlexCAN/FlexCAN.h"


/*
Klasse für die CAN-BUS Kommunikation
Hier wird die CAN-BUS Funktionalität und die Logik für Master und Messmodule implemnetiert
*/

#include "FlexCAN/FlexCAN.h"

class canbus
{
public:

	canbus();
	~canbus();
	void write(CAN_message_t msg);
	void read(CAN_message_t msg);
	FlexCAN can;
	CAN_message_t broadcast; //Startbefehl für die Messmodule
	CAN_message_t errorlog;
	

	



};

