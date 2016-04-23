#include "sensor.h"
#include "config.h"

//counting var for generating the channel array
int ch_stat = 0;

sensor::sensor()
{
	
}


void sensor::beginHCLA() {
	pinMode(s0, OUTPUT);
	pinMode(s1, OUTPUT);
	pinMode(s2, OUTPUT);
	Wire.begin();
#ifdef DEBUGING
	Serial.println("I2C online");
#endif //DEBUGGING

#ifdef SENSOR0

	sensor::setCh(SENSOR0);
#endif
#ifdef SENSOR1

	sensor::setCh(SENSOR1);
#endif
#ifdef SENSOR2
	sensor::setCh(SENSOR2);
#endif

#ifdef SENSOR3

	sensor::setCh(SENSOR3);
#endif
#ifdef SENSOR4
	sensor::setCh(SENSOR4);
#endif
#ifdef SENSOR5
	sensor::setCh(SENSOR5);
#endif
#ifdef SENSOR6
	sensor::setCh(SENSOR6);
#endif
#ifdef SENSOR7
	sensor::setCh(SENSOR7);
#endif

	ch_size = ch_stat;
}

uint16_t sensor::readHCLA(int channel) {
	sensor::SelectChannel(channel);

	uint8_t msb, lsb;
	uint16_t rawPressure;
	Wire.requestFrom(PRESSURE_SENSOR_ADRESS, 2);
	msb = Wire.receive();
	lsb = Wire.receive();
	rawPressure = (int)(msb << 8) | lsb;
	return rawPressure;
}

//channel select f�r 8 Kan�le
void sensor::SelectChannel(int channel) {
	int controlPin[3] = { s0, s1, s2 };

	int muxChannel[8][3] = {
		{ 0, 0, 0 }, //channel 0
		{ 1, 0, 0 }, //channel 1
		{ 0, 1, 0 }, //channel 2
		{ 1, 1, 0 }, //channel 3
		{ 0, 0, 1 }, //channel 4
		{ 1, 0, 1 }, //channel 5
		{ 0, 1, 1 }, //channel 6
		{ 1, 1, 1 }, //channel 7
	};

	//loop through the 3 controllpins
	for (int i = 0; i < 3; i++) {
		digitalWrite(controlPin[i], muxChannel[channel][i]);
	}
}



//generates an array which contains the sensor channel numbers
void sensor::setCh(int chnum) {
	channels[ch_stat] = chnum;
	ch_stat++;
}