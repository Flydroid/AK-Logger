#include "console_stream.h"

ConsoleStream::ConsoleStream() {

}

ConsoleStream::~ConsoleStream() {
        flush();
}

void ConsoleStream::open() {
        //Expects the Serial output already opened with Serial.begin
}

void ConsoleStream::close() {
        //Serial.end should not be called since Serial might
        //still be used somewhere else.
        //We didnt open it so we dont close it.
}

void ConsoleStream::writeLine(String line) {
        Serial.println(line);
}

void ConsoleStream::flush() {
        Serial.flush();
}
