





//#include <Time.h>
#include "config.h"

void send_broadcast();
int compareModules(const void* mod1, const void* mod2);
void send_telemetry();



#ifdef MAVLINK
#include "mavlink.h"
#include "serial.h"

serial mav;

#endif

#ifdef SD_LOG
#include "SdFat.h"
SdFat SD;
SdFile SD_File;

#endif

#ifdef GPS
#include "TinyGPSPlus/TinyGPS++.h"
TinyGPSPlus gps;
#endif



#include <FlexCAN.h>
#include "canbus.h"
canbus cbus;
CAN_message_t c_msg;
CAN_message_t c_msg2;



#ifdef HCLA
#include <i2c_t3.h>
#include "sensor.h"
sensor hcla;
#endif

#ifdef MASTER

//struct with all information on a connected module
struct MODULE{
	uint8_t ID;
	uint8_t	ID_EXT = 0x00;
	uint8_t SYSTEM_STATE;
	String NAME;
	bool READ_STATE = 0;
	uint8_t data1[8];
	uint8_t data2[8];
	uint8_t SENSOR_NUMBER;
}tmp, module_data[MAX_MODULES];

//Define timer and volatiles timing control
IntervalTimer broadcast;
IntervalTimer telemetry;
volatile bool c_broadcast;
volatile bool c_telemetry;

#endif

#ifdef MESSMODUL
struct SYSTEM{
	uint8_t POWER_UP = 0;
	uint8_t READY = 1;
	uint8_t ERROR = 2;
} SYSTEM_STATE;

#endif

/*
//Interrupt function
void measureHCLA(){
}
*/

#ifdef MASTER
#ifdef CANBUS
void send_broadcast(){
	c_broadcast = true;
}

int compareModules(const void* mod1, const void* mod2){
	return ((MODULE*)mod1)->ID - ((MODULE*)mod2)->ID;
}
#endif //CANBUS
#ifdef TELEMETRY
void send_telemetry(){
	c_telemetry = true;
}
#endif



#endif // MASTER

void setup(){
#ifdef DEBUGING
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	delay(2000);
	digitalWrite(13, LOW);
	Serial.begin(115200);
	Serial.println("Serial online");
#define SD_File Serial
#endif	//DEBUG

#ifdef MASTER

	//SD card
#ifdef SD_LOG
	SD.begin(SS_PIN, SPI_FULL_SPEED);
	char fileName[11] = BASE_FILENAME;
	//fileName[0] = datetime.date;
	//+datetime.time + BASE_FILENAME;

	if (!SD_File.open(fileName, O_WRITE | O_APPEND | O_CREAT)){
		//error handling
	}
#endif // SD_LOG

#ifdef HCLA
	hcla.begin();

#endif

#ifdef CANBUS
	broadcast.begin(send_broadcast, 10000);
#ifdef DEBUGING
	Serial.println("Broadcast online");
#endif
#endif //CANBUS
#ifdef TELEMETRY

	telemetry.begin(send_telemetry, 1000000);
#ifdef DEBUG
	Serial.println("Telemetry online");
#endif
#endif // TELEMETRY

	//Bootup end



	/*	reads the incoming check-in massages from the different modules
	Every module gets registered with its ids, state and name
	an array of structs is created which holds the information.
	if during 1000 milliseconds no module checks in, all modules are accounted for
	--->>> Check during testing
	*/
#ifdef CANBUS

	int m_num = 0;
	char m_tmp[8];
	elapsedMillis m_checkin;

	while (m_checkin < 10000){

		CAN_message_t msg;

		if (!cbus.read(msg)){

			continue;

		}

		module_data[m_num].ID = msg.buf[0];
		module_data[m_num].ID_EXT = msg.buf[1];
		module_data[m_num].SYSTEM_STATE = msg.buf[2];
		for (int i = 0; i < 8; i++)
		{
			m_tmp[i] = c_msg2.buf[i];
		}
		module_data[m_num].NAME = String(m_tmp);
#ifdef DEBUGING
		Serial.print(module_data[m_num].NAME);
		Serial.println(" online");
#endif
		m_checkin = 0;
		m_num++;
	}

	Serial.println("All modules checkedin");
	//sort the check-in modules according their id' value

	qsort(module_data, sizeof(module_data), sizeof(MODULE), compareModules);
	/*int max = 5;

	bool change;
	for (int t = 0; t < max; t++)  {
	for (uint16_t i = 0; i < sizeof(module_data); i++){
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
	}*/

	//shift all elements in module_data by one
	for (uint16_t i = 0; i < sizeof(module_data); i++){
		tmp = module_data[i + 1];
		module_data[i + 1] = module_data[i];
		module_data[i + 2] = tmp;
	}
#ifdef HCLA
	//Write Master sensor data to module_date[0x00]
	module_data[MASTER_ID].ID = MASTER_ID;
	module_data[MASTER_ID].NAME = MASTER_NAME;
	module_data[MASTER_ID].SENSOR_NUMBER = hcla.ch_size;

#endif // HCLA

	//Start display, show module name and state

	//Write FileHeader
	SD_File.print("AK-X Logger v.1/nLogdatei vom: ");
	//SD_File.print(datetime.date);
	SD_File.print("um");
	//SD_File.print(datetime.time);
	SD_File.print("/nEingeckete Module");
	for (uint16_t i = 1; i < sizeof(module_data); i++){
		SD_File.print(module_data[i].NAME);

		SD_File.print(module_data[i].ID);
		SD_File.print(" Sensoren=");
		SD_File.print(module_data[i].SENSOR_NUMBER);
		SD_File.print("/n");
	}
	SD_File.print("/nLogdaten:/n");
	for (uint16_t i = 1; i < sizeof(module_data); i++){
		SD_File.print(module_data[i].NAME);
		for (int x = 1; x < module_data[i].SENSOR_NUMBER; x++){
		}
	}
	SD_File.print("/nZeit [ms]\t");
	for (uint16_t i = 1; i < sizeof(module_data); i++){
		SD_File.print(module_data[i].NAME);
		SD_File.print("\t");
		for (int x = 1; x <= module_data[i].SENSOR_NUMBER; x++){
			SD_File.print("S");
			SD_File.print(x);
			SD_File.print("/t");
		}
	}
	SD_File.print("/n");
	//Close File

#ifdef SD_LOG
	SD_File.close();
#endif

#endif // CANBUS

#endif

#ifdef MESSMODUL

	//wait for master to boot
	digitalWrite(13, HIGH);
	delay(1000);
	//announce module to master
	c_msg.id = MESSMODUL_ID;
	c_msg.buf[0] = MESSMODUL_ID;
	c_msg.buf[1] = MESSMODUL_ID_EXT;
	c_msg.buf[2] = SYSTEM_STATE.POWER_UP;
	c_msg.buf[3] = hcla.ch_size;
	c_msg.len = sizeof(c_msg.buf);
	cbus.write(c_msg);
#ifdef DEBUGING
	Serial.println("msg1 send");
#endif
	c_msg2.id = MESSMODUL_ID_EXT;
	for (int i = 0; i < 8; i++){
		c_msg2.buf[i] = int(MOD_NAME[i]);
	}
	c_msg2.len = 8;
	cbus.write(c_msg2);
#ifdef DEBUGING
	Serial.println("msg2 send");
#endif

#ifdef DEBUGING
	digitalWrite(13, LOW);
	Serial.println("Module announced");
#endif // DEBUGGING

	/*
	IntervalTimer messTimer;
	messTimer.begin(measureHCLA, 10);
	*/
#endif
}

void loop(){



#ifdef MASTER

#ifdef CANBUS
	//Read sensor, send broadcast, get data from Modules and Store it.
	if (c_broadcast){
		//send broadcast
		cbus.write(cbus.broadcast);


		//get time
		SD_File.print(millis());
		SD_File.print("\t");
	}
#endif // CANBUS
#ifdef HCLA
	//read the master sensors
	for (uint16_t i = 0; i < hcla.ch_size; i++){
		module_data[0].data1[0 + i * 2] = hcla.readHCLA(hcla.channels[i]);
	}
#endif
#ifdef CANBUS

	//read measurement modules
	for (uint16_t recv_data = 1; recv_data < sizeof(module_data); recv_data++){
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
			if (msg2.id == module_data[msg.id].ID_EXT){
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

	//save data to string
	String datastring;
	for (int i = 0; i < sizeof(module_data); i++){
		for (int p = 0; p < module_data[i].SENSOR_NUMBER; p++){
			uint16_t data = (int)(module_data[i].data1[0 + p]) << 8 | module_data[i].data1[1 + p];
			datastring += String(data) + "\t";
		}
	}

	datastring += "\n";
	//store datastring
	SD_File.print(datastring);

	noInterrupts();
	c_broadcast = false;
	interrupts();


#endif // CANBUS


#ifdef MAVLINK
	if (c_telemetry){
		/*
		calculate Telemetry data
		*Airspeed
		*angel of attack
		*slipangle
		*GPS
		*lift
		send Telemetry data
		*/
		//Send heartbeat

		mav.heartbeat();

		noInterrupts();
		c_telemetry = false;
		interrupts();
	}

#endif
#endif

#ifdef MESSMODUL

	cbus.read(c_msg);
	if (c_msg.id == 0x00){	   //0x00 is the MASTER_ID
		Serial.print("Got Broadcast");
		switch (c_msg.buf[0]){
		case 1:
			c_msg.id = MESSMODUL_ID;
			c_msg2.id = MESSMODUL_ID_EXT;
			for (uint16_t i = 0; i < hcla.ch_size; i++){
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
#endif
}
