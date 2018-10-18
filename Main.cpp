#include <iostream>
#include <sstream>

#include "Colour.hpp"
#include "Utils.hpp"
#include "Picture.hpp"
#include "PicLibrary.hpp"
#include "stdlib.h"

using namespace std;

// TODO: Implement the picture library command-line interpreter

int main(int argc, char **argv) {

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

    string command, filename, path;
    int angle;
    char plane;

    cout << "prmt>";
    cin >> command;

    while (command != "exit" && cin.peek() != EOF) {
        if (command == "liststore") {
            library.print_picturestore();
        }

        if (command == "load") {
            cin >> path >> filename;
            // if(library.didPictureLoad(filename)){
            //     cerr << "Error when loading picture at " << path << ": picture named " << filename << " already exists in store" << endl;
            // }
            library.loadpicture(path, filename);
        }

        if (command == "unload") {
            cin >> filename;
            bool success = library.unloadpicture(filename);
            if (success){
                cout << "unloaded" << filename << "successfully!" << endl;
            }
            else {
                cerr << "Error when unloading " << filename << endl;
            }
        }

        if (command == "save") {
            cin >> filename >> path;
            bool success = library.savepicture(filename, path);
            if (success){
                cout << "saved" << filename << "at" << path << "successfully!" << endl;
            }
            else {
                cerr << "Error when saving picture at " << path << endl;
            }
        }

        if (command == "display") {
            cin >> filename;
            bool success = library.display(filename);
            if (success){
                cout << "displaying" << filename << "" << endl;
            }
            else {
                cerr << "Error when trying to display " << filename << endl;
            }
        }

        if (command == "invert") {
            cin >> filename;
            library.invert(filename);
        }

        if (command == "grayscale"){
            cin >> filename;
            library.grayscale(filename);
        }
        if (command == "rotate") {
            cin >> angle >> filename;
            library.rotate(angle, filename);
        }

        if (command == "flip") {
            cin >> plane >> filename;
            library.flipVH(plane, filename);
        }

        if (command == "blur") {
            cin >> filename;
            library.blur(filename);
        }

        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "prmt>";
        cin >> command;
    }
    return 0;
}



