//
// Created by Admin on 11/15/2021.
//

#ifndef LAB1_REALTOR_LINEARREGRESSION_H
#define LAB1_REALTOR_LINEARREGRESSION_H
#include <vector>
#include "RealEstate.h"
#include "DataProcessing.h"
#include "LinearAlgebra.h"

using namespace std;


class LinearRegression {
    private:
        vector<vector<double>> weights;
    public:
        LinearRegression() {
            this->weights = {};
        }
        void fit(const vector<RealEstate> & trainingData) {
            vector<vector<double>> trainingMatrix = DataProcessing::transformToMatrix(trainingData);
            vector<vector<double>> costVector = DataProcessing::decoupleTargetVariable(trainingMatrix);
            DataProcessing::addConstantColumn(trainingMatrix);
            vector<vector<double>> transposedTrainingMatrix = LinearAlgebra::transposeMatrix(trainingMatrix);
            vector<vector<double>> multiplication1 =
                    LinearAlgebra::multiplyMatrices(transposedTrainingMatrix, trainingMatrix);
            vector<vector<double>> inversedMultiplication = LinearAlgebra::inverseMatrix(multiplication1);
            vector<vector<double>> multiplication2 =
                    LinearAlgebra::multiplyMatrices(transposedTrainingMatrix, costVector);
            this->weights = LinearAlgebra::multiplyMatrices(inversedMultiplication, multiplication2);
        }
        double predict(const vector<RealEstate> & testData) {
            
        }
};


#endif //LAB1_REALTOR_LINEARREGRESSION_H
