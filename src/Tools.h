//
// Created by nick on 17-7-8.
//

#ifndef CARN_TERM2_TOOLS_H
#define CARN_TERM2_TOOLS_H

#include <vector>
#include "Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;


class Tools {

public:
    /**
     * Constructor
     */
    Tools();

    /**
     * Deconstructor
     */
    virtual ~Tools();

    /**
     * A helper member function to calculte RMSE
     */
    VectorXd calculateRMSE(const vector<VectorXd> & estimations, const vector<VectorXd> &ground_truth);

    /**
     * A helper member function to calculate Jacobian
     */
    MatrixXd calculateJacobian(const VectorXd &x_state);

    /**
     * Compute radar measurement function h(x) from predicted state
     */
    VectorXd calculateRadarMeasurementFunction(VectorXd &x);

};


#endif //CARN_TERM2_TOOLS_H

















