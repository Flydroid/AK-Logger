#include <Arduino.h>
#include <Arduino.h>


#include "config.h"
#include <EEPROM.h>



#ifdef CANBUS
time_t getTeensy3Time();
uint8_t monthhelper(char* month);
void measureHCLA();
void send_broadcast();
void send_telemetry();

void setup();

void loop();
void SetTimeCompile();
#line 10 "AK-Logger.ino"
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
ArduinoOutStream cout(sd_file);
const uint8_t BASE_NAME_SIZE = sizeof(BASE_FILENAME) - 1;
char fileName[16] = BASE_FILENAME "00.csv";
#endif

#ifdef GPS
#include "TinyGPSPlus/TinyGPS++.h"
TinyGPSPlus gps;
#endif

#ifdef CANBUS
#include "FlexCAN.h"
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
uint8_t	ID2 = 0x00;
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

#ifndef SD_LOG

ArduinoOutStream cout(Serial);
#define sd_file Serial
#endif //SDLOG

int checkedin_Modules;

#endif









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
// Find an unused file name.
while (sd.exists(fileName)) {
if (fileName[BASE_NAME_SIZE + 1] != '9') {
fileName[BASE_NAME_SIZE + 1]++;
}
else if (fileName[BASE_NAME_SIZE] != '9') {
fileName[BASE_NAME_SIZE + 1] = '0';
fileName[BASE_NAME_SIZE]++;
}
else {
Serial.println("can't create filename");
}
}

if (!sd_file.open(fileName, O_RDWR | O_CREAT | O_AT_END)) {
//error handling
Serial.println("SD open fail");
}
if (!sd_file.timestamp(T_CREATE, year(), month(), day(), hour(), minute(), second())) {
Serial.println("Write timestamp fail");
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








#ifdef CANBUS

int m_num = 1;
char m_tmp[8];
c_msg.id = 0x00;
c_msg.buf[0] = 0;
c_msg.len = 8;
if (cbus.write(c_msg)) {
Serial.println("MasterMSGsend");
}
elapsedMillis m_checkin;
while (m_checkin < 1000) {
CAN_message_t msg;
//	Serial.println(m_checkin);
if (cbus.read(msg)) {
module_data[m_num].ID = msg.buf[0];
module_data[m_num].ID2 = msg.buf[1];
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



















#endif //CANBUS

#ifdef HCLA
//Write Master sensor data to module_date[0x00]
module_data[MASTER_ID].ID = MASTER_ID;
module_data[MASTER_ID].NAME = MASTER_NAME;
module_data[MASTER_ID].SENSOR_NUMBER = hcla.ch_size;
Serial.println("Moduledata ok");

#endif // HCLA

//Start display, show module name and state
//get time

//Write FileHeader
cout << "AK-X Logger v.1 \n Logdatei vom: ";
cout << day() << "." << month() << "." << year() << " um " << hour() << ":" << minute() << "Uhr";
cout << "\n Eingecheckte Module\n";
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
#ifdef SD_LOG

sd_file.close();
Serial.println("File closed.");
#endif
#ifdef DEBUGING
Serial.println("SD Header ok");
#endif
digitalWrite(13, LOW);

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
for (int i = 0; i < module_data[MASTER_ID].SENSOR_NUMBER; i++) {
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
if (module_data[msg.id].ID2 != 0x00) {
cbus.read(msg2);
if (msg2.id == module_data[msg.id].ID2) {
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
#ifdef SD_LOG
if (!sd_file.open(fileName, O_RDWR | O_AT_END)) {
//error handling
Serial.println("SD open fail");
}

#endif
sd_file.print(datastring);

#ifdef SD_LOG
sd_file.timestamp(T_WRITE, year(), month(), day(), hour(), minute(), second());
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









//Send heartbeat

mav.heartbeat();

noInterrupts();
c_telemetry = false;
interrupts();
}

#endif
#endif


}

#ifdef MASTER
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
tm.Year = atoi(year) - 1970;
time_t t = makeTime(tm);
time_t datetime = 0;
datetime += (EEPROM.read(0x00) << 24);
datetime += (EEPROM.read(0x01) << 16);
datetime += (EEPROM.read(0x02) << 8);
datetime += EEPROM.read(0x03);
int n = memcmp(&t, &datetime, 4);
if (n > 0 || n < 0) {
Teensy3Clock.set(t); // set the RTC  with time at compile
EEPROM.write(0x00, (t & 0xFF000000) >> 24);
EEPROM.write(0x01, (t & 0x00FF0000) >> 16);
EEPROM.write(0x02, (t & 0x0000FF00) >> 8);
EEPROM.write(0x03, (t & 0x000000FF));
}
t = Teensy3Clock.get();
setTime(t);

#ifdef DEBUGING
switch (timeStatus())
{
case timeNotSet:
Serial.println("timenotSet");
break;
case timeSet:
Serial.println("timeset");
break;
case timeNeedsSync:
Serial.println("timeneedssync");
break;
default:
break;
}
#endif
}
#endif