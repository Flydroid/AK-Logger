#pragma once

#include <string>

#include "output_stream.h"

class ConsoleStream: public OutoutStream {
public:
        ConsoleStream();
        ~ConsoleStream();

        void open();
        void close();

        void writeLine(std::string line);
        void flush();
}
