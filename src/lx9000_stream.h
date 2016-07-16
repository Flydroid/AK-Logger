#pragma once

#include "input_stream.h"

#include <TinyGPS.h>
#include <SoftwareSerial.h>

#define RXPIN 3
#define TXPIN 2

class Lx9000Stream : public InputStream {
public:
        Lx9000Stream();
        ~Lx9000Stream();

        int open();
        int close();

        String getLineFormat();
        String readNextLine();

        String getName();

private:
        TinyGPS gps;
        SoftwareSerial* ss;
};
