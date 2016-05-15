#include <Arduino.h>
#include <Time.h>
#include <SdFat.h>
#include <elapsedMillis.h>
#include <Sensirion.h>

#include "config.h"

SdFat sdFat;
SdFile logFile;
char filename[100];
ArduinoOutStream logFileStream(logFile);

const int interval = 10;
elapsedMillis timer;

Sensirion sh(14,15);
uint8_t sensirionLastResult;
float temp;
float humidity;
float dew;

uint8_t readSensirionSensor() {
    sensirionLastResult = sh.measure(&temp, &humidity, &dew);
} 

void logData() {
    if(!logFile.open(filename, O_RDWR | O_AT_END)) {
        return;
    }
    
    //Log sensirion data
    if(sensirionLastResult != 1 && sensirionLastResult != 2) {
        logFileStream << temp << ";" << humidity << ";" << dew <<";";
    } else {
        logFileStream << "Sensirion Error;";
    }

    logFileStream<<"\n";

    logFile.close();
}

void setup() {
    //Start setting up the logfile

    //Initialize filesystem
    sdFat.begin(SS_PIN, SPI_HALF_SPEED);
    
    //Generate filename of format AKLogger yy-mm-dd hh:mm:ss.csv
    snprintf(filename,100,"AKLogger %i-%i-%i %i:%i:%i.csv",year(),month(),day(),hour(),minute(),second());
    for(int i=0;sdFat.exists(filename);i++) {
        snprintf(filename,100,"AKLogger %i-%i-%i %i:%i:%i (%i).csv",year(),month(),day(),hour(),minute(),second(),i);
    }
    
    //Open logfile
    if(!logFile.open(filename, O_RDWR | O_CREAT | O_AT_END)) {
        //Catch Error
    }
    
    //Write meta information
    logFileStream<<"AK-Logger v0.1 \n";
    logFileStream<<"Datum: "<<day()<<"."<<month()<<"."<<year()<<" - "<<hour()<<":"<<minute()<<":"<<second()<<"\n\n";

    logFile.close();
    //End setting up logfile
        
}

void loop() {
    if(timer>interval) {
        readSensirionSensor();

        logData();

        timer=0;
    }
}
