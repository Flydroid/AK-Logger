#pragma once

#include <Arduino.h>

#define AKSTREAM_SUCC 0

class AKStream {
public:
        virtual ~AKStream() {

        }

        virtual String getName()=0;

        virtual int open()=0;
        virtual int close()=0;
};
