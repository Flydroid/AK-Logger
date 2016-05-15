#pragma once

//#include <string>

#include "akstream.h"

class InputStream: public AKStream {
public:
        virtual ~InputStream() {

        }

        virtual char readNextLine()=0;
};
