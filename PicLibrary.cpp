#include "PicLibrary.hpp"
#include "Colour.hpp"
#include "Picture.hpp"
#include "Utils.hpp"

class PicLibrary {

private:
    // TODO: define internal picture storage

public:
    // default constructor/deconstructor
    PicLibrary() {};

    ~PicLibrary() {};

    // command-line interpreter routines
    void print_picturestore();

    void loadpicture(string path, string filename);

    void unloadpicture(string filename);

    void savepicture(string filename, string path);

    void display(string filename);

    // picture transformation routines
    void invert(string filename) {
        Picture original = Utils::loadimage(filename);
        int width = original.getwidth();
        int height = original.getheight();

        Picture result = Picture(width, height);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                Colour originalColour = original.getpixel(x, y);

                result.setpixel(x, y, Colour(
                        255 - originalColour.getred(),
                        255 - originalColour.getgreen(),
                        255 - originalColour.getblue()
                                )
                );
            }
        }
    }

    void grayscale(string filename) {
        Picture original = Utils::loadimage(filename);
        int width = original.getwidth();
        int height = original.getheight();

        Picture result = Picture(width, height);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                Colour originalColour = original.getpixel(x, y);

                int average = (
                                      originalColour.getRed() +
                                      originalColour.getGreen() +
                                      originalColour.getBlue()
                              ) / 3;

                result.setpixel(x, y, Colour(average, average, average));
            }
        }
    }

    void rotate(int angle, string filename) {
        Picture original = Utils::loadimage(filename);
        int width = original.getwidth();
        int height = original.getheight();

        if (deg == 180) {

            Picture result = Utils::createimage(width, height);

            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {

                    Colour originalColour = original.getpixel(x, y);

                    Colour resultColour = Color(
                            originalColour.getred(),
                            originalColour.getgreen(),
                            originalColour.getblue()
                    );

                    result.setpixel(width - x, height - y, resultColour);
                }
            }
        } else if (deg == 90) {

            Picture result = Utils::createimage(height, width);

            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {

                }
                Colour originalColour = original.getpixel(x, y);

                Colour resultColour = Color(
                        originalColour.getred(),
                        originalColour.getgreen(),
                        originalColour.getblue()
                );

                result.setpixel(width - y, x, resultColour);
            }
        }
    }

    else {

        Picture result = Utils::creatimage(height, width);

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {

                Colour originalColour = original.getpixel(x, y);

                Colour resultColour = Color(
                        originalColour.getred(),
                        originalColour.getgreen(),
                        originalColour.getblue()
                );

                result.setpixel(y, width - x, resultColour);
            }
        }
    }

    void flipVH(char plane, string filename) {

        Picture original = Utils::loadimage(filename);
        int width = original.getwidth();
        int height = original.getheight();

        if (plane == 'H') {
            Picture result = Utils::createimage(width, height);
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    Colour originalColour = original.getpixel(x, y);

                    Colour resultColour = Colour(
                            originalColour.getred(),
                            originalColour.getgreen(),
                            originalColour.getblue()
                    );

                    result.setpixel(width - x, y, resultColour);
                }
            }
        }

        if (plane == 'V') {
            Picture result = Utils::createimage(width, height);
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    Colour originalColour = original.getpixel(x, y);

                    Colour resultColour = Colour(
                            originalColour.getred(),
                            originalColour.getgreen(),
                            originalColour.getblue()
                    );

                    result.setpixel(x, height - y, resultColour);
                }
            }
        }
    }

    void blur(string filename) {

        Picture original = Utils::loadimage(filename);
        int width = original.getwidth();
        int height = original.getheight();

        Picture result = Utils::createimage(width, height);

        for (int x = 1; x < width - 1; x++) {
            for (int y = 1; y < height - 1; y++) {

                int redList[9];
                int greenList[9];
                int blueList[9];

                int count = 0;

                for (int i = x - 1; i <= x + 1; i++) {
                    for (int j = y - 1; j <= y + 1; j++) {

                        Colour originalColour = original.getpixel(i, j);

                        redList[count] = originalColour.getred();
                        greenList[count] = originalColour.getgreen();
                        blueList[count] = originalColour.getblue();

                        count++;
                    }
                }
                int newRed = Utils::arrayAverage(redList, 9);
                int newGreen = Utils::arrayAverage(greenList, 9);
                int newBlue = Utils::arrayAverage(blueList, 9);
                Colour resultColour = Colour(newRed, newGreen, newBlue);
                result.setpixel(x, y, resultColour);
            }
        }
    }
};