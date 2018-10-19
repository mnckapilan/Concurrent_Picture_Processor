#include "PicLibrary.hpp"
#include "Colour.hpp"
#include "Picture.hpp"
#include "Utils.hpp"

using namespace std;

int PicLibrary::arrayAverage(int array[], int size)
{
    int sum;
    for (int i = 0; i < size; ++i)
    {
        sum += array[i];
    }
    int avg = sum / size;
    return avg;
}

bool PicLibrary::alreadyInStore(string filename)
{
    return pictureStore.find(filename) != pictureStore.end();
}

void PicLibrary::print_picturestore()
{
    for (auto const &pair : pictureStore)
    {
        cout << pair.first << endl << std::flush;
    }
}

bool PicLibrary::loadpicture(string path, string filename)
{
    if (alreadyInStore(filename))
    {
        return false;
    }
    Picture *toBeAdded = new Picture(path);
    if (toBeAdded->getwidth() != 0)
    {
        PictureContainer *container = new PictureContainer(toBeAdded);
        pictureStore.insert({filename, container});
        cout << filename << " successfully loaded! " << endl;
    }
    else
    {
        cout << path << " exists only in your imagination! " << endl;
    }
    return true;
}

bool PicLibrary::unloadpicture(string filename)
{

    if (pictureStore.find(filename) == pictureStore.end())
    {
        return false;
    }

    pictureStore.erase(filename);
    return true;
}

bool PicLibrary::savepicture(string filename, string path)
{

    if (pictureStore.find(filename) == pictureStore.end())
    {
        return false;
    }

    auto image = pictureStore[filename]->_pic.getimage();

    Utils imgio;

    return imgio.saveimage(image, path);
}

bool PicLibrary::display(string filename)
{

    if (pictureStore.find(filename) == pictureStore.end())
    {
        return false;
    }

    auto image = pictureStore[filename]->_pic.getimage();

    Utils imgio;
    imgio.displayimage(image);

    return true;
}

void PicLibrary::invert(string filename)
{

    auto original = pictureStore[filename];
    std::lock_guard<std::mutex> lock(original->_mtx);

    int width = original->_pic.getwidth();
    int height = original->_pic.getheight();

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {

            Colour originalColour = original->_pic.getpixel(x, y);

            original->_pic.setpixel(x, y, Colour(255 - originalColour.getred(), 255 - originalColour.getgreen(), 255 - originalColour.getblue()));
        }
    }
}

void PicLibrary::grayscale(string filename)
{

    auto original = pictureStore[filename];
    std::lock_guard<std::mutex> lock(original->_mtx);

    int width = original->_pic.getwidth();
    int height = original->_pic.getheight();

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            Colour originalColour = original->_pic.getpixel(x, y);

            int average = (originalColour.getred() +
                           originalColour.getgreen() +
                           originalColour.getblue()) /
                          3;

            original->_pic.setpixel(x, y, Colour(average, average, average));
        }
    }
}

void PicLibrary::rotate(int angle, string filename)
{

    if (angle == 270)
    {
        rotate(180, filename);
        rotate(90, filename);
    }
    else if (angle == 180)
    {
        rotate(90, filename);
        rotate(90, filename);
    }
    else
    {
        auto original = pictureStore[filename];
        std::lock_guard<std::mutex> lock(original->_mtx);

        int width = original->_pic.getwidth();
        int height = original->_pic.getheight();

        Picture result(height, width);

        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
            {
                result.setpixel(height - 1 - y, x, original->_pic.getpixel(x, y));
            }
        }

        original->_pic.setimage(result.getimage());
    }
}

void PicLibrary::flipVH(char plane, string filename)
{

    auto original = pictureStore[filename];
    std::lock_guard<std::mutex> lock(original->_mtx);

    int width = original->_pic.getwidth();
    int height = original->_pic.getheight();

    Picture result = Picture(width, height);

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            Colour newColour(0, 0, 0);
            if (plane == 'V')
            {
                newColour = original->_pic.getpixel(x, height - 1 - y);
            }
            else
            {
                newColour = original->_pic.getpixel(width - 1 - x, y);
            }
            result.setpixel(x, y, newColour);
        }
    }
    original->_pic.setimage(result.getimage());
}

void PicLibrary::blur(string filename)
{

    auto original = pictureStore[filename];
    std::lock_guard<std::mutex> lock(original->_mtx);

    int width = original->_pic.getwidth();
    int height = original->_pic.getheight();

    Picture result = Picture(width, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((i != 0) && (j != 0) && (i != (height - 1)) && (j != (width - 1)))
            {
                int red = 0;
                int blue = 0;
                int green = 0;
                for (int k = (i - BLUR_RADIUS); k <= (i + BLUR_RADIUS); ++k)
                {
                    for (int l = (j - BLUR_RADIUS); l <= (j + BLUR_RADIUS); ++l)
                    {
                        Colour originalColour = original->_pic.getpixel(l, k);
                        red += originalColour.getred();
                        green += originalColour.getgreen();
                        blue += originalColour.getblue();
                    }
                }
                result.setpixel(j, i, Colour(red / BLUR_STRENGTH, green / BLUR_STRENGTH, blue / BLUR_STRENGTH));
            }
            else
            {
                result.setpixel(j, i, original->_pic.getpixel(j, i));
            }
        }
    }
    original->_pic.setimage(result.getimage());
}

PictureContainer *PicLibrary::getContainer(string filename)
{
    return pictureStore[filename];
}

void PicLibrary::joinAllThreads()
{
    for (auto i : pictureStore)
    {
        std::for_each(i.second->_threads.begin(), i.second->_threads.end(), [](thread &t) { t.join(); });
    }
    for (auto i : pictureStore)
    {
        i.second->_threads.clear();
    }
}
void PicLibrary::joinPictureThreads(string filename)
{
    if (alreadyInStore(filename))
    {
        std::for_each(pictureStore[filename]->_threads.begin(), pictureStore[filename]->_threads.end(), [](thread &t) { t.join(); });
        pictureStore[filename]->_threads.clear();
    }
}
