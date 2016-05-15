#pragma once

#include <string>

#include "output_stream.h"
#include "input_stream.h"

class AKLogger {
public:
        AKLogger();

        void addOutputStream(OutputStream* ostream);
        void addInputStream(InputStream* istream);

        void writeHeader();
        void writeFooter();
        void logData();
        void log(std::string line);
};
