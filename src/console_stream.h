#pragma once

#include <Arduino.h>

#include "output_stream.h"

class ConsoleStream: public OutputStream {
public:
        ConsoleStream();
        ~ConsoleStream();

        int open();
        int close();

        void writeLine(String line);
        void flush();

        String getName();
};
