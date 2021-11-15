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

void printMatrix(const vector<vector<double>> & matrix) {
    for (const vector<double> & row : matrix) {
        for (const double & value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

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
        vector<vector<double>> predict(const vector<RealEstate> & testData) {
            vector<vector<double>> testVector = DataProcessing::transformToMatrix(testData);
            cout << "testVector" << endl;
            printMatrix(testVector);
            DataProcessing::decoupleTargetVariable(testVector);
            cout << "testVector" << endl;
            printMatrix(testVector);
            DataProcessing::addConstantColumn(testVector);
            cout << "testVector" << endl;
            printMatrix(testVector);
            testVector = LinearAlgebra::transposeMatrix(testVector);
            cout << "transposed testVector" << endl;
            printMatrix(testVector);
            vector<vector<double>> transposedWeights = LinearAlgebra::transposeMatrix(weights);
            cout << "transposedWeights" << endl;
            printMatrix(transposedWeights);
            vector<vector<double>> result = LinearAlgebra::multiplyMatrices(transposedWeights, testVector);
            cout << "result" << endl;
            printMatrix(result);
            return result;
        }
};


#endif //LAB1_REALTOR_LINEARREGRESSION_H
