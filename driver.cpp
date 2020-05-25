/*
*   CSC3022F assignment 2 - Volumetric Imaging Tool with raw pointers
*   Ryan Acton  ACTRYA001
*   Driver program
*/


#include <sstream>
#include <iostream>
#include "volimage.h"
using namespace std;



//Command line input: volimage <imageBase> [-d i j output_file_name] [-x i output_file_name]
int main(int argc, char* argv[])
{
    string img_base;
    string output_f_name;
    string init_flag;
    string f_outp;

    int num_rbytes;
    int num_imgs;
    int num_slice;
    int i_val;
    int j_val;

    string output_msg;

    VolImage vol_img;
	string header = string(argv[1]);
    
	vol_img.readImages(header);
    

    //testing loop to print out all argc values
    // for (int i = 0; i < argc; i++)
    // {
    //     string s = argv[i];
    //     cout << "argv[" << i << "] = " << s << endl;
    // }

    // base case method with no flags, to build internal representation
    if (argc == 2)
    {

        cout << "Number of images: " << vol_img.vol_num_imgs() << endl; 
        cout << "Number of bytes required: " << vol_img.volImageSize() << endl;
        output_msg = "Built internal representation, now exiting.";
        cout << output_msg << endl;
        return 0;

    }

    init_flag = (string)argv[2];

    // correct number of inputs for argc. 
    if(argc == 5) 
    {
        if (init_flag == "-x")
        {
           istringstream iss(argv[3]);
		    iss >> num_slice;
		    f_outp = string(argv[4]); //read file name (argv in position 4) into f_outp
            vol_img.extract(num_slice, f_outp);
            // cout << num_slice << " " << f_outp << endl;
            cout << "You selected: extract and write the slice with number i and write this out to file " << f_outp << "." << endl;
            
        }
        else if (init_flag == "-g") //bonus 5% case
        {
            istringstream iss(argv[3]);
		    iss >> num_slice;
		    f_outp = string(argv[4]);
            // vol_img.extract_from_row(num_slice, f_outp);
            cout << "You have selected: extract the row at the number " << num_slice << " and write this out to file " << f_outp << "." << endl;
        }
        
        else
        {
            output_msg = "Wrong flag used for input of 5 args.";
            cout << output_msg << endl;
        }
        

    }

    else if (argc == 6)
    {

        if (init_flag == "-d")
        {
            istringstream issi(argv[3]); 
            issi >> i_val; //read i value from istringstream into i_val

            istringstream issj(argv[4]);
            issj >> j_val; //read j value from istringstream into j_val
        
            f_outp = string(argv[5]); //read file name (argv in position 4) into f_outp

            vol_img.diffmap(i_val, j_val ,f_outp); //call diffmap in volimage.cpp


            cout << "You selected: compute a difference map between images i and j, and write this out to file." << endl;
        }
        else
        {
            output_msg = "A flag of '-d' is necessary for an argument line of 6 args.";
            cout << output_msg << endl;
        }
        
    }


    else if (argc > 6)
    {
        output_msg = "Too many inputted operators and/or flags.";
        cout << output_msg << endl;
    }


    
    return 0;

}