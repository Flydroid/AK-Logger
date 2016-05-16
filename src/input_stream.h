#pragma once

#include <Arduino.h>

#include "akstream.h"

class InputStream: public AKStream {
public:
        virtual ~InputStream() {

        }

        virtual String getLineFormat()=0;
        virtual String readNextLine()=0;
};
