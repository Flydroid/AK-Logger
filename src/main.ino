//Configurations
#define LOG_INTERVAL_LENGTH_IN_MILLIS 1000

//#define USE_SERIAL_PORT
//#define WAIT_FOR_SERIAL_TO_CONNECT
//#define UPDATE_TIME_FROM_USER

//Configuration end

#include <Arduino.h>
#include <elapsedMillis.h>
#include <Time.h>
#include <TinyGPS++.h>

#include "ak_logger.h"
#include "console_stream.h"
#include "sdcard_stream.h"
#include "sensirion_stream.h"
#include "time_stream.h"

AKLogger logger;
TinyGPSPlus gps;


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
        logger.addOutputStream(new SDCardStream("flug","log"));
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

void setupGPS() {
      Serial2.begin(115200);
}

void  updateTimeFromGPS() {

          while (Serial2.available()) {
              gps.encode(Serial2.read());
              if(gps.time.isValid() && gps.time.age()){
                    setTime(gps.time.hour(),gps.time.minute(),gps.time.second(),gps.date.day(),gps.date.month(),gps.date.year()-1970);
                  if(timeStatus() != timeSet) {
                          Serial.println("Unable to sync with GPS Time");
                  } else {
                          Serial.println("GPS has set the system time");
                  }


            }
        }

}



void setup() {
#ifdef USE_SERIAL_PORT
        setupSerialPort();
#endif
        setupGPS();
        updateTimeFromGPS();

        setupOutputStreams();
        setupInputStreams();

        logger.writeHeader();
}

void loop() {
        if(millisElapsed(LOG_INTERVAL_LENGTH_IN_MILLIS)) {
                logger.logData();
        }
}
