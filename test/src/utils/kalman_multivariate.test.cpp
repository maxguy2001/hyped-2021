/*
 * Author: Donald Jennings
 * Organisation: HYPED
 * Date: 22/11/2020
 * Description: Testing file for Differentiator.hpp
 *
 *    Copyright 2018 HYPED
 *    Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file
 *    except in compliance with the License. You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software distributed under
 *    the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 *    either express or implied. See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <iostream>
#include <string>
#include "math.h"
#include "gtest/gtest.h"
#include "utils/math/kalman_multivariate.hpp"
#include "utils/system.hpp"

using hyped::utils::math::KalmanMultivariate;

// -------------------------------------------------------------------------------------------------
// Functionality
// -------------------------------------------------------------------------------------------------

/**
 * Struct used for test fixtures testing the functionality of Kalman_Multivaraite.hpp. Constructor
 * sets the values of relevant Vector and Matrix objects using Random values. Naming for these
 * vectors and matrices are based off the implementation in kalman_filter.cpp and
 * the variable names within the kalman_multivariate.hpp
 */
struct KalmanFunctionality : public ::testing::Test {
 protected:
  unsigned int n = 2;
  unsigned int m = 3;
  unsigned int k = 1;

  KalmanMultivariate kalman = KalmanMultivariate(n, m, 0);
  VectorXf x0 = VectorXf::Zero(n);
  VectorXf x1 = VectorXf::Random(n);
  VectorXf z = VectorXf::Random(n);
  MatrixXf P0 = MatrixXf::Zero(n, n);
  MatrixXf A = MatrixXf::Random(n, n);
  MatrixXf B = MatrixXf::Random(n, k);
  MatrixXf Q = MatrixXf::Random(n, n);
  MatrixXf H = MatrixXf::Random(m, n);
  MatrixXf R = MatrixXf::Random(m, m);
  MatrixXf P = MatrixXf::Random(n, n);
  std::string zero_state_estimate_err = "Should handle zero vector as state estimate";
  std::string arb_state_estimate_err = "Should handle any arbitrary vector as state estimate";
  std::string zero_covariance_err = "Should handle zero state covariance";
  std::string arb_covariance_err = "Should handle any arbitrary state covariance";

  void SetUp()
  {
    // Assigns the matrices and vectors to the properties within the kalman object.
    kalman.setModels(A, Q, H, R);
    kalman.setInitial(x0, P);
  }
  void TearDown() {}
};

/**
 * Test fixture used for determining whether Kalman handles the zero vector as input for the state
 * estimates. Should accept
 */
TEST_F(KalmanFunctionality, handlesZeroStateEstimate)
{
  ASSERT_EQ(kalman.getStateEstimate(), x0) << zero_state_estimate_err;
}

/**
 * Test fixture used for determining whether Kalman handles an arbitrary vector (using Random()) as
 * input for the state estimates. This should always be accepted.
 */
TEST_F(KalmanFunctionality, handlesArbitraryStateEstimate)
{
  kalman.setInitial(x1, P);
  ASSERT_EQ(kalman.getStateEstimate(), x1) << arb_state_estimate_err;
}

/**
 * Test fixture used for determining whether Kalman handles the zero matrix as input for the state
 * covariance. This should always be accepted.
 */
TEST_F(KalmanFunctionality, handlesZeroStateCovariance)
{
  kalman.setInitial(x0, P0);
  ASSERT_EQ(kalman.getStateCovariance(), P0) << zero_covariance_err;
}

/**
 * Test fixture used for determining whether Kalman handles an arbitrary matrix (using Random()) as
 * input for the state covariance. This should always be accepted.
 */
TEST_F(KalmanFunctionality, handlesArbitraryStateCovariance)
{
  ASSERT_EQ(kalman.getStateCovariance(), P) << arb_covariance_err;
}

// -------------------------------------------------------------------------------------------------
// Mathematical Properties
// -------------------------------------------------------------------------------------------------

/**
 * Struct used for testing the mathematical properties of kalman_multivariate. Constructor initiates
 * an array of Vectors and Matrices to store arbitrary vectors for testing purposes. The arrays are
 * then populated with values so they can be tested.
 */
struct KalmanMathematics : public::testing::Test {
  unsigned int n = 3;
  unsigned int m = 2;
  unsigned int k = 1;

 protected:
  KalmanMultivariate kalmanMathWithoutControl = KalmanMultivariate(n, m, 0);
  KalmanMultivariate kalmanMathWithControl = KalmanMultivariate(n, m, k);
  static constexpr int NUM_TESTDATA = 50;
  VectorXf x1_Data[NUM_TESTDATA];
  VectorXf z_Data[NUM_TESTDATA];
  VectorXf u_Data[NUM_TESTDATA];
  MatrixXf A_Data[NUM_TESTDATA];
  MatrixXf B_Data[NUM_TESTDATA];
  MatrixXf Q_Data[NUM_TESTDATA];
  MatrixXf H_Data[NUM_TESTDATA];
  MatrixXf R_Data[NUM_TESTDATA];
  MatrixXf P_Data[NUM_TESTDATA];
  MatrixXf I = MatrixXf::Identity(n, n);
  std::string expected_state_estimate_err = "State estimate isnt same as expected state estimate";
  std::string expected_covariance_err = "Covariance isnt the same as expected state covariance";
  void SetUp()
  {
    // Populates the arrays defined above with 50 random values
    for (int i = 0; i < 50; i++) {
      x1_Data[i] = VectorXf::Random(n);
      z_Data[i] = VectorXf::Random(m);
      u_Data[i] = VectorXf::Random(k);
      A_Data[i] = MatrixXf::Random(n, n);
      B_Data[i] = MatrixXf::Random(n, k);
      Q_Data[i] = MatrixXf::Random(n, n);
      H_Data[i] = MatrixXf::Random(m, n);
      R_Data[i] = MatrixXf::Random(m, m);
      P_Data[i] = MatrixXf::Random(n, n);
    }
  }

  void TearDown() {}
};

/**
 * Test fixture for testing whether the filter (without control) updates the X Vector and P Matrix
 * accordingly. Maths has been replicated throughout since to track the values updating and final
 * assert at the end checks that the values are as expected.
 * Checks that both the X vector and P Matrix are updated appropriately
 */
TEST_F(KalmanMathematics, handlesFilterWithoutControl)
{
  for (int i = 0; i < NUM_TESTDATA; i++) {
    MatrixXf A = A_Data[i];
    MatrixXf H = H_Data[i];
    MatrixXf R = R_Data[i];
    MatrixXf Q = Q_Data[i];
    VectorXf z = z_Data[i];
    kalmanMathWithoutControl.setModels(A, Q, H, R);
    kalmanMathWithoutControl.setInitial(x1_Data[i], P_Data[i]);
    VectorXf x = kalmanMathWithoutControl.getStateEstimate();
    MatrixXf p = kalmanMathWithoutControl.getStateCovariance();
    kalmanMathWithoutControl.filter(z);

    // Mimicks predict(VectorXf&)
    x = A * x;
    p = A * p * A.transpose() + Q;

    // Mimicks correct()
    MatrixXf K = (p * H.transpose()) * (H * p * H.transpose() + R).inverse();
    x = x + K * (z - H * x);
    p = (I - K * H) * p;

    ASSERT_EQ(kalmanMathWithoutControl.getStateEstimate(), x)
      << expected_state_estimate_err;
    ASSERT_EQ(kalmanMathWithoutControl.getStateCovariance(), p)
       << expected_covariance_err;
  }
}

/**
 * Test fixture for testing whether the filter (with control) updates the X Vector and P Matrix
 * accordingly. Maths has been replicated throughout since to track the values updating and final
 * assert at the end checks that the values are as expected.
 * Checks that both the X vector and P Matrix are updated appropriately
 */
TEST_F(KalmanMathematics, handlesFilterWithControl)
{
  for (int i = 0; i < NUM_TESTDATA; i ++) {
    MatrixXf A = A_Data[i];
    MatrixXf B = B_Data[i];
    MatrixXf Q = Q_Data[i];
    MatrixXf H = H_Data[i];
    MatrixXf R = R_Data[i];
    VectorXf z = z_Data[i];
    VectorXf u = u_Data[i];
    kalmanMathWithControl.setModels(A, B, Q, H, R);
    kalmanMathWithControl.setInitial(x1_Data[i], P_Data[i]);
    VectorXf x = kalmanMathWithControl.getStateEstimate();
    MatrixXf p = kalmanMathWithControl.getStateCovariance();
    kalmanMathWithControl.filter(u, z);

    // Mimicks filter(VectorXf& u, VectorXf& z)
    x = A * x + B * u;
    p = (A * p * A.transpose()) + Q;

    // Mimicks correct()
    MatrixXf K = (p * H.transpose()) * (H * p * H.transpose() + R).inverse();
    x = x + K * (z - H * x);
    p = (I - K * H) * p;

    ASSERT_EQ(kalmanMathWithControl.getStateEstimate(), x)
      << expected_state_estimate_err;
    ASSERT_EQ(kalmanMathWithControl.getStateCovariance(), p)
      << expected_covariance_err;
  }
}
