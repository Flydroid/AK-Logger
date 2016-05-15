#pragma once

//#include <string>

#include "akstream.h"

class OutputStream : public AKStream {
public:
        virtual ~OutputStream() {

        }

        virtual void writeLine(char line)=0;
        virtual void flush()=0;
};
