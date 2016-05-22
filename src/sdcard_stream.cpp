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

        isOpened = true;
        return SD_CARD_SUCC;
}

int SDCardStream::close() {
        return SD_CARD_SUCC;
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
