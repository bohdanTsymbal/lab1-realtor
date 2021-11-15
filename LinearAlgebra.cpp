//
// Created by Admin on 11/15/2021.
//

#include "LinearAlgebra.h"

vector<vector<double>> LinearAlgebra::transposeMatrix(const vector<vector<double>> & matrix) {
    vector<vector<double>> transposedMatrix;

    for (const double & value : matrix[0]) {
        transposedMatrix.emplace_back();
    }

    for (int i = 0; i < matrix[0].size(); i++) {
        for (const vector<double> & row : matrix) {
            transposedMatrix[i].push_back(row[i]);
        }
    }

    return transposedMatrix;
}

vector<vector<double>> LinearAlgebra::getSubmatrix(const vector<vector<double>> &matrix, int elRow, int elColumn) {
    vector<vector<double>> submatrix;

    for (int i = 0; i < matrix.size(); i++) {
        if (i != elRow) {
            submatrix.emplace_back();
            for (int j = 0; j < matrix[i].size(); j++) {
                if (j != elColumn) {
                    submatrix[submatrix.size() - 1].push_back(matrix[i][j]);
                }
            }
        }
    }

    return submatrix;
}

double LinearAlgebra::calculateDeterminant(const vector<vector<double>> & matrix) {
    if (matrix.size() == 1 && matrix[0].size() == 1) {
        return matrix[0][0];
    }
    if (matrix.size() == 2 && matrix[0].size() == 2) {
        return matrix[1][1] * matrix[0][0] - matrix[1][0] * matrix [0][1];
    }

    double determinant = 0.0;
    for (int i = 0; i < matrix[0].size(); i++) {
        determinant += matrix[0][i] * getCofactor(matrix, 0, i);
    }

    return determinant;
}

double LinearAlgebra::getCofactor(const vector<vector<double>> & matrix, int elRow, int elColumn) {
    double cofactor = pow(-1, elRow + elColumn)
                      * calculateDeterminant(getSubmatrix(matrix, elRow, elColumn));
    return cofactor;
}

vector<vector<double>> LinearAlgebra::inverseMatrix(const vector<vector<double>> & matrix) {
    vector<vector<double>> transposedMatrix = transposeMatrix(matrix);
    vector<vector<double>> newMatrix;

    for (int i = 0; i < transposedMatrix.size(); i++) {
        newMatrix.emplace_back();
        for (int j = 0; j < transposedMatrix[i].size(); j++) {
            newMatrix[newMatrix.size() - 1].push_back(getCofactor(transposedMatrix, i, j));
        }
    }

    double determinant = calculateDeterminant(matrix);
    for (vector<double> & row : newMatrix) {
        for (double & value : row) {
            value /= determinant;
        }
    }

    return newMatrix;
}

vector<vector<double>> LinearAlgebra::multiplyMatrices(const vector<vector<double>> & leftMatrix,
                                        const vector<vector<double>> & rightMatrix) {
    vector<vector<double>> multiplicationResult;

    multiplicationResult.reserve(leftMatrix.size());
    for (const vector<double> & row : leftMatrix) {
        multiplicationResult.emplace_back();
        for (const double & value : rightMatrix[0]) {
            multiplicationResult[multiplicationResult.size() - 1].push_back(0.0);
        }
    }

    for (int i = 0; i < rightMatrix[0].size(); i++) {
        for (int j = 0; j < rightMatrix.size(); j++) {
            for (int k = 0; k < leftMatrix.size(); k++) {
                multiplicationResult[k][i] += rightMatrix[j][i] * leftMatrix[k][j];
            }
        }
    }

    return multiplicationResult;
}