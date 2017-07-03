#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include "Eigen/Dense"

using namespace std;

void check_argument(int argc,char* argv[])
{
    string usage_instructions = "Usage instruction:";
    usage_instructions += argv[0];
    usage_instructions += "path/to/input.txt output.txt";

    bool args_valid = false;
    //make sure that the user has provided correct input and output files
    if(argc == 1)
    {
        cerr << usage_instructions << endl;
    }
    else if(argc == 2)
    {
        cerr << "Please input an output file.\n" << usage_instructions << endl;
    }
    else if(argc == 3)
    {
        args_valid == true;
    }
    else if(argc >  3)
    {
        cerr << "Too mang arguments.\n" << usage_instructions << endl;
    }

    if(!args_valid){
        exit(EXIT_FAILURE);
    }

}

void check_files(ifstream& in_file,string& in_name,ofstream& out_file,string& out_name){
    if(!in_file.is_open()){
        cerr << "Can't open input file: " << in_name << endl;
        exit(EXIT_FAILURE);
    }

    if(!out_file.is_open()){
        cerr << "Cannot open output file: " << out_name << endl;
        exit(EXIT_FAILURE);
    }

}


int main(int argc,char* argv[]) {
//    std::cout << "Hello, World!" << std::endl;
    check_argument(argc,argv);

    string in_file_name = argv[1];
    ifstream in_file_(in_file_name.c_str(),ifstream::in);

    string out_file_name = argv[2];
    ofstream out_file_(out_file_name.c_str(),ofstream::out);

    check_files(in_file_,in_file_name,out_file_,out_file_name);


    return 0;
}