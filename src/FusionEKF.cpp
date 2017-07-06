//
// Created by tsx on 2017/7/5.
//

#include "FusionEKF.h"
#include <iostream>
//#include "Tools.h"
#include "Eigen/Dense"

using namespace std;
using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;

/*
 * Constructor
 */
FusionEKF::FusionEKF():
    is_initialized_(false),
    previous_timestamp_(0),
    noise_ax_(5),
    noise_ay_(5)
{
    //initializing matrices
    R_laser_ = MatrixXd(2,2);
    R_radar_ = MatrixXd(3,3);
    H_laser_ = MatrixXd(2,4);
    Hj_ = MatrixXd(3,4);

    //measurement covariance
    R_laser_ << 0.0225,   0,
                0,      0.0225;

    R_radar_ << 0.09,    0,    0,
                0,    0.0009,  0,
                0,      0,    0.09;

    //measurement matrix
    H_laser_ << 1, 0, 0,  0,
                0, 1, 0,  0;

    //initial state covariance matrix P
    MatrixXd P = MatrixXd(4,4);
    P << 1,  0,  0,  0,
         0,  1,  0,  0,
         0,  0, 1000, 0,
         0,  0,   0,  1000;

    //the initial transition matrix F
    MatrixXd F = MatrixXd(4,4);
    F << 1,  0,  1,  0,
         0,  1,  0,  1,
         0,  0,  1,  0,
         0,  0,  0,  1;

    VectorXd x = VectorXd(4);
    MatrixXd Q = MatrixXd(4,4);

    //create filter object
    ekf_ = KalmanFilter(x, P,F,H_laser_,R_laser_, Q);

}


/*
 * Deconstructor
 */
FusionEKF::~FusionEKF() {}

void FusionEKF::ProcessMeasurement(const MeasurementPackage &measurement_pack) {

    /***********************************************************
     *           Initialization
     **********************************************************/
    if(!is_initialized_){
        /**
         * Initialize the state ekf_.x_ with the first measurement.
         * Create teh co-variance matrix
         */
        ekf_.x_ << 1, 1, 1, 1;
        if(measurement_pack.sensor_type_ == MeasurementPackage::RADAR){
            /**
             * Convert radar from polar to cartisian coodinates and initialize state.
             */
            double rho = measurement_pack.raw_measurements_[0];
            double phi = measurement_pack.raw_measurements_[1];
            double rho_dot = measurement_pack.raw_measurements_[2];
            ekf_.x_ << rho * cos(phi), rho * sin(phi),rho_dot * sin(phi),rho_dot * cos(phi);

        } else if(measurement_pack.sensor_type_ == MeasurementPackage::LASER){
            /**
             * Initialize state
             */
            ekf_.x_ << measurement_pack.raw_measurements_[0],measurement_pack.raw_measurements_[1],0,0;
        }

        previous_timestamp_ = measurement_pack.timeStamp_;

        //done initialization, no need to predict or update
        is_initialized_ = true;
        return;
    }

    /*******************************************************
     *          Prediction
     *******************************************************/
    /**
     * Update the state transition matrix F according to the new elapsed time.
     * Time is measured in seconds.
     * Update the process noise covariance matrix.
     * Use noise_ax = 5 and noise_ay = 5 for your Q matrix.
     */
    //Compute the time elapsed between the current and previous measurements,in seconds
    double dt = (measurement_pack.timeStamp_ - previous_timestamp_) / 1000000.0;
    previous_timestamp_ = measurement_pack.timeStamp_;

    ekf_.F_ <<  1,  0,  dt,  0,
                0,  1,  0,   dt,
                0,  0,  1,   0,
                0,  0,  0,   1;

    ekf_.Q_ << pow(dt,4)/4.0 * noise_ax_,  0, pow(dt,3) / 2.0 * noise_ax_,  0,
               0,  pow(dt,4) / 4.0 * noise_ay_,  0,  pow(dt,3) / 2.0 * noise_ay_,
               pow(dt,3) / 2.0 * noise_ax_,  0,  pow(dt,2) * noise_ax_,  0,
               0,  pow(dt,3) / 2.0 * noise_ay_,  0,  pow(dt,2) * noise_ay_;

    if(dt > 0.001){
        ekf_.Predict();
    }


}
