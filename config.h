#ifndef CONFIG_H
#define CONFIG_H



/*
Konfigurationsdatei:
Hier wird festlegt als was das Modul geflasht wird.
Master, Messmodul oder Telemetriemodul

Die Funktionien der einzelen Module sind hier definiert.

*/

/* Module */
//#define MESSMODUL

//#define TELEMETRY
#define MASTER

#ifdef MESSMODUL
#define HCLA
#define DEBUGING

/* Define identifying  CAN addresses for
the measurement modules
0x00 is reserved ID for the master module
The MESSMODUL_ID is counted from 0x01 to 0x10
The extended ID is for Modules which need more
than one massage for sending its data  */
#define MESSMODUL_ID 0x01
#define MESSMODUL_ID_EXT 0x11

//name of the module, max 8 characters long
#define MOD_NAME "mitte"

#endif

#ifdef MASTER
#define HCLA
//#define MAVLINK
#define SD_LOG
#define DEBUGING
//#define CANBUS




#define MASTER_ID 0x00
#define MASTER_NAME "AK-Logger Master"
#define MAX_MODULES 1
//#define GPS
#ifdef GPS
#define SERIAL_GPS Serial2
#endif

#define CH_AIRSPEED  0x00
#define CH_ATTACK	 0x01
#define CH_SLIP	     0x02

//SD-Card Definitions:
#define SS_PIN 14
#define BASE_FILENAME "Logger.dat"

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

