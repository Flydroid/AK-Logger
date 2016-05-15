#pragma once

//#include <string>

#include "output_stream.h"

class ConsoleStream: public OutputStream {
public:
        ConsoleStream();
        ~ConsoleStream();

        void open();
        void close();

        void writeLine(char line);
        void flush();
};
