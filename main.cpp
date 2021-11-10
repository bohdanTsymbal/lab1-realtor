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
    double cost;
};

void printVector(vector<RealEstate> const & vector) {
    for (RealEstate item : vector) {
        cout << item.area << " " << item.bedroomsNumber << " " << item.toiletsNumber << " " << item.subwayDistance
             << item.isCommercial << " " << item.cost << endl;
    }
}

int main() {
    double area, cost;
    int bedroomsNumber, toiletsNumber, subwayDistance;
    bool isCommercial;
    vector<RealEstate> trainData;

    cout << "Hi, let's try to predict your real estate cost!" << endl;
    cout << "Please enter area (in square meters), a number of bedrooms, a number of toilets, "
            "time you need to get to the nearest subway station on foot (in minutes), whether it is "
            "commercial or dwelling (type 1 or 0 respectively) and cost (in US dollars):" << endl;
    cout << "(You should separate values by space and estate items by new line (each item on a new line))" << endl;

    cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial >> cost;
    while (area != 0) {
        trainData.push_back({area, bedroomsNumber, toiletsNumber, subwayDistance, isCommercial, cost });
        cin >> area >> bedroomsNumber >> toiletsNumber >> subwayDistance >> isCommercial >> cost;
    }

    printVector(trainData);

    return 0;
}
