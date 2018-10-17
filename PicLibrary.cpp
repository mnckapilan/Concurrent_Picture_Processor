#include "PicLibrary.hpp"
#include "Colour.hpp"
#include "Picture.hpp"
#include "Utils.hpp"

using namespace std;

int PicLibrary::arrayAverage(int array[], int size) {
    int sum;
    for (int i = 0; i < size; ++i) {
        sum += array[i];
    }
    int avg = sum / size;
    return avg;
}

bool PicLibrary::didPictureLoad(string filename) {
    return pictureStore.find(filename) != pictureStore.end();
}


void PicLibrary::print_picturestore() {

    for (auto const &pair : pictureStore) {
        cout << pair.first << endl;
    }
}

bool PicLibrary::loadpicture(string path, string filename) {

    auto picture = make_shared<Picture>(Picture(path));

    if (pictureStore.find(filename) != pictureStore.end()) {
        return false;
    }

    pictureStore[filename] = picture;
    return true;
}

bool PicLibrary::unloadpicture(string filename) {

    if (pictureStore.find(filename) == pictureStore.end()) {
        return false;
    }

    pictureStore.erase(filename);
    return true;
}

bool PicLibrary::savepicture(string filename, string path) {

    if (pictureStore.find(filename) == pictureStore.end()) {
        return false;
    }

    auto image = pictureStore[filename]->getimage();

    Utils imgio;

    return imgio.saveimage(image, path);
}

bool PicLibrary::display(string filename) {

    if (pictureStore.find(filename) == pictureStore.end()) {
        return false;
    }

    auto image = pictureStore[filename]->getimage();

    Utils imgio;
    imgio.displayimage(image);

    return true;
}

void PicLibrary::invert(string filename) {

    auto original = pictureStore[filename];

    int width = original->getwidth();
    int height = original->getheight();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            Colour originalColour = original->getpixel(x, y);

            original->setpixel(x, y, Colour(
                    255 - originalColour.getred(),
                    255 - originalColour.getgreen(),
                    255 - originalColour.getblue()
            ));
        }
    }
}

void PicLibrary::grayscale(string filename) {

    auto original = pictureStore[filename];

    int width = original->getwidth();
    int height = original->getheight();

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Colour originalColour = original->getpixel(x, y);

            int average = (
                                  originalColour.getred() +
                                  originalColour.getgreen() +
                                  originalColour.getblue()
                          ) / 3;

            original->setpixel(x, y, Colour(average, average, average));
        }
    }
}

void PicLibrary::rotate(int angle, string filename) {

    if (angle == 270) {
        rotate(180, filename);
        rotate(90, filename);
    } else if (angle == 180) {
        rotate(90, filename);
        rotate(90, filename);
    } else {
        auto original = pictureStore[filename];

        int width = original->getwidth();
        int height = original->getheight();

        Picture result(height, width);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                result.setpixel(height - 1 - y, x, original->getpixel(x, y));
            }
        }

        original->setimage(result.getimage());
    }
}

void PicLibrary::flipVH(char plane, string filename) {

    auto original = pictureStore[filename];

    int width = original->getwidth();
    int height = original->getheight();

    Picture result = Picture(width, height);

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            if (plane != 'H' && plane != 'V'){
                cout << "invalid input" << endl;
                return;
            }
            if (plane == 'H') {
                result.setpixel(width - x, y, original->getpixel(x, y));
            }
            if (plane == 'V'){
                result.setpixel(x, height - y, original->getpixel(x, y));
            }
        }
    }
    original->setimage(result.getimage());
}

void PicLibrary::blur(string filename) {

    auto original = pictureStore[filename];

    int width = original->getwidth();
    int height = original->getheight();

    Picture result = *original;

    for (int x = 1; x < width - 1; x++) {
        for (int y = 1; y < height - 1; y++) {

            int redList[BLUR_STRENGTH];
            int greenList[BLUR_STRENGTH];
            int blueList[BLUR_STRENGTH];

            int count = 0;

            for (int i = x - 1; i <= x + 1; i++) {
                for (int j = y - 1; j <= y + 1; j++) {

                    Colour originalColour = original->getpixel(i, j);

                    redList[count] = originalColour.getred();
                    greenList[count] = originalColour.getgreen();
                    blueList[count] = originalColour.getblue();

                    count++;
                }
            }
            int newRed = arrayAverage(redList, BLUR_STRENGTH);
            int newGreen = arrayAverage(greenList, BLUR_STRENGTH);
            int newBlue = arrayAverage(blueList, BLUR_STRENGTH);
            Colour resultColour = Colour(newRed, newGreen, newBlue);
            result.setpixel(x, y, resultColour);
        }
    }
    original->setimage(result.getimage());
}
