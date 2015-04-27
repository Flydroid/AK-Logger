





#include "config.h"

#ifdef MAVLINK
#include "mavlink\mavlink.h"L
#include "serial.h"

serial mav;

#endif

#ifdef SD_LOG
#include "SdFat\SdFat.h"
#endif


#include "FlexCAN\FlexCAN.h"
#include "canbus.h"
canbus cbus;
CAN_message_t c_msg;
CAN_message_t c_msg2;

#ifdef HCLA
#include "i2c_t3\i2c_t3.h"
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
	c_msg.id = MESSMODUL_ID;
	c_msg2.id = MESSMODUL_ID;
	if (c_msg.id == cbus.broadcast.id  && c_msg.buf == cbus.broadcast.buf){
		for (int i = 0; i < sizeof(hcla.channels); i++){
			uint16_t tmp = hcla.readHCLA(hcla.channels[i]);
			if (i < 4){
				c_msg.buf[0 + i * 2] = tmp << 8;
				c_msg.buf[1 + i * 2] = tmp;
			}
			else{
				c_msg2.buf[-8 + i * 2] = tmp << 8;
				c_msg2.buf[-7 + i * 2] = tmp;
			}
		}
		c_msg.len = sizeof(c_msg.buf);
		cbus.write(c_msg);
		if (sizeof(c_msg2) != 0){
			cbus.write(c_msg2);
		}

	}

#endif
}

void measureHCLA(){

}