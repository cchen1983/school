//
//  Driver.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "IDriver.h"

#ifndef __H_DRIVER__
#define __H_DRIVER__

class Driver: public IDriver {
public:
    Driver (std::string name, int age, int exp):IDriver(name, age, exp) {}
    
    void Drive() {
        std::cout << getName() + " is driving the car." << std::endl;
    }
};

#endif