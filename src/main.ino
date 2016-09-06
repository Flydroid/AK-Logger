//Configurations
#define LOG_INTERVAL_LENGTH_IN_MILLIS 100

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

void setTimefromUserInput() {
        if(Serial.available()) {
                Serial.println("Please enter the current timestamp (0 for skipping):");
                time_t t;
                t = Serial.parseInt();

                if(t!=0) {
                        Teensy3Clock.set(t);
                        delay(100);
                        setTime(Teensy3Clock.get());
                        Serial.println("RTC successfully updated");
                }
        }
}

void setupTime() {
        setSyncProvider((getExternalTime)Teensy3Clock.get());

        if(Serial.available()) {
                if(timeStatus() != timeSet) {
                        Serial.println("Unable to sync with RTC");
                } else {
                        Serial.println("RTC has set the system time");
                }
        }

        setTimefromUserInput();
}

void setup() {
        setupSerialPort();

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
