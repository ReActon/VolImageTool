#ifndef VOLIMAGE
#define VOLIMAGE

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;
class VolImage
    {
    private: 

        int width, height; // width and height of image stack
        vector<unsigned char**> slices; // data for each slice, in order

    public: 

        VolImage(); // default constructor - define in .cpp
        ~VolImage(); // destructor - define in .cpp file

        // populate the object with images in stack and
        //set member variables define in .cpp   
        bool readImages(std::string baseName);

        // compute difference map and write out; define in .cpp
        void diffmap(int sliceI, int sliceJ, std::string output_prefix);

        // extract slice sliceId and write to output - define in .cpp
        void extract(int sliceId, std::string output_prefix);

        // number of bytes uses to store image data bytes
        //and pointers (ignore vector<> container, dims etc)
        int volImageSize(void); // define in .cpp

        int vol_num_imgs(void);

        // extract an image from a row
        void extract_from_row(int rowN, std::string output_prefix);

};

#endif