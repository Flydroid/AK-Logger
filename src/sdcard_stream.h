#pragma once

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

#include "output_stream.h"

#define SD_CARD_PIN 14
#define ERR_INIT_SD_CARD 1

class SDCardStream: public OutputStream {
public:
        SDCardStream(String filename, String fileextension);
        ~SDCardStream();

        int open();
        int close();

        void writeLine(String line);
        void flush();

        String getName();

private:
        String filename;
        String fileextension;
        String fullName;
        bool isOpened;
        File logFile;
};
