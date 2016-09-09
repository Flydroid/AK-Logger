//Configurations
#define LOG_INTERVAL_LENGTH_IN_MILLIS 100

#define USE_SERIAL_PORT
#define WAIT_FOR_SERIAL_TO_CONNECT

//Configuration end

#include <Arduino.h>
#include <elapsedMillis.h>
#include <Time.h>

#include "ak_logger.h"
#include "console_stream.h"
#include "sdcard_stream.h"
#include "sensirion_stream.h"
#include "time_stream.h"

AKLogger logger;

bool millisElapsed(int milliseconds) {
        static elapsedMillis timer;

        if(timer>LOG_INTERVAL_LENGTH_IN_MILLIS) {
                timer = 0;
                return true;
        }
        return false;
}

void setupOutputStreams() {
        logger.addOutputStream(new ConsoleStream);
        logger.addOutputStream(new SDCardStream("test","txt"));
}

void setupInputStreams() {
        logger.addInputStream(new TimeStream);
        logger.addInputStream(new SensirionStream);
}

void setupSerialPort() {
        Serial.begin(9600);

 #ifdef WAIT_FOR_SERIAL_TO_CONNECT
        while(!Serial){
                ;
        }
#endif
}

void setupTime() {
        setSyncProvider((getExternalTime)Teensy3Clock.get);

        if(Serial) {
                if(timeStatus() != timeSet) {
                        Serial.println("Unable to sync with RTC");
                } else {
                        Serial.println("RTC has set the system time");
                }
        }
}

void setup() {
#ifdef USE_SERIAL_PORT
        setupSerialPort();
#endif

        setupTime();

        setupOutputStreams();
        setupInputStreams();

        logger.writeHeader();
}

void loop() {
        if(millisElapsed(LOG_INTERVAL_LENGTH_IN_MILLIS)) {
                logger.logData();
        }
}
