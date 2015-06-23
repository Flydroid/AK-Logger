

#ifndef SENSOR_H
#define SENSOR_H




/*
Klasse für das Auslesen der Sensoren
Differenzdruck Sensor HCLA
Interialmeasurementunit MPU9150
Statischer Drucksensor
*/

#include "config.h"
#include "i2c_t3.h"
#include "mavlink.h"


/* Senoren:*/

#define PRESSURE_SENSOR_ADRESS 0x78
//Multiplexer Kontrollpins, für Messmodul angepasst
#define s0	10
#define s1	11
#define s2	12





class sensor
{
public:
	sensor();


	uint16_t readHCLA(int channel);
	void begin();
	float calc_airspeed();
	uint8_t* channels;
	void setCh(int chnum);
	void SelectChannel(int channel);
	uint8_t ch_size;

private:

	int _ch_num = 0;
	int ch_stat = 0;
	int _p = 1;





};

#endif // !SENSOR_H

