#pragma once

#include "input_stream.h"

class SensirionStream: public InputStream {
public:
        SensirionStream();
        ~SensirionStream();

        void open();
        void close();

        String readNextLine();
};
