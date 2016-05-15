#pragma once

class Stream {
public:
        virtual ~Stream() {

        }

        virtual void open()=0;
        virtual void close()=0;
};
