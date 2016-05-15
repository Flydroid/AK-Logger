#pragma once

#include <string>

class OutputStream: public Stream {
public:
        virtual ~OutputStream() {

        }

        virtual void writeLine(std::string line)=0;
        virtual void flush()=0;
};
