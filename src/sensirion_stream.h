#pragma once

#define SENSIRION_DATA_PIN 14
#define SENSIRION_CLOCK_PIN 15

#include <Sensirion.h>

#include "input_stream.h"

class SensirionStream: public InputStream {
public:
        SensirionStream();
        ~SensirionStream();

        void open();
        void close();

        String getLineFormat();
        String readNextLine();

private:
        Sensirion sensor;

};
