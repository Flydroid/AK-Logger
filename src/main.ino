//Configurations
#define LOG_INTERVAL_LENGTH_IN_MILLIS 100

#define MAX_OUTPUT_STREAM 5
#define MAX_INPUT_STREAM 5

//Configuration end

#include <elapsedMillis.h>

#include "ak_logger.h"
#include "console_stream.h"
#include "sdcard_stream.h"
#include "sensirion_stream.h"

AKLogger logger;

bool millisElapsed(int milliseconds) {
        static elapsedMillis timer;

        if(timer>LOG_INTERVAL_LENGTH_IN_MILLIS) {
                timer = 0;
                return true;
        }
        return false;
}

void setupOutputStreams() {
        logger.addOutputStream(new ConsoleStream);
        logger.addOutputStream(new SDCardStream);
}

void setupInputStreams() {
        logger.addInputStream(new SensirionStream);
}

void setup() {
        setupOutputStreams();
        setupInputStreams();

        logger.writeHeader();
}

void loop() {
        if(millisElapsed(LOG_INTERVAL_LENGTH_IN_MILLIS)) {
                logger.logData();
        }
}
