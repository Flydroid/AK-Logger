#pragma once

#include <SimpleList.h>

#include "output_stream.h"
#include "input_stream.h"

class AKLogger {
public:
        AKLogger();
        ~AKLogger();

        void addOutputStream(OutputStream* ostream);
        void addInputStream(InputStream* istream);

        void writeHeader();
        void writeFooter();
        void logData();
        void log(String line);

        void shutdown();

private:
        SimpleList<OutputStream*> ostreams;
        SimpleList<InputStream*> istreams;

        bool isActive;

        String readInputStreams();
        void logLineFormat();
};
