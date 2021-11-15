#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct RealEstate {
    double area;
    int bedroomsNumber;
    int toiletsNumber;
    int subwayDistance;
    bool isCommercial;
    double cost = -1;
};

void printVector(const vector<RealEstate> & vector);
void printMatrix(const vector<vector<double>> & matrix);
vector<vector<double>> decoupleTargetVariable(vector<vector<double>> & trainingData);
void addConstantColumn(vector<vector<double>> & trainingData);
vector<vector<double>> transformToMatrix(const vector<RealEstate> & trainingData);
vector<vector<double>> transposeMatrix(const vector<vector<double>> & matrix);
vector<vector<double>> getSubmatrix(const vector<vector<double>> & matrix, int elRow, int elColumn);
double calculateDeterminant(const vector<vector<double>> & matrix);
double getCofactor(const vector<vector<double>> & matrix, int elRow, int elColumn);
vector<vector<double>> inverseMatrix(const vector<vector<double>> & matrix);
vector<vector<double>> multiplyMatrices(const vector<vector<double>> & leftMatrix,
                                        const vector<vector<double>> & rightMatrix);
vector<double> fit(const vector<vector<double>> & trainingData);
double predict(const vector<RealEstate> & trainingData, const vector<RealEstate> & predictingParameters);

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
        trainData.push_back({area, bedroomsNumber, toiletsNumber, subwayDistance, isCommercial, cost });
        cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial >> cost;
    }
//    printVector(trainData);

//    cout << "Now please enter the parameters of the estate item cost of which you would like to find out "
//            "(the same way you have done it for the training data, but without cost obviously):" << endl;

//    cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial;
//    while(area != 0) {
//
//    }

    vector<vector<double>> trainMatrix = transformToMatrix(trainData);
    cout << "Training data:" << endl;
    printMatrix(trainMatrix);

    vector<vector<double>> costVector = decoupleTargetVariable(trainMatrix);
    cout << "Target variable vector:" << endl;
    printMatrix(costVector);
    cout << "Training data matrix:" << endl;
    printMatrix(trainMatrix);

    addConstantColumn(trainMatrix);
    cout << "Training data matrix with constant:" << endl;
    printMatrix(trainMatrix);

    vector<vector<double>> transposedTrainMatrix = transposeMatrix(trainMatrix);
    cout << "Transposed training data matrix:" << endl;
    printMatrix(transposedTrainMatrix);

    vector<vector<double>> matricesMultiplication = multiplyMatrices(transposedTrainMatrix, trainMatrix);
    cout << "Matrices multiplication result:" << endl;
    printMatrix(matricesMultiplication);

    double matricesMultiplicationDeterminant = calculateDeterminant(matricesMultiplication);
    cout << "Determinant:" << endl;
    cout << matricesMultiplicationDeterminant << endl;

    vector<vector<double>> inversedMultiplication = inverseMatrix(matricesMultiplication);
    cout << "Inversed multiplication matrix:" << endl;
    printMatrix(inversedMultiplication);

    return 0;
}

void printVector(const vector<RealEstate> & vector) {
    for (RealEstate item : vector) {
        cout << item.area << " " << item.bedroomsNumber << " " << item.toiletsNumber << " " << item.subwayDistance
             << " " << item.isCommercial << " " << item.cost << endl;
    }
}

void printMatrix(const vector<vector<double>> & matrix) {
    for (const vector<double> & row : matrix) {
        for (const double & value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

vector<vector<double>> transformToMatrix(const vector<RealEstate> & trainingData) {
    vector<vector<double>> matrix;
    matrix.reserve(trainingData.size());

    for (const RealEstate & item : trainingData) {
        matrix.push_back(vector<double> { item.area, (double)item.bedroomsNumber, (double)item.toiletsNumber,
                                          (double)item.subwayDistance, (double)item.isCommercial, item.cost });
    }

    return matrix;
}

vector<vector<double>> decoupleTargetVariable(vector<vector<double>> & trainingData) {
    vector<vector<double>> targetVariableVector;
    targetVariableVector.reserve(trainingData.size());

    for (vector<double> & observation : trainingData) {
        targetVariableVector.push_back(vector<double> { observation.back() });
        observation.pop_back();
    }

    return targetVariableVector;
}

void addConstantColumn(vector<vector<double>> & trainingData) {
    for (vector<double> & observation : trainingData) {
        observation.insert(observation.begin(), 1.0);
    }
}

vector<vector<double>> transposeMatrix(const vector<vector<double>> & matrix) {
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

vector<vector<double>> getSubmatrix(const vector<vector<double>> & matrix, int elRow, int elColumn) {
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

double calculateDeterminant(const vector<vector<double>> & matrix) {
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

double getCofactor(const vector<vector<double>> & matrix, int elRow, int elColumn) {
    double cofactor = pow(-1, elRow + elColumn)
            * calculateDeterminant(getSubmatrix(matrix, elRow, elColumn));
    return cofactor;
}

vector<vector<double>> inverseMatrix(const vector<vector<double>> & matrix) {
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

vector<vector<double>> multiplyMatrices(const vector<vector<double>> & leftMatrix,
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
