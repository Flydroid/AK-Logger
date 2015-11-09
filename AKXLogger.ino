
#include "config.h"

#ifdef CANBUS
void send_broadcast();
#endif
#ifdef TELEMETRY
void send_telemetry();
#endif

#ifdef MAVLINK

#include "serial.h"

serial mav;

#endif




#ifdef SD_LOG
#include "SdFat.h"
SdFat sd;
SdFile sd_file;

#endif

#ifdef GPS
#include "TinyGPSPlus/TinyGPS++.h"
TinyGPSPlus gps;
#endif

#ifdef CANBUS
#include <FlexCAN.h>
#include "canbus.h"
canbus cbus;
CAN_message_t c_msg;
CAN_message_t c_msg2;
#endif

#ifdef HCLA
#include <i2c_t3.h>
#include "sensor.h"
sensor hcla;
#endif

#ifdef MASTER
//Set up Time functions
#include <Time.h>
time_t getTeensy3Time()
{
	return Teensy3Clock.get();
}
uint8_t monthhelper(char* month) {
	for (int i = 1; i <= 12;) {
		if (!strcmp(month, monthShortStr(i))) {
			return i;
		}
		else
		{
			i++;
		}
	}
}
void SetTimeCompile();
TimeElements tm;



//struct with all information on a connected module
struct MODULE {
	uint8_t ID;
	uint8_t	ID_EXT = 0x00;
	uint8_t SYSTEM_STATE;
	String NAME;
	bool READ_STATE = 0;
	uint16_t data1[8];
	uint16_t data2[8];
	uint8_t SENSOR_NUMBER;
}tmp, module_data[MAX_MODULES + 1];

//Define timer and volatiles timing control
#ifdef CANBUS
IntervalTimer broadcast;
volatile bool c_broadcast;
#endif //CANBUS

#ifdef TELEMETRY
volatile bool c_telemetry;
IntervalTimer telemetry;
#endif

#ifndef SDLOG
#define sd_file Serial
#endif //SDLOG

int checkedin_Modules;

#endif

#ifdef MESSMODUL
struct SYSTEM {
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
void send_broadcast() {
	c_broadcast = true;
}

#endif //CANBUS
#ifdef TELEMETRY
void send_telemetry() {
	c_telemetry = true;
}
#endif

#endif // MASTER

void setup() {
#ifdef DEBUGING
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	delay(2000);
	digitalWrite(13, LOW);
	Serial.begin(9600);
	Serial.println("Serial online");
#endif	//DEBUG

#ifdef MASTER
	//Sync Time after compile
	setSyncProvider(getTeensy3Time);
	SetTimeCompile();


	//SD card
#ifdef SD_LOG
	sd.begin(SS_PIN, SPI_HALF_SPEED);
	char fileName[11] = BASE_FILENAME;
	//fileName[0] = datetime.date;
	//+datetime.time + BASE_FILENAME;

	if (!sd_file.open("Logger.dat", O_RDWR | O_CREAT | O_AT_END)) {
		//error handling
		Serial.println("SD open fail");
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

	int m_num = 1;
	char m_tmp[8];
	elapsedMillis m_checkin;

	while (m_checkin < 1000) {
		CAN_message_t msg;

		if (cbus.read(msg)) {
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
	}
	checkedin_Modules = m_num;

	Serial.println("All modules checkedin");
	//sort the check-in modules according their id' value

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



#endif //CANBUS

#ifdef HCLA
	//Write Master sensor data to module_date[0x00]
	module_data[MASTER_ID].ID = MASTER_ID;
	module_data[MASTER_ID].NAME = MASTER_NAME;
	module_data[MASTER_ID].SENSOR_NUMBER = hcla.ch_size;
	Serial.println("Moduledata ok");

#endif // HCLA

	//Start display, show module name and state

	//Write FileHeader
	sd_file.print("AK-X Logger v.1 \n Logdatei vom: ");

	sd_file.print("um");

	sd_file.print("\n Eingeckete Module\n");
	for (uint16_t i = 0; i < checkedin_Modules; i++) {
		sd_file.print(module_data[i].NAME);
		sd_file.print(" ID: ");
		sd_file.print(module_data[i].ID, HEX);
		sd_file.print(" mit ");
		sd_file.print(module_data[i].SENSOR_NUMBER);
		sd_file.print(" Sensoren\n");
	}
	sd_file.print("\n Logdaten: \n");
	for (uint16_t i = 0; i < checkedin_Modules; i++) {
		sd_file.print(module_data[i].NAME);
		for (int x = 1; x < module_data[i].SENSOR_NUMBER; x++) {
		}
	}
	sd_file.print("\n Zeit [ms]\t");
	for (uint16_t i = 0; i < checkedin_Modules; i++) {
		sd_file.print(module_data[i].NAME);
		sd_file.print("\t");
		for (int x = 1; x <= module_data[i].SENSOR_NUMBER; x++) {
			sd_file.print("S");
			sd_file.print(x);
			sd_file.print("\t");
		}
	}
	sd_file.print("\n");
	//Close File
#ifdef SDLOG
	sd_file.close();
	Serial.println("File closed.");
#endif
#ifdef DEBUGING
	Serial.println("SD Header ok");
#endif
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
	for (int i = 0; i < 8; i++) {
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

void loop() {
#ifdef MASTER

#ifdef CANBUS
	//Read sensor, send broadcast, get data from Modules and Store it.
	if (c_broadcast) {
		//send broadcast
		cbus.write(cbus.broadcast);

		//get time
		String datastring;
		datastring += String(millis());
		datastring += "\t";

#endif // CANBUS

#ifdef HCLA
		//read the master sensors
		for (uint16_t i = 0; i < module_data[MASTER_ID].SENSOR_NUMBER; i++) {
			module_data[0].data1[i] = hcla.readHCLA(hcla.channels[i]);
		}
#endif
#ifdef CANBUS

		//read measurement modules
		for (uint16_t recv_data = 1; recv_data < checkedin_Modules - 1; recv_data++) {
			CAN_message_t msg, msg2;
			cbus.read(msg);
			if (!module_data[msg.id].READ_STATE) {
				continue;
			}
			for (int i = 0; i < 8; i++) {
				uint8_t msb, lsb;
				msb = msg.buf[i];
				lsb = msg.buf[i + 1];
				module_data[msg.id].data1[i / 2] = msb << 8 | lsb;
			}
			if (module_data[msg.id].ID_EXT != 0x00) {
				cbus.read(msg2);
				if (msg2.id == module_data[msg.id].ID_EXT) {
					for (int i = 0; i < 8; i++) {
						uint8_t msb, lsb;
						msb = msg.buf[i];
						lsb = msg.buf[i + 1];
						module_data[msg.id].data1[4 + (i / 2)] = msb << 8 | lsb;
					}
				}
				else {
					//error wrong second canbus massage
				}
			}
			module_data[msg.id].READ_STATE = 1;
		}
#endif // CANBUS

		//save data to string

		for (int i = 0; i < checkedin_Modules; i++) {
			for (int p = 0; p < module_data[i].SENSOR_NUMBER; p++) {
				uint16_t data = (int)(module_data[i].data1[p]);
				datastring += String(data) + "\t";
			}
		}

		datastring += "\n";
		//store datastring
#ifdef SDLOG
		if (!sd_file.open("Logger.dat", O_RDWR | O_CREAT | O_AT_END)) {
			//error handling
			Serial.println("SD open fail");
		}
#endif
		sd_file.print(datastring);
#ifdef SDLOG
		sd_file.close();
#endif

#ifdef CANBUS
		noInterrupts();
		c_broadcast = false;
		interrupts();
#endif

	}

#ifdef MAVLINK
	if (c_telemetry) {
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
	if (c_msg.id == 0x00) {	   //0x00 is the MASTER_ID
		Serial.print("Got Broadcast");
		switch (c_msg.buf[0]) {
		case 1:
			c_msg.id = MESSMODUL_ID;
			c_msg2.id = MESSMODUL_ID_EXT;
			for (uint16_t i = 0; i < hcla.ch_size; i++) {
				uint16_t tmp = hcla.readHCLA(hcla.channels[i]);
				if (i < 4) {
					c_msg.buf[0 + i * 2] = tmp >> 8;// msb
					c_msg.buf[1 + i * 2] = tmp; //lsb
				}
				else {
					c_msg2.buf[-8 + i * 2] = tmp << 8;
					c_msg2.buf[-7 + i * 2] = tmp;
				}
			}
			c_msg.len = sizeof(c_msg.buf);
			cbus.write(c_msg);
			if (sizeof(c_msg2) != 0) {
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

void SetTimeCompile() {
	char hour[2], seconds[2], minute[2], month[3], day[2], year[4];
	for (int i = 0; i < 2; i++) {
		hour[i] = TIME[i];
		minute[i] = TIME[i + 3];
		seconds[i] = TIME[i + 6];
	}
	for (int i = 0; i < 3; i++) {
		month[i] = DATE[i];
	}
	for (int i = 0; i < 2; i++) {
		day[i] = DATE[i + 4];
	}
	for (int i = 0; i < 4; i++) {
		year[i] = DATE[i + 7];
	}

	tm.Hour = atoi(hour);
	tm.Minute = atoi(minute);
	tm.Second = atoi(seconds);
	tm.Month = monthhelper(month);
	tm.Day = atoi(day);
	tm.Year = atoi(year)-1970;
	time_t t = makeTime(tm);
	if (t != 0 && t > Teensy3Clock.get()) {
		Teensy3Clock.set(t); // set the RTC
		setTime(t);
#ifdef DEBUGING
		Serial.println("RTC mit Compile Time in sync");
#endif
	}
	else
	{
		t = Teensy3Clock.get();
		setTime(t);
		
	}
}