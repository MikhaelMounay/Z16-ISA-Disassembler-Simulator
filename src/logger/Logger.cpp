#include "Logger.h"

#include <iostream>
#include <fstream>
using namespace std;

// Constructors
Logger::Logger() {
    stream = &_oss;
}

Logger::Logger(ostream* Stream) {
    stream = Stream;
}

// Getters
ostream* Logger::get_ostream() {
    return stream;
}

string Logger::toString() {
    return _oss.str();
}

void Logger::fatal(const string& msg) {
    if (stream != nullptr) {
        (*stream) << msg << endl;
    }

    if (stream != &_oss) {
        _oss << msg << endl;
    }

    cerr << msg << endl;

    ofstream logFile("Z16Simulator.log.txt");
    if (logFile.is_open()) {
        logFile << toString() << endl;
        logFile.close();
    }

    exit(1);
}
