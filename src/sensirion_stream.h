#pragma once

#include <Arduino.h>

#define SENSIRION_DATA_PIN 22
#define SENSIRION_CLOCK_PIN 23

#include <Sensirion.h>

#include "input_stream.h"

class SensirionStream: public InputStream {
public:
        SensirionStream();
        ~SensirionStream();

        int open();
        int close();

        String getLineFormat();
        String readNextLine();

        String getName();

private:
        Sensirion sensor;

};
