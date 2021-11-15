#include <iostream>
#include <string>
#include <vector>
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

int main() {
    double area, cost;
    int bedroomsNumber, toiletsNumber, subwayDistance;
    bool isCommercial;
    vector<RealEstate> trainData;

    cout << "Hi, let's try to predict your real estate cost!" << endl
         << "First of all, we need some training data." << endl
         << "Please enter area (in square meters), a number of bedrooms, a number of toilets, "
            "time you need to get to the nearest subway station on foot (in minutes), whether it is "
            "commercial or dwelling (type 1 or 0 respectively) and cost (in US dollars):" << endl
         << "(You should separate values by space and estate items by new line (each item on a new line))" << endl;

    cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial >> cost;
    while (area != 0) {
        RealEstate estate(area, bedroomsNumber, toiletsNumber, subwayDistance, isCommercial, cost);
        trainData.push_back(estate);
        cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial >> cost;
    }

//    cout << "Now please enter the parameters of the estate item cost of which you would like to find out "
//            "(the same way you have done it for the training data, but without cost obviously):" << endl;

//    cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial;
//    while(area != 0) {
//
//    }

    vector<vector<double>> trainMatrix = DataProcessing::transformToMatrix(trainData);
    cout << "Training data:" << endl;
    printMatrix(trainMatrix);

    vector<vector<double>> costVector = DataProcessing::decoupleTargetVariable(trainMatrix);
    cout << "Target variable vector:" << endl;
    printMatrix(costVector);
    cout << "Training data matrix:" << endl;
    printMatrix(trainMatrix);

    DataProcessing::addConstantColumn(trainMatrix);
    cout << "Training data matrix with constant:" << endl;
    printMatrix(trainMatrix);

    vector<vector<double>> transposedTrainMatrix = LinearAlgebra::transposeMatrix(trainMatrix);
    cout << "Transposed training data matrix:" << endl;
    printMatrix(transposedTrainMatrix);

    vector<vector<double>> matricesMultiplication = LinearAlgebra::multiplyMatrices(transposedTrainMatrix, trainMatrix);
    cout << "Matrices multiplication result:" << endl;
    printMatrix(matricesMultiplication);

    double matricesMultiplicationDeterminant = LinearAlgebra::calculateDeterminant(matricesMultiplication);
    cout << "Determinant:" << endl;
    cout << matricesMultiplicationDeterminant << endl;

    vector<vector<double>> inversedMultiplication = LinearAlgebra::inverseMatrix(matricesMultiplication);
    cout << "Inversed multiplication matrix:" << endl;
    printMatrix(inversedMultiplication);

    return 0;
}