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

    PicLibrary library = PicLibrary();

    for (int i = 1; argv[i] != NULL; ++i) {
        char *name;
        size_t name_start = string(argv[i]).rfind("/");

        if (name_start == string::npos) {
            name = argv[i];
        } else {
            name = &argv[i][name_start + 1];
        }

        library.loadpicture(argv[i], name);
    }

    string command, name, filepath;
    int angle;
    char plane;

    cin >> command;

    while (command != "exit") {

        if (command == "liststore") {
            library.print_picturestore();
        }

        if (command == "load") {
            cin >> filepath >> name;
            library.loadpicture(filepath, name);
        }

        if (command == "unload") {
            cin >> name;
            library.unloadpicture(name);
        }

        if (command == "save") {
            cin >> name >> filepath;
            library.savepicture(name, filepath);
        }

        if (command == "display") {
            cin >> name;
            library.display(name);
        }

        if (command == "invert") {
            cin >> name;
            library.invert(name);
        }
        if (command == "rotate") {
            cin >> angle >> name;
            library.rotate(angle, name);
        }

        if (command == "flip") {
            cin >> plane >> name;
            library.flipVH(plane, name);
        }

        if (command == "blur") {
            cin >> name;
            library.blur(name);
        }

        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cin >> command;
    }
    return 0;
}



