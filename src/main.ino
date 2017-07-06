//Configurations
#define LOG_INTERVAL_LENGTH_IN_MILLIS 1000
#define GPS_CHECK_INTERVAL_IN_MILLIS 10000

#define LED_PIN 7

#define USE_SERIAL_PORT
//#define WAIT_FOR_SERIAL_TO_CONNECT

//Configuration end

#include <Arduino.h>
#include <elapsedMillis.h>
#include <Time.h>
#include <TinyGPS++.h>
#include <String>

#include "ak_logger.h"
#include "console_stream.h"
#include "sdcard_stream.h"
#include "sensirion_stream.h"
#include "time_stream.h"

AKLogger logger;
TinyGPSPlus gps;

elapsedMillis log_timer;
elapsedMillis gps_timer;
/*
bool millisElapsed(int milliseconds) {
        static elapsedMillis timer;

        if(timer>milliseconds) {
                timer = 0;
                return true;
        }
        return false;
}
*/

/*
void setupOutputStreams() {
        logger.addOutputStream(new ConsoleStream);
        logger.addOutputStream(new SDCardStream("flug","log"));
}

void setupInputStreams() {
        logger.addInputStream(new TimeStream);
        logger.addInputStream(new SensirionStream);
}
*/

void setupSerialPort() {
        Serial.begin(115200);

 #ifdef WAIT_FOR_SERIAL_TO_CONNECT
        while(!Serial){
                ;
        }
#endif
}

void setupGPS() {
      Serial2.begin(38400);
      Serial.println("Serial2 Online");

}

void updateTimeFromGPS() {
  while (timeStatus() != timeSet) {
    Serial.println("waiting for GPS");
   digitalWrite(LED_PIN, HIGH);
    while (Serial2.available()) {
      if (gps.encode(Serial2.read())) {
        Serial.println("GPS encoded");
      //  Serial.println(gps.time.age());
      //  Serial.println(gps.time.isValid());
      //  Serial.println(gps.date.isValid());
        if (gps.time.isValid() && gps.date.isValid() && gps.time.age() < 1000) {
          // gps.time.hour() for correct Germany timezone
          setTime(gps.time.hour() + 2, gps.time.minute(), gps.time.second(), gps.date.day(), gps.date.month(), gps.date.year());
          if (timeStatus() != timeSet) {
            Serial.println("Unable to sync with GPS Time");
          } else {
            Serial.println("GPS has set the system time");
          }
        }
      }
    }
  }
  digitalWrite(LED_PIN, LOW);
}

void setup() {

#ifdef USE_SERIAL_PORT
        setupSerialPort();
#endif
        pinMode(LED_PIN,OUTPUT);

        setupGPS();
        Serial.println("GPS setup done");
        updateTimeFromGPS();
    //    setupOutputStreams();
    //    setupInputStreams();

      //  logger.writeHeader();
        pinMode(0, INPUT_PULLDOWN);

}

void loop() {


  bool velocity = 0;
  if (gps_timer >= GPS_CHECK_INTERVAL_IN_MILLIS) {
    Serial.println("Check GPS");
    while (Serial2.available()){

      velocity = digitalRead(0);
      if (gps.encode(Serial2.read())) {
        if (gps.location.isValid()) {
          //velocity = gps.speed.kmph();
        }
      }
    }

    if (velocity ==1  && !logger.isActive) {
      Serial.println("Logger is on");
      String filename = String("AK-Logger_" + String(hour()) + "-" + String(minute())+ "-" + String(second()) + "_" + String(day())  +"-" + String(month())+ "-" + String(year()));
      Serial.println(filename);
      logger.isActive = true;
      logger.addOutputStream(new SDCardStream(filename, "log"));
      logger.addOutputStream(new ConsoleStream);
      logger.addInputStream(new TimeStream);
      logger.addInputStream(new SensirionStream);
    }
    if (velocity ==0 && logger.isActive) {
      Serial.println("Logger is off");
      logger.shutdown();
    }
    gps_timer =0;
  }
  if (log_timer >= LOG_INTERVAL_LENGTH_IN_MILLIS && logger.isActive) {
    logger.logData();
    log_timer = 0;
  }

}
