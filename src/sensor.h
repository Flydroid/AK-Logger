

#ifndef SENSOR_H
#define SENSOR_H




/*
Klasse für das Auslesen der Sensoren
Differenzdruck Sensor HCLA
Interialmeasurementunit MPU9150
Statischer Drucksensor
*/
#include "Wire.h"
#include "config.h"





/* Senoren:*/

#define PRESSURE_SENSOR_ADRESS 0x78
//Multiplexer Kontrollpins, für Messmodul angepasst

#define s0	6
#define s1	5
#define s2	2






class sensor
{
public:
	sensor();
	
	uint16_t readHCLA(int channel);
	void beginHCLA();
	uint8_t channels[8];
	void setCh(int chnum);
	void SelectChannel(int channel);
	uint8_t ch_size;

private:

	int _ch_num = 0;
	int ch_stat = 0;
	int _p = 1;





};

#endif // !SENSOR_H

