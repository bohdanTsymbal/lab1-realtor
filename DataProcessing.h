//
// Created by Admin on 11/15/2021.
//

#ifndef LAB1_REALTOR_DATAPROCESSING_H
#define LAB1_REALTOR_DATAPROCESSING_H
#include <iostream>
#include <vector>
#include "RealEstate.h"

using namespace std;


class DataProcessing {
    public:
        static vector<vector<double>> transformToMatrix(const vector<RealEstate> & trainingData);
        static vector<vector<double>> decoupleTargetVariable(vector<vector<double>> & trainingData);
        static void addConstantColumn(vector<vector<double>> & trainingData);
};


#endif //LAB1_REALTOR_DATAPROCESSING_H
