#pragma once

#include <Arduino.h>

#include "output_stream.h"

#define CONSOLE_SUCC 0

class ConsoleStream: public OutputStream {
public:
        ConsoleStream();
        ~ConsoleStream();

        int open();
        int close();

        void writeLine(String line);
        void flush();
};
