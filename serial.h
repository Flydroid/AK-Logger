#pragma once

/*
Klasse für die Serialkommunikation mit PC, Funkmodul und Telemetrie
sowie die Implemntierug der Weitergabe von Fehlermeldungen
*/

#include "config.h"
#include "mavlink\mavlink.h"
#include "sensor.h"
class serial
{
public:

	serial();
	~serial();
	void heartbeat();
	void serial::air_speed(float airspeed);

private:
	int system_type;
	int autopilot_type;
	mavlink_message_t msg;
	uint8_t buf[MAVLINK_MAX_PACKET_LEN];


};

