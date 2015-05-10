#pragma once

/*
Klasse für das Auslesen der Sensoren
Differenzdruck Sensor HCLA
Interialmeasurementunit MPU9150
Statischer Drucksensor
*/

#include "config.h"
#include "i2c_t3/i2c_t3.h"


/* Senoren:*/
#ifdef HCLA
#define PRESSURE_SENSOR_ADRESS 0x78
//Multiplexer Kontrollpins, für Messmodul angepasst
#define s0	10
#define s1	11
#define s2	12


#endif

// MPU9150, schon dabei um die Struktur darzustellen
#ifdef MPU9150

#endif




class sensor
{
public:
	sensor();
	~sensor();

	uint16_t readHCLA(int channel);
	float calc_airspeed();
	int* channels; 
	void setCh(int chnum, int ch_stat);
	void SelectChannel(int channel);

private:

	int _ch_num = 0;


	
	

};

