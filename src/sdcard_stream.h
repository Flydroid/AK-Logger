#pragma once

#include "output_stream.h"

class SDCardStream: public OutputStream {
public:
        SDCardStream();
        ~SDCardStream();

        void open();
        void close();

        void writeLine(String line);
        void flush();
};
