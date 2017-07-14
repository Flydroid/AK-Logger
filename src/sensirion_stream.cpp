#include "sensirion_stream.h"

#include <Arduino.h>
#include <Sensirion.h>

SensirionStream::SensirionStream(): sensor(SENSIRION_DATA_PIN,SENSIRION_CLOCK_PIN) {

}

SensirionStream::~SensirionStream() {

}

int SensirionStream::open() {
        sensor.reset();

        return AKSTREAM_SUCC;
}

int SensirionStream::close() {
        sensor.reset();
        return AKSTREAM_SUCC;
}

String SensirionStream::getLineFormat() {
        return "Temperature;Humidity";//;Dewpoint";
}

String SensirionStream::readNextLine() {
        static float temperature=0.0;
        static float humidity=0.0;
        static float dewpoint=0.0;

        uint8_t err_code = sensor.measure(&temperature, &humidity, &dewpoint);

        if(err_code == 1 || err_code == 2) {
                return "ERROR;ERROR";//;ERROR";
        }

        String result(temperature);
        result+=";"+String(humidity);//+";"+String(dewpoint);

        return result;
}

String SensirionStream::getName() {
        return "SensirionStream";
}
