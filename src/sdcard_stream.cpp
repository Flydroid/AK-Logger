#include "sdcard_stream.h"

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

SDCardStream::SDCardStream(String filename_): filename(filename_), isOpened(false) {

}

SDCardStream::~SDCardStream() {

}

int SDCardStream::open() {
        if(!SD.begin(SD_CARD_PIN)) {
                return ERR_INIT_SD_CARD;
        }

        if(SD.exists(filename.c_str())) {
                String newfilename=filename;
                for(int i=1; SD.exists(newfilename.c_str());i++) {
                        newfilename = filename + "_" +String(i);
                }

                filename = newfilename;
        }

        isOpened = true;
        return AKSTREAM_SUCC;
}

int SDCardStream::close() {
        return AKSTREAM_SUCC;
}

void SDCardStream::writeLine(String line) {
        if(!isOpened)
                return;

        File logFile = SD.open(filename.c_str(),FILE_WRITE);

        if(logFile) {
                logFile.println(line);
                logFile.close();
        }
}

void SDCardStream::flush() {
        //Nothing to do
}

String SDCardStream::getName() {
        return "SDCardStream";
}
