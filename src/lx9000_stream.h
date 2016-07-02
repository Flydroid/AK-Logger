#pragma once

#include "input_stream.h"

class Lx9000Stream : public InputStream {
public:
        Lx9000Stream();
        ~Lx9000Stream();

        int open();
        int close();

        String getLineFormat();
        String readNextLine();

        String getName();
};
