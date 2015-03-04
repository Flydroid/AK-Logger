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
//#define MASTER



#ifdef MESSMODUL
#define HCLA 5
int channels[] = {0,1,2,3};	//Bsp für ein normal bestücktes Messmodul, mit 4 HCLA

#endif


#ifdef MASTER


#endif


#ifdef TELEMETRY

#endif












#endif // !1
