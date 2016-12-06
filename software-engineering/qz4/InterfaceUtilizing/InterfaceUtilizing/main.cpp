//
//  main.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <iostream>
#include "Factory.h"
#include "Driver.h"
#include "NormalCar.h"
#include "RaceDriver.h"

int main(int argc, const char * argv[]) {
    Driver driver = Factory::CreateDriver("vikram", 38, 5);
    VintageCar car = Factory::CreateVintageCar("Old Toyota");
    car.DriveCar(driver);
    
    RaceDriver raceDriver = Factory::CreateRaceDriver("charlie", 40, 21);
    car.DriveCar(raceDriver);

    
    return 0;
}
