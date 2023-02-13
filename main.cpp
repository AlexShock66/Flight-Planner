#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include "FlightPlanner.h"
using namespace std;
int main(int argc, char** argv) {
    if(argc == 1) {
        cout << "Running Testing Environment" <<endl;
        Catch::Session().run();
    } else {
        cout << "Running non Testing environment" <<endl;
        FlightPlanner test;
        cout << argv[1] <<endl;
        cout << argv[2] <<endl;
        cout << argv[3] <<endl;
    test.setInputFile(argv[1]);
    test.setHandleFile(argv[2]);
    test.setOutputFile(argv[3]);
        test.run();

        std::cout << "Hello and wrote sample output file." << std::endl;
        return 0;
    }
//return 0;
}

