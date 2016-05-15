//Configurations
#define LOG_INTERVAL_LENGTH_IN_MILLIS 100

#include <elapsedMillis.h>

#include "ak_logger.h"

AKLogger logger;

bool millisElapsed(int milliseconds) {
        static elapsedMillis timer;

        if(timer>LOG_INTERVAL_LENGTH_IN_MILLIS) {
                timer = 0;
                return true;
        }
        return false;
}

void setup() {
        logger.writeHeader();
}

void loop() {
        if(millisElapsed(LOG_INTERVAL_LENGTH_IN_MILLIS)) {
                logger.logData();
        }
}
