#ifndef CONFIG_H
#define CONFIG_H


/*
Konfigurationsdatei:
Hier wird festlegt als was das Modul geflasht wird.
Master, Messmodul oder Telemetriemodul

Die Funktionien der einzelen Module sind hier definiert.

*/

/* Module */
#define MESSMODUL


//#define TELEMETRY
#define MASTER



#ifdef MESSMODUL
#define HCLA 
#define MESSMODUL_ID 1

#endif


#ifdef MASTER
#define HCLA
#define MAVLINK
#define CANBUS
#define MASTER_ID 0

#define CH_AIRSPEED  0
#define CH_ATTACK	 1
#define CH_SLIP	     2


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
