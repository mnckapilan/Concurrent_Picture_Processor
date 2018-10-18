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
            Colour newColour(0, 0, 0);
            if (plane == 'V') {
                newColour = original->getpixel(x, height - 1 - y);
            } else {
                newColour = original->getpixel(width - 1 - x, y);
            }
            result.setpixel(x, y, newColour);
        }
    }
    original->setimage(result.getimage());
}

void PicLibrary::blur(string filename) {

    auto original = pictureStore[filename];

    int width = original->getwidth();
    int height = original->getheight();

    Picture result = Picture(width, height);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if((i != 0) && (j != 0) && (i != (height - 1)) && (j != (width - 1))) {
                int red = 0;
                int blue = 0;
                int green = 0;
                for(int k = (i - BLUR_RADIUS); k <= (i + BLUR_RADIUS); ++k) {
                    for(int l = (j - BLUR_RADIUS); l <= (j + BLUR_RADIUS); ++l) {
                        Colour originalColour = original->getpixel(l, k);
                        red += originalColour.getred();
                        green += originalColour.getgreen();
                        blue += originalColour.getblue();
                    }
                }
                result.setpixel(j, i, Colour (red/BLUR_STRENGTH, green/BLUR_STRENGTH, blue/BLUR_STRENGTH));
            } else {
                result.setpixel(j, i, original->getpixel(j, i));
            }
        }
    }
    original->setimage(result.getimage());
}
