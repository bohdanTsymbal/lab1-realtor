//
// Created by Admin on 11/15/2021.
//

#ifndef LAB1_REALTOR_REALESTATE_H
#define LAB1_REALTOR_REALESTATE_H


class RealEstate {
    public:
        double area;
        int bedroomsNumber;
        int toiletsNumber;
        int subwayDistance;
        bool isCommercial;
        double cost;

        RealEstate(double area, int bedroomsNumber, int toiletsNumber, int subwayDistance,
                   bool isCommercial, double cost = 0) {
            this->area = area;
            this->bedroomsNumber = bedroomsNumber;
            this->toiletsNumber = toiletsNumber;
            this->subwayDistance = subwayDistance;
            this->isCommercial = isCommercial;
            this->cost = cost;
        }
};


#endif //LAB1_REALTOR_REALESTATE_H
