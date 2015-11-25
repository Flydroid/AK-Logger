#ifndef CONFIG_H
#define CONFIG_H



/*
Konfigurationsdatei:
Hier wird festlegt als was das Modul geflasht wird.
Master, Messmodul oder Telemetriemodul

Die Funktionien der einzelen Module sind hier definiert.

*/

#include "SdFat.h"
/* Module */
//#define MESSMODUL

//#define TELEMETRY
//#define MASTER

#ifdef MESSMODUL
#define HCLA
#define DEBUGING
#define CANBUS


/* Define identifying  CAN addresses for
the measurement modules
0x00 is reserved ID for the master module
The MESSMODUL_ID is counted from 0x01 to 0x10
The second ID is for Modules which need more
than one massage for sending its data  */

#define MESSMODUL1_ID 0x01
#define MESSMODUL1_ID2 0x11
#define MESSMODUL1_NAME "mitte"
#define MESSMODUL2_ID 0x02
#define MESSMODUL2_ID2 0x22
#define MESSMODUL2_NAME "Flügel"
#define MESSMODUL3_ID 0x03
#define MESSMODUL3_ID2 0x33
#define MESSMODUL3_NAME "winglet"

//name of the module, max 8 characters long




#endif

#ifdef MASTER
#define HCLA
//#define MAVLINK
#define SD_LOG
#define DEBUGING
#define CANBUS


#define TIME __TIME__
#define DATE __DATE__

#define MASTER_ID 0x00
#define MASTER_NAME "AK-Logger Master"
#define MAX_MODULES 3
//#define GPS
#ifdef GPS
#define SERIAL_GPS Serial2
#endif

#define CH_AIRSPEED  0x00
#define CH_ATTACK	 0x01
#define CH_SLIP	     0x02

//SD-Card Definitions:
#define SS_PIN 14
#define BASE_FILENAME "AKXLogger"

#endif

#ifdef TELEMETRY

#endif

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

