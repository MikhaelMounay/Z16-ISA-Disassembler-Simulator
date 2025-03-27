#ifndef LOGGER_H
#define LOGGER_H

#include <sstream>
using namespace std;

class Logger {
private:
    ostringstream _oss;
    ostream* stream;

public:
    // Constructors
    Logger();
    explicit Logger(ostream* OS);

    // Getters
    ostream* get_ostream();
    string toString();

    // Methods
    // Prints the given msg, saves the log, and exits the program directly
    void fatal(const string& msg);

    // Operator Overloading
    template <typename T>
    Logger& operator<<(const T& a) {
        if (stream != nullptr) {
            (*stream) << a;
        }

        if (stream != &_oss) {
            _oss << a;
        }

        return *this;
    }

    Logger& operator<<(ostream& (*manip)(ostream&)) {
        if (stream != nullptr) {
            (*stream) << manip;
        }

        if (stream != &_oss) {
            _oss << manip;
        }

        return *this;
    }
};

#endif //LOGGER_H
