#include "sensor.h"
#include "config.h"
#include "i2c_t3\i2c_t3.h"

sensor::sensor(){
#ifdef HCLA
Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);

#endif

#ifdef MPU9150

#endif

}

//Destructor
sensor::~sensor()
{
}


#ifdef HCLA
uint16_t sensor::readHCLA(int channel){
	SelectChannel(channel);
	uint8_t msb, lsb;
	uint16_t rawPressure;
	Wire.requestFrom(PRESSURE_SENSOR_ADRESS, 2, I2C_STOP);
	while (Wire.available()){
		 msb = Wire.read();
		 lsb = Wire.read();
	}
	return rawPressure = (int)(msb << 8) | lsb;
}
#endif


void SelectChannel(int channel){
	int controlPin[] = { s0, s1, s2, s3 };

	int muxChannel[16][4] = {
		{ 0, 0, 0, 0 }, //channel 0
		{ 1, 0, 0, 0 }, //channel 1
		{ 0, 1, 0, 0 }, //channel 2
		{ 1, 1, 0, 0 }, //channel 3
		{ 0, 0, 1, 0 }, //channel 4
		{ 1, 0, 1, 0 }, //channel 5
		{ 0, 1, 1, 0 }, //channel 6
		{ 1, 1, 1, 0 }, //channel 7
		{ 0, 0, 0, 1 }, //channel 8
		{ 1, 0, 0, 1 }, //channel 9
		{ 0, 1, 0, 1 }, //channel 10
		{ 1, 1, 0, 1 }, //channel 11
		{ 0, 0, 1, 1 }, //channel 12
		{ 1, 0, 1, 1 }, //channel 13
		{ 0, 1, 1, 1 }, //channel 14
		{ 1, 1, 1, 1 }  //channel 15
	};

	//loop through the 4 sig
	for (int i = 0; i < 4; i++){
		digitalWrite(controlPin[i], muxChannel[channel][i]);
	}
}