#include <iostream>
#include "LinearRegression.h"

using namespace std;

void printManual() {
    cout << "Hi, let's try to predict your real estate cost!" << endl
         << "First of all, we need some training data." << endl
         << "Please follow these two pieces of advice so that the program works correctly:" << endl
         << "1. Enter at least 6 units of real estate items as training data;" << endl
         << "2. Try to provide the maximum variety of parameters values in the input data;" << endl
         << "3. You should separate the parameters values by space and real estate units by a new line" << endl
         << "(each item on a new line);" << endl
         << "4. You should enter 0 as an area value to stop input of the data." << endl
         << "Now we can start!" << endl
         << "Please enter area (in square meters), a number of bedrooms, a number of toilets," << endl
         << "time you need to get to the nearest subway station on foot (in minutes)," << endl
         << "whether it is commercial or dwelling (enter 1 or 0 respectively) and cost (in US dollars):" << endl;
}

int main() {
    printManual();

    double area, cost;
    int bedroomsNumber, toiletsNumber, subwayDistance;
    bool isCommercial;
    vector<RealEstate> trainingData;

    cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial >> cost;
    while (area != 0 || trainingData.size() < 6) {
        if (area == 0) {
            cout << "Ooops, check the advice #1!" << endl;
            cout << "Please continue entering the training data:" << endl;
        } else {
            RealEstate estate(area, bedroomsNumber, toiletsNumber, subwayDistance, isCommercial, cost);

            string errorMessage;
            if (estate.isValid(errorMessage))
                trainingData.push_back(estate);
            else {
                cout << errorMessage << endl;
                cout << "You can continue entering the training data:" << endl;
            }
        }
        cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial >> cost;
    }

    LinearRegression regression;
    regression.fit(trainingData);

    cout << "Now please enter the parameters of the estate item cost of which you would like to find out" << endl
         <<"(the same way you have done it for the training data, but without cost obviously):" << endl;

    cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial;
    while(area != 0) {
        vector<RealEstate> testData;
        RealEstate estate(area, bedroomsNumber, toiletsNumber, subwayDistance, isCommercial);

        string errorMessage;
        if (estate.isValid(errorMessage)) {
            testData.push_back(estate);
            double predictedCost = regression.predict(testData)[0][0];
            cout << "The cost of this real estate item is " << predictedCost << " USD" << endl;
        }
        else {
            cout << errorMessage << endl;
        }

        cout << "You can enter the next unit if you want:" << endl;
        cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial;
    }

    cout << "Thank you for using our program. We hope you have had enjoyable experience!" << endl;

    return 0;
}