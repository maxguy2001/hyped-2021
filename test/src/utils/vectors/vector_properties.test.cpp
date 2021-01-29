#include <math.h>
#include <cstdlib>
#include "gtest/gtest.h"
#include "utils/math/vector.hpp"
#include "vector_basic.test.cpp"
/*
 * Author: Pablo Morandé
 * Organisation: HYPED
 * Date: 13/11/2020
 * Description: Testing file for vector.hpp
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
namespace hyped
{
namespace utils
{
namespace math
{
/**
 * @brief Struct used to set up all the variables used in the tests one porperty present in some
 * of the operations defined for vectors
 * Associativity.
 * This tests will check if Associativity holds in multiplication and addition.
 */
struct Associativity : public::testing::Test
{
  const int dimension = 3;
  Vector<int, 3> vector_one;
  Vector<int, 3> vector_two;
  Vector<int, 3> vector_three;
  Vector<int, 3> vector_result_one;
  Vector<int, 3> vector_result_two;
  void SetUp()
{
    vector_one = Vector<int, 3>(createRandomArray());
    vector_two = Vector<int, 3>(createRandomArray());
    vector_three = Vector<int, 3>(createRandomArray());
    vector_result_one = Vector<int, 3>();
    vector_result_two = Vector<int, 3>();
  }
};
/**
 * @brief Test used to check if the operator (+=) is associative given three random 3D vectors.
 * (a + b) + c = a + (b + c).
 */
TEST_F(Associativity, isAdditionAssociative)
{
  vector_result_one += vector_one;
  vector_result_one += vector_two;
  vector_result_one += vector_three;

  vector_result_two += vector_two;
  vector_result_two += vector_three;
  vector_result_two += vector_one;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector_result_two[i], vector_result_one[i]);
  }
}
/**
 * @brief Test used to check if the operator (+) is associative given three random 3D vectors.
 * (a + b) + c = a + (b + c).
 */
TEST_F(Associativity, isAutoAdditionAssociative)
{
  vector_result_one = (vector_one+ vector_two) + vector_three;
  vector_result_two = vector_one + (vector_two+vector_three);
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector_result_two[i], vector_result_one[i]);
  }
}
/**
 * @brief Test used to check if the operator (*=) is associative given three random 3D vectors.
 * (a * b) * c = a * (b * c).
 */
TEST_F(Associativity, isMultiplicationAssociative)
{
  vector_result_one *= vector_one;
  vector_result_one *= vector_two;
  vector_result_one *= vector_three;
  vector_result_two *= vector_two;
  vector_result_two *= vector_three;
  vector_result_two *= vector_one;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector_result_two[i], vector_result_one[i]);
  }
}
/**
 * @brief Test used to check if the operator (*) is associative given three random 3D vectors.
 * (a * b) * c = a * (b * c).
 */
TEST_F(Associativity, isAutoMultiplicationAssociative)
{
  vector_result_one = (vector_one * vector_two) * vector_three;
  vector_result_two = vector_one * (vector_two * vector_three);
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector_result_two[i], vector_result_one[i]);
  }
}
/**
 * @brief Struct used to set up all the variables used in the tests for checking if
 * one porperty is resent in some of the operations defined for vectors
 * Commutativity.
 * This tests will check if Commutativity holds in multiplication and addition.
 * Also checks that substraction is anticommutative.
 */
struct Commutativity : public ::testing::Test
{
  const int dimension = 3;
  Vector<int, 3> vector_one;
  Vector<int, 3> vector_two;
  Vector<int, 3> vector_result_one;
  Vector<int, 3> vector_result_two;
  void SetUp()
  {
    vector_one = Vector<int, 3>(createRandomArray());
    vector_two = Vector<int, 3>(createRandomArray());
    vector_result_one = Vector<int, 3>();
    vector_result_two = Vector<int, 3>();
  }
};
/**
 * @brief Test used to check if the operator (+=) is commutative given two random 3D vectors.
 * a + b = b + a.
 */
TEST_F(Commutativity, isAdditionCommutative)
{
  vector_result_one += vector_one;
  vector_result_one += vector_two;
  vector_result_two += vector_two;
  vector_result_two += vector_one;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector_result_two[i], vector_result_one[i]);
  }
}
/**
 * @brief Test used to check if the operator (+) is commutative given two random 3D vectors.
 * a + b = b + a.
 */
TEST_F(Commutativity, isAutoAdditionCommutative)
{
  vector_result_one = vector_two + vector_one;
  vector_result_two = vector_one + vector_two;
  for (int i = 0;i < dimension;i++) {
  ASSERT_EQ(vector_result_one[i], vector_result_two[i]);
  }
}
/**
 * @brief Test used to check if the operator (*=) is commutative given two random 3D vectors.
 * a * b = b * a.
 */
TEST_F(Commutativity, isMultiplicationCommutative)
{
  vector_result_one *= vector_two;
  vector_result_one *= vector_one;
  vector_result_two *= vector_one;
  vector_result_two *= vector_two;
  for (int i = 0;i < dimension;i++) {
  ASSERT_EQ(vector_result_one[i], vector_result_two[i]);
  }
}
/**
 * @brief Test used to check if the operator (*) is commutative given two random 3D vectors.
 * a * b = b * a.
 */
TEST_F(Commutativity, isAutoMultiplicationCommutative)
{
  vector_result_one = vector_two * vector_one;
  vector_result_two = vector_one * vector_two;
  for (int i = 0;i < dimension;i++) {
  ASSERT_EQ(vector_result_one[i], vector_result_two[i]);
  }
}
/**
 * @brief Test used to check if the operator (-=) is anticommutative given two random 3D vectors.
 * a - b = -(b - a).
 */
TEST_F(Commutativity, isSubstractionNotCommutative)
{
  vector_result_one += vector_one;
  vector_result_one -= vector_two;
  vector_result_two += vector_two;
  vector_result_two -= vector_one;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector_result_two[i], -vector_result_one[i]);
  }
}
/**
 * Test used to check if the operator (-) is anticommutative given two random 3D vectors.
 * a - b = -(b - a).
 */
TEST_F(Commutativity, isAutoSubstractionNotCommutative)
{
  vector_result_one = vector_two - vector_one;
  vector_result_two = vector_one - vector_two;
  for (int i = 0;i < dimension;i++) {
  ASSERT_EQ(vector_result_one[i], -vector_result_two[i]);
  }
}
/**
 * @brief Struct used to set up all the variables used in the tests for checking if
 * some porperties with the identity vectors (0,0,0) or (1,1,1) hold for the operations defined for
 * vectors
 */
struct IdentityOperations : public ::testing::Test
{
  std::array<int, 3> values = createRandomArray();
  const int dimension = 3;
  Vector<int, 3> identity_vector;
  Vector<int, 3> vector;
  void SetUp()
  {
    identity_vector = Vector<int, 3>();
    vector = Vector<int, 3>(values);
  }
};
/**
 * @brief Test used to check if adding the identity vector (0,0,0) using += just leaves the vector
 * unchanged.
 */
TEST_F(IdentityOperations, handlesAdditionIdentity)
{
  vector+=identity_vector;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector[i], values[i]);
  }
}
/**
 * @brief Test used to check if adding the identity vector (0,0,0) using + just returns the vector
 * unchanged.
 */
TEST_F(IdentityOperations, hadlesAutoAdditonIdentity)
{
  Vector<int, 3> output = vector + identity_vector;
  for (int i = 0; i < dimension;i++) {
    ASSERT_EQ(vector[i], output[i]);
  }
}
/**
 * @brief Test used to check if substracting the identity vector (0,0,0) using -=
 * just leaves the vector unchanged.
 * It will also check that if we substract a vectgor to itself then the original vector is changed
 * to the identity vector (-=).
 */
TEST_F(IdentityOperations, handlesSubstractionIdentities)
{
  vector -= identity_vector;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector[i], values[i]);
  }
  vector -= vector;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(vector[i], identity_vector[i]);
  }
}
/**
 * @brief Test used to check if substracting the identity vector (0,0,0) using -
 * just returns the vector unchanged.
 * It will also check that if we substract a vectgor to itself then we get back the identity vector.
 */
TEST_F(IdentityOperations, handlesAutoSubstractionIdentities)
{
  Vector<int, 3> output = vector - identity_vector;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(output[i], values[i]);
  }
  output = vector - vector;
  for (int i = 0;i < dimension;i++) {
    ASSERT_EQ(output[i], identity_vector[i]);
  }
}
/**
 * @brief Test used to check if multiplying the vector with the identity vector (0,0,0) using *=
 * just it changes the vector to the the identity vector.
 * It will also check that if we multiply a vector by the identity vector (1,1,1) then our original
 * vector is unchanged.
 */
TEST_F(IdentityOperations, handlesMultiplicationIdentities)
{
  identity_vector = Vector<int, 3>(1);
  vector *= identity_vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(vector[i], values[i]);
  }
  identity_vector = Vector<int, 3>();
  vector *= identity_vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(vector[i], 0);
  }
}
/**
 * @brief Test used to check if multiplying the vector with the identity vector (0,0,0) using *
 * just returns identity vector.
 * It will also check that if we multiply a vector by the identity vector (1,1,1) then we get our
 * original vector.
 */
TEST_F(IdentityOperations, handlesAutoMultiplicationIdentities)
{
  identity_vector = Vector<int, 3>(1);
  Vector<int, 3> output = vector * identity_vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(output[i], vector[i]);
  }
  identity_vector = Vector<int, 3>();
  output = vector * identity_vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(output[i], 0);
  }
}
/**
 * @brief Test used to check if changing the sign of the identity vector (0,0,0) using -
 * just leave the vector unchanged identity vector.
 * It will also check that if we change the sign of a vector and then add it to the original I will
 * end up with the identity vector (0,0,0).
 */
TEST_F(IdentityOperations, handlesChangeOfSignIdentity)
{
  identity_vector = -identity_vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(identity_vector[i], 0);
  }
  Vector<int, 3> vector_two = -vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(identity_vector[i], vector_two[i] + vector[i]);
  }
}
/**
 * @brief Test used to check divide the identity vector (0,0,0) by any vector using /
 * we get the identity back.
 * It will also check that if we divide a vector by itself /. We get the identity vector (1,1,1) as
 * result
 * Finally it checks that if we divide a vector by the identity vector (1,1,1) we get the original
 * vector as result.
 */
TEST_F(IdentityOperations, handlesAutoDivisionIdentities)
{
  vector = Vector<int, 3>(createRandomWithoutZeroesArray());
  Vector<int, 3> output =  identity_vector / vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(output[i], identity_vector[i]);
  }
  identity_vector = Vector<int, 3>(1);
  output =  vector/vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(output[i], identity_vector[i]);
  }
  output =  vector/identity_vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(vector[i], output[i]);
  }
}
/**
 * @brief Test used to check if the identity vector (0,0,0) divided by any vector using /=
 * leaves the identity vector is unchanged.
 * It will also check that if we divide a vector by itself /=. The vector will be changed
 * to the identity vector (1,1,1).
 * Finally it checks that if we divide a vector by the identity vector (1,1,1) our original vector
 * is unchanged.
 */
TEST_F(IdentityOperations, handlesDivisionIdentities)
{
  vector = Vector<int, 3>(createRandomWithoutZeroesArray());
  identity_vector /= vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(0, identity_vector[i]);
  }
  identity_vector = Vector<int, 3>(1);
  vector /= vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(vector[i], identity_vector[i]);
  }
  std::array<int, 3>values = createRandomWithoutZeroesArray();
  vector = Vector<int, 3>(values);
  vector /=  identity_vector;
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(vector[i], values[i]);
  }
}
/**
 * @brief Test used to check if taking the square root of the identity vector (0,0,0) or (1,1,1) leaves the vector
 * unchanged
 */
TEST_F(IdentityOperations, handlesSqrtIdentities)
{
  vector = identity_vector.sqrt();
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(vector[i], identity_vector[i]);
  }
  identity_vector = Vector <int, 3>(1);
  vector = identity_vector.sqrt();
  for (int i = 0; i < dimension; i++) {
    ASSERT_EQ(vector[i], identity_vector[i]);
  }
}
/**
 * @brief Test used to check if the identity vector (0,0,0) has a magnitude of zero and that the
 * magnitude of (1,1,1) is equal to sqrt of three.
 */
TEST_F(IdentityOperations, handlesNormIdentities)
{
  double norm = identity_vector.norm();
  ASSERT_EQ(norm, 0);
  identity_vector = Vector<int, 3>(1);
  norm = identity_vector.norm();
  ASSERT_EQ(norm, std::sqrt(3));
}
}
}
}