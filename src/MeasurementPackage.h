//
// Created by nick on 17-7-3.
//

#ifndef CARN_TERM2_MEASUREMENTPACKAGE_H
#define CARN_TERM2_MEASUREMENTPACKAGE_H

#include "Eigen/Dense"

class MeasurementPackage {

public:
    long timeStamp_;

    enum SensorType{
        LASER,
        RADAR
    } sensor_type_;

    Eigen::VectorXd raw_measurements_;

};


#endif //CARN_TERM2_MEASUREMENTPACKAGE_H
