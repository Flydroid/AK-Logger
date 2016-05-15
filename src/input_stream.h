#pragma once

#include <string>

#include "stream.h"

class InputStream: public Stream {
public:
        virtual ~InputStream() {

        }

        std::string readNextLine()=0;
};
