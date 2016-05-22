#pragma once

class AKStream {
public:
        virtual ~AKStream() {

        }

        virtual int open()=0;
        virtual int close()=0;
};
