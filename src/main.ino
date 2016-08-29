//Configurations
#define LOG_INTERVAL_LENGTH_IN_MILLIS 100

#define WAIT_FOR_SERIAL_TO_CONNECT

//Configuration end

#include <Arduino.h>
#include <elapsedMillis.h>

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

}

void setup() {
        setupSerialPort();

        setupOutputStreams();
        setupInputStreams();

        setupTime();

        logger.writeHeader();
}

void loop() {
        if(millisElapsed(LOG_INTERVAL_LENGTH_IN_MILLIS)) {
                logger.logData();
        }
}
