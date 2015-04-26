


#include "mavlink\mavlink.h"
#include "SdFat\SdFat.h"
#include "config.h"

#ifdef MAVLINK
#include "serial.h"
serial mav;

#endif

#include "canbus.h"
canbus cbus;
CAN_message_t c_msg;

#ifdef HCLA
#include "sensor.h"
sensor hcla;
#endif

void setup(){





Serial.begin(115200);
Serial.println("Serial online");

IntervalTimer messTimer;
messTimer.begin(measureHCLA, 10);






	





}


void loop(){
#ifdef MAVLINK
	mav.heartbeat();
	//mav.air_speed();
#endif


#ifdef MASTER
	cbus.write(cbus.broadcast);

#endif




#ifdef MESSMODUL
	cbus.read(c_msg);		
	if (c_msg.id == 0x1){
		for (int i = 0; i < sizeof(hcla.sensors); i++){
			uint16_t tmp = hcla.readHCLA(i);
			c_msg.buf[0 + i] = tmp << 8;
			c_msg.buf[1 + i] = tmp;
		}
	}
							  




#endif









	

	
	



}

void measureHCLA(){

}