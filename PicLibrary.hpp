#ifndef PICLIB_H
#define PICLIB_H

#define BLUR_STRENGTH 9

#include <map>
#include <memory>
#include <string>

#include "Picture.hpp"
#include "Utils.hpp"

class PicLibrary {

  private:
    std::map<std::string, shared_ptr<Picture>> pictureStore;
//    Picture getPicture(string filename);

    int arrayAverage(int array[], int size);


public:
  // default constructor/deconstructor
  PicLibrary(){};
  ~PicLibrary(){};

  // command-line interpreter routines
  void print_picturestore();
  bool loadpicture(string path, string filename);
  bool unloadpicture(string filename);
  bool savepicture(string filename, string path);
  bool display(string filename);

  //added functions
  bool didPictureLoad(string filename);


  // picture transformation routines
  void invert(string filename);
  void grayscale(string filename);
  void rotate(int angle, string filename);
  void flipVH(char plane, string filename);
  void blur(string filename);
};

#endif

