#include "lx9000_stream.h"

#include <TinyGPS.h>
#include <SoftwareSerial.h>

Lx9000Stream::Lx9000Stream():ss(nullptr) {

}

Lx9000Stream::~Lx9000Stream() {
        delete ss;
}

int Lx9000Stream::open() {
        if(ss) {
                return AKSTREAM_SUCC;
        }

        ss = new SoftwareSerial(RXPIN,TXPIN);
        ss->begin(4800);

        return AKSTREAM_SUCC;
}

int Lx9000Stream::close() {
        return AKSTREAM_SUCC;
}

String Lx9000Stream::getLineFormat() {
        return "Latitude;Longitude";
}

String Lx9000Stream::readNextLine() {
        if(!ss->available()) {
                return "ERROR;ERROR";
        }

        char c= ss->read();
        gps.encode(c);

        float lat,lon;
        unsigned long age;
        gps.f_get_position(&lat,&lon,&age);

        String result;
        result+=String(lat)+";"+String(lon);

        return result;
}

String Lx9000Stream::getName() {
        return "Lx9000Stream";
}
