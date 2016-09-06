#include "time_stream.h"

#include <Time.h>

TimeStream::TimeStream() {

}

TimeStream::~TimeStream() {

}

int TimeStream::open() {
        return AKSTREAM_SUCC;
}

int TimeStream::close() {
        return AKSTREAM_SUCC;
}

String TimeStream::getLineFormat() {
        return "Timestamp";
}

String TimeStream::readNextLine() {
        String timeStamp("");
        timeStamp += String(hour())+":"+String(minute())+":"+String(second());

        return "";
}

String TimeStream::getName() {
        return "TimeStream";
}
