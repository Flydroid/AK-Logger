#include "time_stream.h"

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
        return "Timestamp;";
}

String TimeStream::readNextLine() {
        return "";
}

String TimeStream::getName() {
        return "TimeStream";
}
