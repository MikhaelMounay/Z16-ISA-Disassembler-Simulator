#include <iostream>

using namespace std;

#include "logger/Logger.h"
#include "executor/Executor.h"

string usageMsg(const string& argv0) {
    return "Usage: " + argv0 + " <input_file>";
    // return "Usage: " + argv0 +
    //        " [-v] [-d <dump_log_file>] [-o <output_file>] [--verilog <verilog_file>] <input_file>";
}

int main(int argc, char *argv[]) {
    Logger log(&cout); // TODO: change according to CLI args
    string inputFilepath;

    // Handling Command Line Arguments
    if (argc < 2) {
        log.fatal(
            "Error: please specify a valid input file\n\n" + usageMsg(argv[0]));
    }

    // TODO: CLI switches
    inputFilepath = argv[1];
    if (inputFilepath.empty()) {
        log.fatal(
            "Error: Input file name must be provided" + usageMsg(
                argv[0]));
    }

    // Reading, Processing Business Logic, and Writing to output destination
    Executor executor(&log, inputFilepath);
    executor.exec();

    return 0;
}
