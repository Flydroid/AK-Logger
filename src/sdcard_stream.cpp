#include "sdcard_stream.h"


SDCardStream::SDCardStream(String filename_, String fileextension_): filename(filename_), fileextension(fileextension_), isOpened(false) {

}

SDCardStream::~SDCardStream() {

}

int SDCardStream::open() {
        if(!sd.begin(SD_CARD_PIN, SD_SCK_MHZ(50))){
                return ERR_INIT_SD_CARD;
                Serial.println("Error SDCard");
                sd.initErrorHalt();
        }

        fullName = filename + "." + fileextension;

        if(!logFile.open(fullName.c_str(), O_CREAT | O_WRITE | O_EXCL)){
            sd.errorHalt("open file failed");
        }

        isOpened = true;
        return AKSTREAM_SUCC;
}

int SDCardStream::close() {
        logFile.close();
        Serial.println("SD Card close");
        return AKSTREAM_SUCC;
}

void SDCardStream::writeLine(String line) {
  if (!isOpened) {
    return;
  }
  logFile.println(line);
  logFile.flush();
}


void SDCardStream::flush() {
        //Nothing to do
}

String SDCardStream::getName() {
        return "SDCardStream";
}
