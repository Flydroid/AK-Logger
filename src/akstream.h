#pragma once

class AKStream {
public:
        virtual ~AKStream() {

        }

        virtual void open()=0;
        virtual void close()=0;
};
