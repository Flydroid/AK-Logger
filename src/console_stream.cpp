#include "console_stream.h"

#include <Arduino.h>

ConsoleStream::ConsoleStream() {

}

ConsoleStream::~ConsoleStream() {
        flush();
}

int ConsoleStream::open() {
        //Expects the Serial output already opened with Serial.begin
        return AKSTREAM_SUCC;
}

int ConsoleStream::close() {
        //Serial.end should not be called since Serial might
        //still be used somewhere else.
        //We didnt open it so we dont close it.
        return AKSTREAM_SUCC;
}

void ConsoleStream::writeLine(String line) {
        if(Serial.available()) {
                Serial.println(line);
        }
}

void ConsoleStream::flush() {
        Serial.flush();
}

String ConsoleStream::getName() {
        return "ConsoleStream";
}
