/*
*   CSC3022F assignment 2 - Volumetric Imaging Tool with raw pointers
*   Ryan Acton  ACTRYA001
*   Volimage functionality 
*/

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>           //for the slices vector
#include "volimage.h"

using namespace std;



// string header;
/* Constructor method to set width and height to 0 */
VolImage::VolImage()
{
    width = 0;
    height = 0;
}

/* Destructor method to clear the char array to avoid memory leak */
VolImage::~VolImage()
{
    for (int i = 0; i < slices.size(); i++)
    {
        for (int j = 0; j < height; j++)
        {
            delete[] slices[i][j];
        }
        delete[] slices[i];
    }   
    // delete slices;
}

/* Method to read in the raw files into a char array object */
bool VolImage::readImages(string baseName)
{

    int amount;

    string dir_name = "brain_mri_raws/";

    string header = baseName + ".data";

    header = dir_name + header;
	ifstream h_file(header.c_str());
    // cout << "height is: " << height << "width is: " << width << endl;
    if (h_file.is_open())
    {
        // cout << "Success" << endl;
        string line;
        // while (getline(h_file, line))
        // {
            getline(h_file, line);
            stringstream iss(line);                          //read the whole input line into the string stream

            iss >> width;
            // cout << "width is: "<< width << endl;            //read each item in the line into a var: width, head or amount
            iss >> height;
            // cout << "height is: "<< height << endl;
            iss >> amount;
            // cout << "amount is: "<< amount << endl;

        // }
            
        h_file.close();

    }
    else
    {
        cout << "not found";
    }

    unsigned char** b_arr;

    for (int i = 0; i < amount; i++)
    {
        stringstream s_stream;
        string s_ival;
        s_stream << i;

        s_ival = s_stream.str();

        string rimg_name = dir_name + baseName + s_ival + ".raw";
        // cout << rimg_name << endl;

        ifstream raw_imgs(rimg_name.c_str());

        if (raw_imgs.is_open())
        {

            b_arr = new unsigned char*[height];
         

            slices.push_back(b_arr);                  //put array into vector slices as individual slice

            for(int j = 0; j < height; j++){

                slices[i][j] = new unsigned char[width];   
            
                raw_imgs.read(reinterpret_cast<char*> (slices[i][j]), width);      
            
            }

            raw_imgs.close();
            // cout << slices.size() << endl;
        }

        
        else
        {
            cout << "file not found" << endl;
        }
        
        
    }
    

}

/* Method to write a diffmap for a given range to a text file as well as a header data file */
void VolImage::diffmap(int sliceI, int sliceJ, string output_prefix)
{
    string out_f_head = output_prefix + ".data";
    string out_f_final = output_prefix + ".raw";
    ofstream out_f_stream(out_f_head.c_str());
            // char out_arr[size];


     string s_out;


    ofstream file_out(out_f_final.c_str());

    if (file_out.is_open())
    {

        // int pos_counter;
        for(int i = 0; i < height; i++){                        //r

            for (int j = 0; j < width; j++)                     //c
            {
               char val = abs(((float)slices[sliceI][i][j]- (float)slices[sliceJ][i][j])/2);
                // pos_counter++;
                file_out.write(&val, 1);                       //refernce of var

            }
        }
            file_out.close();


    }


}

/* Method to calculate the required space for the images */
int VolImage::volImageSize(void)
{
	int imgs_size = sizeof(unsigned char*) + slices.size() * height * (sizeof(unsigned char**)+ width) ; //for the non accounted for pointers

    return imgs_size;
}

/* Method to calculate the number of images in slices */
int VolImage::vol_num_imgs(void){
		
    int num_imgs = slices.size();

	return num_imgs;
	
}

/* Method to extract the raw image at a given sliceID and make it viewable for the python viewer */
void VolImage::extract(int sliceId, string output_prefix){

    string pref_s = output_prefix + ".data";
    string s_out_name = output_prefix + ".raw";


    ofstream h_o_stream(pref_s.c_str());


    if(h_o_stream.is_open())
    {
      h_o_stream << width << " " << height << " " << 1 << endl;

      cout<< "Created header file "<< pref_s <<endl;

      h_o_stream.close();
    }
    else
    {
      cout << "Unable to open file: " << pref_s << endl;
    }

    ofstream output_stream(s_out_name.c_str());

    if (output_stream.is_open())
    {
        for (int j = 0; j < height; j++)
        {

            char* val_p = ( char*)slices[sliceId][j];   //create char pointer to point to the data in the slices vector

            output_stream.write(val_p, width);     //write the data 

        }
        
        output_stream.close();

    }
    else
    {
        cout << "Unable to open file: " << s_out_name << endl; 
    }
    

}

// /* Similar method to the normal extract method except extract from a row using rowN*/
// void VolImage::extract_from_row(int rowN, string output_prefix)
// {

//     string pref_s = output_prefix + ".data";
//     string s_out_name = output_prefix + ".raw";


//     ofstream h_o_stream(pref_s.c_str());


//     if(h_o_stream.is_open())
//     {
//       h_o_stream << width << " " << height << " " << 1 << endl;

//       cout<< "Created header file "<< pref_s <<endl;

//       h_o_stream.close();
//     }
//     else
//     {
//       cout << "Unable to open file: " << pref_s << endl;
//     }

//     ofstream output_stream(s_out_name.c_str());

//     if (output_stream.is_open())
//     {

//         cout << "width: " << width << endl;
//         cout << "slices size: " << slices.size() << endl;
//         for (int i = 0; i < (slices.size() * width); i++)
//         {

//             char* val_p = ( char*)slices[i][rowN];   //create char pointer to point to the data in the slices vector
//                                                      //this time only in one row (rowN)

//             output_stream.write(val_p, width);     //write the data 

//         }
        
//         output_stream.close();

//     }
//     else
//     {
//         cout << "Unable to open file: " << s_out_name << endl; 
//     }
    

// }

 


