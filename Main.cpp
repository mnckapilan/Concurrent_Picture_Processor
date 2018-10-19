#include <iostream>
#include <sstream>
#include <thread>

#include "Colour.hpp"
#include "Utils.hpp"
#include "Picture.hpp"
#include "PicLibrary.hpp"
#include "stdlib.h"

using namespace std;

int main(int argc, char **argv)
{
    thread t1;
    vector<thread> threads;
    unsigned ConcurrentThreadSupport = thread::hardware_concurrency();

    PicLibrary library = PicLibrary();

    for (int i = 1; i < argc; i++)
    {
        string path = argv[i];

        string filename;
        int pos = path.find_last_of('/');
        if (pos == string::npos)
        {
            filename = path;
        }
        else
        {
            filename = path.substr(pos + 1);
        }

        library.loadpicture(path, filename);
    }

    string command, filename, path;
    int angle;
    char plane;

    cout << "prmt>";
    cin >> command;

    while (command != "exit" && cin.peek() != EOF)
    {
        if (command == "liststore")
        {
            library.joinAllThreads();
            library.print_picturestore();
        }

        if (command == "load")
        {
            cin >> path >> filename;
            if (library.alreadyInStore(filename))
            {
                cerr << " Error when loading picture at " << path << " : picture named " << filename << " already exists in store" << endl;
            }
            bool success = library.loadpicture(path, filename);
            if (success)
            {
                cout << " picture loaded successfully from " << path << endl;
            }
        }

        if (command == "unload")
        {
            cin >> filename;
            library.joinPictureThreads(filename);
            bool success = library.unloadpicture(filename);
            if (success)
            {
                cout << "unloaded " << filename << " successfully!" << endl;
            }
            else
            {
                cerr << "Error when unloading " << filename << endl;
            }
        }

        if (command == "save")
        {
            cin >> filename >> path;
            library.joinPictureThreads(filename);
            bool success = library.savepicture(filename, path);
            if (success)
            {
                cout << " saved " << filename << " at " << path << " successfully!" << endl;
            }
            else
            {
                cerr << "Error when saving picture at " << path << endl;
            }
        }

        if (command == "display")
        {
            cin >> filename;
            library.joinPictureThreads(filename);
            bool success = library.display(filename);
            if (success)
            {
                cout << "displaying" << filename << "" << endl;
            }
            else
            {
                cerr << "Error when trying to display " << filename << endl;
            }
        }

        if (command == "invert")
        {
            cin >> filename;
            if (library.alreadyInStore(filename))
            {
                auto container = library.getContainer(filename);
                container->_threads.push_back(thread(&PicLibrary::invert, &library, filename));
            }
        }

        if (command == "grayscale")
        {
            cin >> filename;
            if (library.alreadyInStore(filename))
            {
                auto container = library.getContainer(filename);
                container->_threads.push_back(thread(&PicLibrary::grayscale, &library, filename));
            }
        }
        if (command == "rotate")
        {
            cin >> angle >> filename;
            if (library.alreadyInStore(filename))
            {
                auto container = library.getContainer(filename);
                container->_threads.push_back(thread(&PicLibrary::rotate, &library, angle, filename));
            }
        }

        if (command == "flip")
        {
            cin >> plane >> filename;
            if (library.alreadyInStore(filename))
            {
                auto container = library.getContainer(filename);
                container->_threads.push_back(thread(&PicLibrary::flipVH, &library, plane, filename));
            }
        }

        if (command == "blur")
        {
            cin >> filename;
            if (library.alreadyInStore(filename))
            {
                auto container = library.getContainer(filename);
                container->_threads.push_back(thread(&PicLibrary::blur, &library, filename));
            }
        }

        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin >> command;
    }
    library.joinAllThreads();
    return 0;
}
