//
// Created by nick on 17-7-3.
//

#ifndef CARN_TERM2_GROUNDTRUTHPACKAGE_H
#define CARN_TERM2_GROUNDTRUTHPACKAGE_H

#include "Eigen/Dense"

#include "Eigen/src/Core/Matrix.h"

class GroundTruthPackage {
public:
    long timeStamp_;

    enum SensorType{
        LASER,
        RADAR
    } sensor_type_;

    Eigen::VectorXd gt_values_;

};


#endif //CARN_TERM2_GROUNDTRUTHPACKAGE_H
