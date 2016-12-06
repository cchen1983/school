//
//  RaceCar.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "ICar.h"
#include "IDriver.h"

#ifndef __H_RACECAR__
#define __H_RACECAR__


class RaceCar: public ICar {
public:
    RaceCar(std::string modelName):ICar(modelName) {}
    
    void DriveCar(Driver driver) {
        if (driver.getYearsOfExperience() > 10) {
            driver.Drive();
        }
    }
    
    void DriveCar(RaceDriver driver) {
        if (driver.getYearsOfExperience() > 10) {
            driver.Drive();
        }
    }
};

#endif