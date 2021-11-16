//
// Created by Admin on 11/15/2021.
//

#ifndef LAB1_REALTOR_DATAPROCESSING_H
#define LAB1_REALTOR_DATAPROCESSING_H
#include <vector>
#include <cmath>
#include "RealEstate.h"

using namespace std;


class DataProcessing {
    public:
        static vector<vector<double>> transformToMatrix(const vector<RealEstate> & estateList);
        static vector<vector<double>> decoupleTargetVariable(vector<vector<double>> & dataMatrix);
        static void addConstantColumn(vector<vector<double>> & dataMatrix);
        static void applyLogToMatrix(vector<vector<double>> & dataMatrix);
        static void applyExpToMatrix(vector<vector<double>> & dataMatrix);
};


#endif //LAB1_REALTOR_DATAPROCESSING_H
