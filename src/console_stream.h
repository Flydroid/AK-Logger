#pragma once

#include "output_stream.h"

class ConsoleStream: public OutputStream {
public:
        ConsoleStream();
        ~ConsoleStream();

        void open();
        void close();

        void writeLine(String line);
        void flush();
};
