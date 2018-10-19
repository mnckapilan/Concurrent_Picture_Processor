#ifndef COLOUR_H
#define COLOUR_H

// The Colour class is used to represent a pixel of an image in RGB format
class Colour
{

public:
  // class constructor (sets all attributes)
  Colour(int red, int green, int blue);

  // class attribute getters
  int getred();
  int getgreen();
  int getblue();

  // class attribute setters
  void setred(int value);
  void setgreen(int value);
  void setblue(int value);

private:
  // class attributes for RGB pixel
  int red;
  int green;
  int blue;
};

#endif
