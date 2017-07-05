#include "sdcard_stream.h"


SDCardStream::SDCardStream(String filename_, String fileextension_): filename(filename_), fileextension(fileextension_), isOpened(false) {

}

SDCardStream::~SDCardStream() {

}

int SDCardStream::open() {
        if(!SD.begin(SD_CARD_PIN)) {
                return ERR_INIT_SD_CARD;
                Serial.println("Error SDCard");
        }

        fullName = filename + "." + fileextension;
        logFile = SD.open(fullName.c_str(),FILE_WRITE);

        isOpened = true;
        return AKSTREAM_SUCC;
}

int SDCardStream::close() {
        logFile.close();
        Serial.println("SD Card close");
        return AKSTREAM_SUCC;
}

void SDCardStream::writeLine(String line) {
        if(!isOpened){
        Serial.println("Ready for Write");
                return;
        }
        if(logFile) {
              if( logFile.println(line)){
                Serial.println("write Succesful");
              }
                logFile.flush();
        }
}

void SDCardStream::flush() {
        //Nothing to do
}

String SDCardStream::getName() {
        return "SDCardStream";
}
