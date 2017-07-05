#pragma once

#include <Arduino.h>
#include <SimpleList.h>

#include "output_stream.h"
#include "input_stream.h"

class AKLogger {
public:
        AKLogger();
        ~AKLogger();

        void addOutputStream(OutputStream* ostream);
        void addInputStream(InputStream* istream);
        void closeAndDeleteOutputStreams();
        void closeAndDeleteInputStreams();

        void writeHeader();
        void writeFooter();
        void logData();
        void log(String line);

        void start();
        void shutdown();

        bool isActive;

private:
        SimpleList<OutputStream*> ostreams;
        SimpleList<InputStream*> istreams;


        String readInputStreams();
        void logLineFormat();


};
