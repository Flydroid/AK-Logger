





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

#ifdef MASTER
struct MODULES{
	uint8_t ID;
	uint8_t	ID_EXT = 0x00;
	uint8_t SYSTEM_STATE;
	String NAME;
	bool READ_STATE = 0;
	uint8_t data1[8];
	uint8_t data2[8];


}tmp;
MODULES *module_data;

#endif // MASTER



#ifdef MESSMODUL
struct SYSTEM{
	uint8_t POWER_UP = 0;
	uint8_t READY = 1;
	uint8_t ERROR = 2;
} SYSTEM_STATE;

#endif 


void setup(){
#ifdef DEBUG
	Serial.begin(115200);
	Serial.println("Serial online");
#endif


#ifdef MASTER

	/*
	Master boot up
	*/

	int m_num=0;
	char m_tmp[8];
	elapsedMillis m_checkin;

	/*	reads the incoming check-in massages from the different modules
	Every module gets registered with its ids, state and name
	an array of structs is created which holds the information.
	if during 1000 milliseconds no module checks in, all modules are accounted for
	--->>> Check during testing
	*/
	while (m_checkin < 1000){
		CAN_message_t msg;
		if (!cbus.read(msg)){
			continue;
		}

		module_data = new MODULES;
		module_data[m_num].ID = msg.buf[0];
		module_data[m_num].ID_EXT = msg.buf[1];
		module_data[m_num].SYSTEM_STATE = msg.buf[2];
		for (int i = 0; i < 8; i++)
		{
			m_tmp[i] = c_msg2.buf[i];
		}
		module_data[m_num].NAME = String(m_tmp);
		m_checkin = 0;
		m_num++;
	}

	//sort the check-in modules according their id' value
	int max = 5;
	bool change;
	for (int t = 0; t < max; t++)  {
		for (int i = 0; i < sizeof(module_data); i++){
			if (module_data[i].ID < module_data[i + 1].ID){
				tmp = module_data[i];
				module_data[i] = module_data[i + 1];
				module_data[i + 1] = tmp;
				change = 1;
			}
		}
		if (!change){
			break;
		}
		change = 0;
	}
	
	//shift all elements in module_data by one
	for (int i = 0; i < sizeof(module_data); i++){
		tmp = module_data[i+1];
		module_data[i+1] = module_data[i];
		module_data[i + 2] = tmp;
	}






#endif

#ifdef MESSMODUL


	//wait for master to boot
	delay(2000);
	//announce module to master
	c_msg.id = MESSMODUL_ID;
	c_msg.buf[0] = MESSMODUL_ID;
	c_msg.buf[1] = MESSMODUL_ID_EXT;
	c_msg.buf[2] = SYSTEM_STATE.POWER_UP;
	c_msg.len = sizeof(c_msg.buf);
	cbus.write(c_msg);
	c_msg2.id = MESSMODUL_ID_EXT;
	for (int i = 0; i < 8; i++){
		c_msg2.buf[i] = int(MOD_NAME[i]);
	}
	c_msg2.len = 8;
	cbus.write(c_msg2);

	IntervalTimer messTimer;
	messTimer.begin(measureHCLA, 10);

#endif















}


void loop(){



#ifdef MASTER

	//Send heartbeat
#ifdef MAVLINK
	mav.heartbeat();
#endif


	//read sensors
	uint16_t s_buf[sizeof(hcla.channels)];
	for (int i = 0; i < sizeof(hcla.channels); i++){
		uint16_t tmp = hcla.readHCLA(hcla.channels[i]);
		s_buf[0 + i * 2] = tmp << 8;
		s_buf[1 + i * 2] = tmp;
	}

	//send broadcast
	cbus.write(cbus.broadcast);


	//read measurement modules
	for (int recv_data = 1; recv_data < sizeof(module_data); recv_data++){
		CAN_message_t msg, msg2;
		cbus.read(msg);
		if (!module_data[msg.id].READ_STATE){
			continue;
		}
		for (int i = 0; i < 8; i++){
			module_data[msg.id].data1[i] = msg.buf[i];
		}
		if (module_data[msg.id].ID_EXT != 0x00){
			cbus.read(msg2);
			if (msg2.id == msg.id){
				for (int i = 0; i < 8; i++){
					module_data[msg.id].data2[i] = msg.buf[i];
				}
			}
			else{
			//error wrong second canbus massage
			}

		}
		module_data[msg.id].READ_STATE = 1;
	}



	//Store data	


	//save data to  SD



	/*
	calculate Telemetry data
	*Airspeed
	*angel of attack
	*slipangle
	*GPS
	*lift
	send Telemetry data
	*/




#endif




#ifdef MESSMODUL


	cbus.read(c_msg);
	if (c_msg.id == MASTER_ID){
		switch (c_msg.buf[0]){
		case 1:
			c_msg.id = MESSMODUL_ID;
			c_msg2.id = MESSMODUL_ID_EXT;
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
				c_msg2.len = sizeof(c_msg2.buf);
				cbus.write(c_msg2);
			}
		case 2:
			// Send errorlog
		default:
			break;
		}

	}




}
#endif

//Interrupt function
void measureHCLA(){

}