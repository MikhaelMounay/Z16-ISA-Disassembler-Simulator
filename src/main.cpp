#include <iostream>
#include <fstream>
using namespace std;

#include "logger/Logger.h"
#include "executor/Executor.h"

string usageMsg(const string& argv0) {
    return "Usage: " + argv0 +
           " [-v] [-o <output_file>] <input_file>";
}

int main(int argc, char* argv[]) {
    Logger log;
    bool verbose = false;
    string outputFilepath;
    string inputFilepath;

    // Handling Command Line Arguments
    if (argc < 2) {
        log.fatal(
            "Error: please specify a valid input file\n\n" + usageMsg(argv[0]));
    }

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "-v") {
            verbose = true;
        } else if (string(argv[i]) == "-o") {
            if (argv[i + 1] == nullptr || string(argv[i + 1]).
                starts_with("-")) {
                log.fatal(
                    "Error: Output file path must be provided after -o\n\n" +
                    usageMsg(argv[0]));
            }

            outputFilepath = string(argv[i + 1]);
            i++;
        } else if (string(argv[i]).starts_with("-")) {
            log.fatal(
                "Error: Unknown flag: " + string(argv[i]) + " " + usageMsg(
                    argv[0]));
        } else {
            inputFilepath = string(argv[i]);
            if (inputFilepath.empty()) {
                log.fatal(
                    "Error: Input file name must be provided" + usageMsg(
                        argv[0]));
            }
        }
    }

    if (verbose) {
        log = Logger(&cout);
    }

    // Reading, Processing Business Logic, and Writing to output destination
    Executor executor(&log, inputFilepath);
    executor.exec();

    string output = executor.getOutput()->toString();
    cout << output << endl;

    if (!outputFilepath.empty()) {
        ofstream outputFile(outputFilepath);
        if (!outputFile.is_open()) {
            log.fatal(
                "Error: Unable to open output file " + outputFilepath + "\n");
        }

        outputFile << log.toString();
        outputFile << output;

        outputFile.close();
    }

    return 0;
}
