#pragma once

#include <string>

#include "output_stream.h"

class SDCardStream: public OutputStream {
public:
        SDCardStream();
        ~SDCardStream();

        void open();
        void close();

        void writeLine(std::string line);
        void flush();
};
