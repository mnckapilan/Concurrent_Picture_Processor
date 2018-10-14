#include <iostream>

#include "Colour.hpp"
#include "Utils.hpp"
#include "Picture.hpp"
#include "PicLibrary.hpp"
#include "stdlib.h"

using namespace std;

// TODO: Implement the picture library command-line interpreter

int main(int argc, char **argv) {

//
//  cout << "------------------------------------------------------" << endl;
//  cout << "TODO: Implement the C++ Picture Processing Interpreter" << endl;
//  cout << "------------------------------------------------------" << endl;


    // write main IO loop that runs the command-line interpreter interactive shell

    if (argc == 1) {
        switch (argv) {
            case "liststore":
                cout << "list store" << endl;
                break;
            case "exit":
                exit(0);
            default:
                return 0;
        }
    }
    if (argc == 2) {
        switch (argv) {
            case "liststore":
                cout << "list store" << endl;
                break;
            case "exit":
                exit(0);
            default:
                return 0;
        }

        int counter;
        printf("Program Name Is: %s", argv[0]);

        if (argc == 1)
            printf("\nNo Extra Command Line Argument Passed Other Than Program Name");

        if (argc >= 2) {
            printf("\nNumber Of Arguments Passed: %d", argc);
            printf("\n----Following Are The Command Line Arguments Passed----");
            for (counter = 0; counter < argc; counter++)
                printf("\nargv[%d]: %s", counter, argv[counter]);
        }
        return 0;
        return 0;

    }


