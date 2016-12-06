//
//  VintageCar.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "ICar.h"
#include "IDriver.h"

#ifndef __H_VINTAGECAR__
#define __H_VINTAGECAR__

class VintageCar: public ICar {
public:
    VintageCar(std::string modelName):ICar(modelName) {}
    
    void DriveCar(Driver driver) {
        if (driver.getYearsOfExperience() > 20) {
            driver.Drive();
        }
        else {
            std::cout << "cannot drive this car." << std::endl;
        }
    }
    
    void DriveCar(RaceDriver driver) {
        if (driver.getYearsOfExperience() > 20) {
            driver.Drive();
        }
        else {
            std::cout << "cannot drive this car." << std::endl;
        }
    }
};

#endif