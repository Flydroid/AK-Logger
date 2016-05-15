#pragma once

#include "akstream.h"

class InputStream: public AKStream {
public:
        virtual ~InputStream() {

        }

        virtual String readNextLine()=0;
};
