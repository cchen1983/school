//
//  Factory.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "ICar.h"
#include "IDriver.h"
#include "Driver.h"
#include "RaceDriver.h"
#include "NormalCar.h"
#include "RaceCar.h"
#include "VintageCar.h"

#ifndef __H_FACTORY__
#define __H_FACTORY__

class Factory {
public:
    static NormalCar CreateNormalCar(std::string modelName) {
        return NormalCar(modelName);
    }
    
    static RaceCar CreateRaceCar(std::string modelName) {
        return RaceCar(modelName);
    }
    
    static VintageCar CreateVintageCar(std::string modelName) {
        return VintageCar(modelName);
    }
    
    static Driver CreateDriver(std::string name, int age, int exp) {
        return Driver(name, age, exp);
    }
    
    static RaceDriver CreateRaceDriver(std::string name, int age, int exp) {
        return RaceDriver(name, age, exp);
    }
};

#endif