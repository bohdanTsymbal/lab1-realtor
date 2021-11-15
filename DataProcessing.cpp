//
// Created by Admin on 11/15/2021.
//

#include "DataProcessing.h"

using namespace std;

vector<vector<double>> DataProcessing::transformToMatrix(const vector<RealEstate> & trainingData) {
    vector<vector<double>> matrix;
    matrix.reserve(trainingData.size());

    for (const RealEstate & item : trainingData) {
        matrix.push_back(vector<double> { item.area, (double)item.bedroomsNumber, (double)item.toiletsNumber,
                                          (double)item.subwayDistance, (double)item.isCommercial, item.cost });
    }

    return matrix;
}

vector<vector<double>> DataProcessing::decoupleTargetVariable(vector<vector<double>> & trainingData) {
    vector<vector<double>> targetVariableVector;
    targetVariableVector.reserve(trainingData.size());

    for (vector<double> & observation : trainingData) {
        targetVariableVector.push_back(vector<double> { observation.back() });
        observation.pop_back();
    }

    return targetVariableVector;
}

void DataProcessing::addConstantColumn(vector<vector<double>> & trainingData) {
    for (vector<double> & observation : trainingData) {
        observation.insert(observation.begin(), 1.0);
    }
}