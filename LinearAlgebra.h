//
// Created by Admin on 11/15/2021.
//

#ifndef LAB1_REALTOR_LINEARALGEBRA_H
#define LAB1_REALTOR_LINEARALGEBRA_H
#include <vector>

using namespace std;


class LinearAlgebra {
    public:
        static vector<vector<double>> transposeMatrix(const vector<vector<double>> & matrix);
        static vector<vector<double>> getSubmatrix(const vector<vector<double>> & matrix, int elRow, int elColumn);
        static double calculateDeterminant(const vector<vector<double>> & matrix);
        static double getCofactor(const vector<vector<double>> & matrix, int elRow, int elColumn);
        static vector<vector<double>> inverseMatrix(const vector<vector<double>> & matrix);
        static vector<vector<double>> multiplyMatrices(const vector<vector<double>> & leftMatrix,
                                                const vector<vector<double>> & rightMatrix);
};


#endif //LAB1_REALTOR_LINEARALGEBRA_H
