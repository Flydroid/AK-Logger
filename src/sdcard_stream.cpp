#include "sdcard_stream.h"

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

SDCardStream::SDCardStream(String filename_, String fileextension_): filename(filename_), fileextension(fileextension_), isOpened(false) {

}

SDCardStream::~SDCardStream() {

}

int SDCardStream::open() {
        if(!SD.begin(SD_CARD_PIN)) {
                return ERR_INIT_SD_CARD;
        }

        fullName = filename + "." + fileextension;
        if(SD.exists(fullName.c_str())) {
                for(int i=1; SD.exists(fullName.c_str());i++) {
                        fullName = filename + "_" + String(i) + "." + fileextension;
                }
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

        File logFile = SD.open(fullName.c_str(),FILE_WRITE);

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
