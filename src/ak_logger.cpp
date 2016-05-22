#include "ak_logger.h"

#include <Arduino.h>
#include <SimpleList.h>

#include "input_stream.h"
#include "output_stream.h"

AKLogger::AKLogger():isActive(true) {

}

AKLogger::~AKLogger() {
        shutdown();
}

void AKLogger::addOutputStream(OutputStream* ostream){
        if(ostream == nullptr)
                return;

        if(ostream->open()) {
                Serial.println("opened");
                ostreams.push_back(ostream);
        }
}

void AKLogger::addInputStream(InputStream* istream) {
        if(istream == nullptr)
                return;

        if(istream->open())
                istreams.push_back(istream);
}

void AKLogger::logLineFormat() {
        for(SimpleList<InputStream*>::iterator it = istreams.begin(); it != istreams.end(); it++) {
                log((*it)->getLineFormat());
        }
}

void AKLogger::writeHeader() {
        log("AK-Logger v1.0");
        log("Datum: TODO");
        log("");
        logLineFormat();
}

void AKLogger::writeFooter() {
        log("End of logging: DATUM_TODO");
}

String AKLogger::readInputStreams() {
        String input;
        for(SimpleList<InputStream*>::iterator it = istreams.begin(); it != istreams.end(); it++) {
                input+=(*it)->readNextLine();
                input+=";";
        }

        return input;
}

void AKLogger::logData() {
        if(!isActive)
                return;

        String data = readInputStreams();
        log(data);
}

void AKLogger::log(String line) {
        if(!isActive)
                return;

        for(SimpleList<OutputStream*>::iterator it = ostreams.begin(); it != ostreams.end(); it++) {
                (*it)->writeLine(line);
        }
}

void AKLogger::shutdown() {
        if(!isActive)
                return;

        isActive = false;

        closeAndDeleteOutputStreams();
        closeAndDeleteInputStreams();
}

void AKLogger::closeAndDeleteOutputStreams() {
        for(SimpleList<OutputStream*>::iterator it = ostreams.begin(); it != ostreams.end(); it++) {
                (*it)->flush();
                (*it)->close();
                delete &(*it);
                it = ostreams.erase(it);
        }
}

void AKLogger::closeAndDeleteInputStreams() {
        for(SimpleList<InputStream*>::iterator it = istreams.begin(); it != istreams.end(); it++) {
                (*it)->close();
                delete &(*it);
                it = istreams.erase(it);
        }
}
