//
// Created by Admin on 11/15/2021.
//

#ifndef LAB1_REALTOR_REALESTATE_H
#define LAB1_REALTOR_REALESTATE_H
#include <string>

using namespace std;

class RealEstate {
    public:
        double area;
        int bedroomsNumber;
        int toiletsNumber;
        int subwayDistance;
        bool isCommercial;
        double cost;

        RealEstate(double area, int bedroomsNumber, int toiletsNumber, int subwayDistance,
                   bool isCommercial, double cost = 1) {
            this->area = area;
            this->bedroomsNumber = bedroomsNumber;
            this->toiletsNumber = toiletsNumber;
            this->subwayDistance = subwayDistance;
            this->isCommercial = isCommercial;
            this->cost = cost;
        }

        bool isValid(string & errorMessage) const {
            if (area <= 0 || area > 500000) {
                errorMessage = "Area value must be within (0, 500000] square meters!";
                return false;
            }
            if (bedroomsNumber <= 0 || bedroomsNumber > 35000) {
                errorMessage = "Number of bedrooms must be within [1,35000] units!";
                return false;
            }
            if (toiletsNumber < 0 || toiletsNumber > 25000) {
                errorMessage = "Number of toilets must be within [0,25000] units!";
                return false;
            }
            if (subwayDistance <= 0 || subwayDistance > 240) {
                errorMessage =
                        "Time you need to get to the nearest subway station on foot must be within [1,240] units!";
                return false;
            }
            if (cost <= 0) {
                errorMessage = "Cost value must be greater than 0!";
                return false;
            }

            return true;
        }
};


#endif //LAB1_REALTOR_REALESTATE_H
