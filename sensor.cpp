#include "sensor.h"

#define PRESSURE_SENSOR_ADRESS	0x7


int ch_stat=0;


sensor::sensor(){
#ifdef HCLA
Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, I2C_RATE_400);

#ifdef SENSOR0
setCh(SENSOR0, ch_stat);
#endif 
#ifdef SENSOR1
setCh(SENSOR1, ch_stat);
#endif  
#ifdef SENSOR2
setCh(SENSOR2, ch_stat);
#endif // SENSOR2

#ifdef SENSOR3
setCh(SENSOR3, ch_stat);
#endif 
#ifdef SENSOR4
setCh(SENSOR4, ch_stat);
#endif 
#ifdef SENSOR5
setCh(SENSOR5, ch_stat);
#endif
#ifdef SENSOR6
setCh(SENSOR6, ch_stat);
#endif
#ifdef SENSOR7
setCh(SENSOR7, ch_stat);
#endif





#endif

#ifdef MPU9150

#endif

}

//Destructor
sensor::~sensor()
{
}



uint16_t sensor::readHCLA(int channel){
	sensor::SelectChannel(channel);
	
	uint8_t msb, lsb;
	uint16_t rawPressure;
	Wire.requestFrom(PRESSURE_SENSOR_ADRESS, 2, I2C_STOP);
	msb = Wire.readByte();
	lsb = Wire.readByte();
	if (Wire.getError() == 0){
		return rawPressure = (int)(msb << 8) | lsb;
	}
	else{
	//Error Funktion
	}
}


//channel select für 8 Kanäle
void sensor::SelectChannel(int channel){

	int controlPin[] = { s0, s1, s2};

	int muxChannel[8][3] = {
		{ 0, 0, 0 }, //channel 0
		{ 1, 0, 0 }, //channel 1
		{ 0, 1, 0}, //channel 2
		{ 1, 1, 0}, //channel 3
		{ 0, 0, 1}, //channel 4
		{ 1, 0, 1}, //channel 5
		{ 0, 1, 1}, //channel 6
		{ 1, 1, 1}, //channel 7
	};

	//loop through the 3 controllpins
	for (int i = 0; i < 3; i++){
		digitalWrite(controlPin[i], muxChannel[channel][i]);
	}
}


 float sensor::calc_airspeed(){
	uint16_t temp = readHCLA(CH_AIRSPEED);
	float airspeed;
	//temp*x; // Airspeed calculation	
	 
	return airspeed;
}

  
 void sensor::setCh(int chnum,int ch_stat){
	 
	channels  = new int;
	channels[ch_stat] = chnum;
	ch_stat++;
 }