#ifndef CONFIG_H
#define CONFIG_H
#include "string.h"

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
int channels[] = {0,1,2,3};	//Bsp für ein normal bestücktes Messmodul, mit 4 HCLA

#endif


#ifdef MASTER
#define HCLA
#define MAVLINK
#define CANBUS

#define CH_AIRSPEED  0
#define CH_ATTACK	 1
#define CH_SLIP	     2


#endif


#ifdef TELEMETRY

#endif

#ifdef HCLA


#define SENSOR0	 0
#define SENSOR1	 3
//#define SENSOR2	 0;
//#define SENSOR3	;
//#define SENSOR4	;
//#define SENSOR5	;
//#define SENSOR6	
//#define SENSOR7



#endif












#endif // !1
