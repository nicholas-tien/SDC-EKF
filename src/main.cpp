#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <stdlib.h>
#include "Eigen/Dense"
#include "MeasurementPackage.h"
#include "GroundTruthPackage.h"


using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

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

    vector<MeasurementPackage> meas_packages;
    vector<GroundTruthPackage> gt_packages;

    string line;
    // Prep the measurement packages
    // (each line represents a measurement at a timestamp)
    while (getline(in_file_,line)){
        string sensor_type;
        MeasurementPackage meas_pack;
        GroundTruthPackage gt_pack;
        istringstream iss(line);
        long timestamp;

        //read measurement from the current line
        iss >> sensor_type;
        if(sensor_type.compare("L") == 0){
            //LASER measurement

            //read measurement at this timestamp
            meas_pack.sensor_type_ == MeasurementPackage::LASER;
            meas_pack.raw_measurements_ = VectorXd(2);

            float x;
            float y;

            iss >> x;
            iss >> y;

            meas_pack.raw_measurements_ << x, y;
            iss >> timestamp;
            meas_pack.timeStamp_ == timestamp;
            meas_packages.push_back(meas_pack);

        } else if(sensor_type.compare("R") == 0){

            //RADAR measurements

            //read measurements at this timestamp
            meas_pack.sensor_type_ == MeasurementPackage::RADAR;
            meas_pack.raw_measurements_ = VectorXd(2);
            float ro;
            float phi;
            float ro_dot;
            iss >> ro;
            iss >> phi;
            iss >> ro_dot;
            meas_pack.raw_measurements_ << ro, phi, ro_dot;
            iss >> timestamp;
            meas_pack.timeStamp_ = timestamp;
            meas_packages.push_back(meas_pack);

        }

        // Read ground truth data to compare later
        float x_gt;
        float y_gt;
        float vx_gt;
        float vy_gt;
        iss >> x_gt;
        iss >> y_gt;
        iss >> vx_gt;
        iss >> vy_gt;
        gt_pack.gt_values_ = VectorXd(4);
        gt_pack.gt_values_ << x_gt, y_gt, vx_gt, vy_gt;
        gt_packages.push_back(gt_pack);


    }



    return 0;
}