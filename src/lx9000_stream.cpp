#include "lx9000_stream.h"

Lx9000Stream::Lx9000Stream() {

}

Lx9000Stream::~Lx9000Stream() {

}

int Lx9000Stream::open() {
        return AKSTREAM_SUCC;
}

int Lx9000Stream::close() {
        return AKSTREAM_SUCC;
}

String Lx9000Stream::getLineFormat() {
        return "";
}

String Lx9000Stream::readNextLine() {
        return "";
}

String Lx9000Stream::getName() {
        return "Lx9000Stream";
}
