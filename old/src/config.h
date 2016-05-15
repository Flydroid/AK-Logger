#ifndef CONFIG_H
#define CONFIG_H



/*
Konfigurationsdatei:
Hier wird festlegt als was das Modul geflasht wird.
Master, Messmodul oder Telemetriemodul

Die Funktionien der einzelen Module sind hier definiert.

*/



#define HCLA
#define SD_LOG
#define DEBUGING



#define TIME __TIME__
#define DATE __DATE__

#define MASTER_ID 0x00
#define MASTER_NAME "AK-Logger Master"

//Der AK-Logger hat normal keine Module und der CAN Bus ist deaktiviert.
//#define CANBUS
#define MAX_MODULES 0




//SD-Card Definitions:
#define SS_PIN 14
#define BASE_FILENAME "AKLogger"



#ifdef HCLA

#define SENSOR0	 0
#define SENSOR1	 1
#define SENSOR2	 2
//#define SENSOR3 3
//#define SENSOR4 4
//#define SENSOR5 5
//#define SENSOR6 6
//#define SENSOR7 7

#endif

#endif // !1
