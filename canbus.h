#include "FlexCAN/FlexCAN.h"


/*
Klasse f�r die CAN-BUS Kommunikation
Hier wird die CAN-BUS Funktionalit�t und die Logik f�r Master und Messmodule implemnetiert
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
	CAN_message_t broadcast; //Startbefehl f�r die Messmodule
	CAN_message_t errorlog;
	

	



};

