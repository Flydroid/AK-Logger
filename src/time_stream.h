#pragma once

#include "input_stream.h"

class TimeStream: public InputStream {
public:
        TimeStream();
        ~TimeStream();

        int open();
        int close();

        String getLineFormat();
        String readNextLine();

        String getName();
};
