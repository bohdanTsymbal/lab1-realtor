//
// Created by Admin on 11/15/2021.
//

#include "DataProcessing.h"

using namespace std;

vector<vector<double>> DataProcessing::transformToMatrix(const vector<RealEstate> & estateList) {
    vector<vector<double>> matrix;
    matrix.reserve(estateList.size());

    for (const RealEstate & item : estateList) {
        matrix.push_back(vector<double> { item.area, (double)item.bedroomsNumber, (double)item.toiletsNumber,
                                          (double)item.subwayDistance, (double)item.isCommercial, item.cost });
    }

    return matrix;
}

vector<vector<double>> DataProcessing::decoupleTargetVariable(vector<vector<double>> & dataMatrix) {
    vector<vector<double>> targetVariableVector;
    targetVariableVector.reserve(dataMatrix.size());

    for (vector<double> & observation : dataMatrix) {
        targetVariableVector.push_back(vector<double> { observation.back() });
        observation.pop_back();
    }

    return targetVariableVector;
}

void DataProcessing::addConstantColumn(vector<vector<double>> & dataMatrix) {
    for (vector<double> & observation : dataMatrix) {
        observation.insert(observation.begin(), 1.0);
    }
}

void DataProcessing::applyLogToMatrix(vector<vector<double>> & dataMatrix) {
    for (vector<double> & row : dataMatrix) {
        for (double & value : row) {
            value = log(value);
        }
    }
}

void DataProcessing::applyExpToMatrix(vector<vector<double>> & dataMatrix) {
    for (vector<double> & row : dataMatrix) {
        for (double & value : row) {
            value = exp(value);
        }
    }
}