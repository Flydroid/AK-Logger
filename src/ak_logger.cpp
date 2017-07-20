#include "ak_logger.h"

#include <Arduino.h>
#include <SimpleList.h>
#include <Time.h>

#include "input_stream.h"
#include "output_stream.h"

AKLogger::AKLogger(){}

AKLogger::~AKLogger() {
        shutdown();
}

void AKLogger::start(){
        isActive = true;
}

void AKLogger::addOutputStream(OutputStream *ostream) {

  if (!isActive) {

    return;
  }

  if (ostream == nullptr) {

    return;
  }

  int err = ostream->open();
  if (err == AKSTREAM_SUCC) {
      Serial.println("Successully opened '" + ostream->getName() + "'");
    ostreams.push_back(ostream);
  } else {
      Serial.println("Failed to open '" + ostream->getName() + "': " + String(err));
  }
}

void AKLogger::addInputStream(InputStream* istream) {
        if(!isActive)
                return;

        if(istream == nullptr)
                return;

        int err = istream->open();
        if(err == AKSTREAM_SUCC) {
                        Serial.println("Successully opened '"+istream->getName()+"'");
                istreams.push_back(istream);
        } else {
                        Serial.println("Failed to open '"+istream->getName()+"': "+String(err));
        }

}

void AKLogger::logLineFormat() {
        String lineformat="";
        for(SimpleList<InputStream*>::iterator it = istreams.begin(); it != istreams.end(); it++) {
                lineformat+=(*it)->getLineFormat()+";";
        }
        log(lineformat);
}

void AKLogger::writeHeader() {
        String datum(year());
        datum += "-"+String(month())+"-"+String(day());

        log("AK-Logger v1.0");
        log("Datum: "+datum);
        log("");
        logLineFormat();
}

void AKLogger::writeFooter() {
        log("End of logging");
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
        writeFooter();
        isActive = false;

        closeAndDeleteOutputStreams();
        closeAndDeleteInputStreams();
}

void AKLogger::closeAndDeleteOutputStreams() {
        for(SimpleList<OutputStream*>::iterator it = ostreams.begin(); it != ostreams.end(); it++) {
                (*it)->flush();
                (*it)->close();
                Serial.println("Successully closed '"+ (*it)->getName()+"'");
                delete &(*it);
        }
        ostreams.clear();
}

void AKLogger::closeAndDeleteInputStreams() {
        for(SimpleList<InputStream*>::iterator it = istreams.begin(); it != istreams.end();it++ ) {
                (*it)->close();
                Serial.println("Successully closed '"+ (*it)->getName()+"'");
                delete &(*it);


        }
        istreams.clear();
}
