//
//  NormalCar.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "ICar.h"
#include "IDriver.h"

#ifndef __H_NORMALCAR__
#define __H_NORMALCAR__

class NormalCar: public ICar {
public:
    NormalCar(std::string modelName):ICar(modelName) {}
    
    void DriveCar(Driver driver) {
        if (driver.getAge() > 18) {
            driver.Drive();
        }
    }
    
    void DriveCar(RaceDriver driver) {
        if (driver.getAge() > 18) {
            driver.Drive();
        }
    }
};

#endif
