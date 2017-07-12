//
// Created by tsx on 2017/7/5.
//

#ifndef CARN_TERM2_FUSIONEKF_H
#define CARN_TERM2_FUSIONEKF_H

#include "MeasurementPackage.h"
#include <vector>
#include <string>
#include <fstream>
#include "KalmanFilter.h"
#include "Tools.h"

class FusionEKF {
public:
    /**
     * Constructot
     */
    FusionEKF();

    /**
     * Deconstructor
     */
    virtual  ~FusionEKF();

    /**
     * Run the whole flow of the kalman filter from here
     */
    void ProcessMeasurement(const MeasurementPackage &measurement_pack);

    /**
     * Kalman filter update and prediction math lives in here
     */
    KalmanFilter ekf_;

private:
    //check whether the tracking toolbox was initiallized or not(first measurement)
    bool is_initialized_;

    //previous prediction timestamp (timestamp of the measurement that was used for prediction)
    long previous_timestamp_;

    //tool object used to compute RMSE
    Tools tools;

    MatrixXd R_laser_;  // Laser measurement covariance matrix
    MatrixXd R_radar_;  // radar measurement covariance matrix
    MatrixXd H_laser_;  // laser measurement matrix
    MatrixXd Hj_;

    float noise_ax_;   //accelaration
    float noise_ay_;



};


#endif //CARN_TERM2_FUSIONEKF_H
