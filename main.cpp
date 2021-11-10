#include <iostream>
#include <string>
#include <vector>

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
