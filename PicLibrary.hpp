#ifndef PICLIB_H
#define PICLIB_H

#define BLUR_STRENGTH 9
#define BLUR_RADIUS 1

#include <unordered_map>
#include <memory>
#include <string>
#include <atomic>
#include <mutex>

#include "Picture.hpp"
#include "Utils.hpp"

/*   Thread-safe synchronization strategy

 *  I initially added a mutex to the Picture class, but since mutexes are non
 *  -movable and non-copyable and that will lead to errors during lookups and insertions.
 *  
 *  After some consulting of my friends, I decided to create "Picture Containers" which 
 *  contain instances of the picture, a corresponding mutex and a vector of threads. The threads are those
 *  that are trying to modify the particular Picture in its container.
 * 
 *  I had to change the previous map of Pictures (which I used for the sequential implementation) 
 *  into a map of containers to make this work, as well as create threads when commands that 
 *  modify the images are invoked 
 */

class PicLibrary
{

private:
  std::map<std::string, PictureContainer *> pictureStore;
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
  PictureContainer *getContainer(string filename);
  bool alreadyInStore(string filename);
  void joinAllThreads();
  void joinPictureThreads(string filename);

  // picture transformation routines
  void invert(string filename);
  void grayscale(string filename);
  void rotate(int angle, string filename);
  void flipVH(char plane, string filename);
  void blur(string filename);
};

#endif
