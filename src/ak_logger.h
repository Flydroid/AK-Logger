#pragma once

#include <SimpleList.h>

#include "output_stream.h"
#include "input_stream.h"

class AKLogger {
public:
        AKLogger(int maxNumberOfOutputStreams, int maxNumberOfInputStreams);
        ~AKLogger();

        void addOutputStream(OutputStream* ostream);
        void addInputStream(InputStream* istream);

        void writeHeader();
        void writeFooter();
        void logData();
        void log(String line);

private:
        SimpleList<OutputStream*> ostreams;
        SimpleList<InputStreams*> istreams;
};
