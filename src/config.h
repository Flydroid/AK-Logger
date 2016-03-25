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
  

//#define TELEMETRY
#define MASTER


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
