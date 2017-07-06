//
// Created by tsx on 2017/7/4.
//

#ifndef CARN_TERM2_KALMANFILTER_H
#define CARN_TERM2_KALMANFILTER_H

#include "Eigen/Dense"

using Eigen::MatrixXd;
using Eigen::VectorXd;

class KalmanFilter {
public:
    //state vector
    MatrixXd x_;

    //state covariance matrix
    MatrixXd P_;

    //state transition matrix
    MatrixXd F_;

    //process covariance matrix
    MatrixXd Q_;

    //measurement matrix
    MatrixXd H_;

    // measurement vovariance matrix
    MatrixXd R_;


    /**
     * Constructor
     */
    KalmanFilter();  //default constructor

    KalmanFilter(VectorXd &x_in,MatrixXd &P_in,MatrixXd &F_in,    //initializing constructor
                MatrixXd &H_in,MatrixXd &R_in,MatrixXd &Q_in);

    /**
     * Deconstructor
     */
    virtual ~KalmanFilter();

    /**
     * Prediction predicts the state and the state covariance
     * using the process model
     * @param delta_T Time between k and k+1 in s
     */
    void Predict();

    /**
     * Updates the state and state covariance
     * Method uses the latest measurement,and the instant variables for calculation
     * @param z:The measurement at k+1
     */

    void Update(const VectorXd &z);  //Standard model

    /**
     * Update the state and the state covariace .
     *
     * This version passes in sensor dependent vector and matrices, so it can be
     * used for all sensor types
     *
     * Method uses pre-calculated delta vector y,which is the difference of the measurement
     * vector k+1.
     *
     * Also,a sensor type dependent measurement matrix is passed in.
     * For Linear measurement models,this is a fixed matrix,
     * and for non-linear a calculated Jacobian matrix.
     *
     * @param y : delta of the measurement k+1 and predicted state k+1
     * @param H : measurement matrix for state update
     * @param R : noise covariacn matrix of the sensor
     *
     */
    void Update(const VectorXd &y, const MatrixXd &H,const MatrixXd &R);

private:
    MatrixXd I_;

};


#endif //CARN_TERM2_KALMANFILTER_H
