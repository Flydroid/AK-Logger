#pragma once

#include <Arduino.h>

#include "akstream.h"

class OutputStream : public AKStream {
public:
        virtual ~OutputStream() {

        }

        virtual void writeLine(String line)=0;
        virtual void flush()=0;
};
