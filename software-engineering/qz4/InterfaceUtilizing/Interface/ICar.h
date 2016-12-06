//
//  ICar.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <stdio.h>
#include <string>
#include "IDriver.h"
#include "Driver.h"
#include "RaceDriver.h"

#ifndef __H_ICAR__
#define __H_ICAR__

class ICar {
public:
    //virtual ~ICar(){}
    virtual void DriveCar(Driver dirver) = 0;
    virtual void DriveCar(RaceDriver dirver) = 0;
    
    ICar(std::string modelName) {
        mModelName = modelName;
    }
    
    void setModeName(std::string name) {
        mModelName = name;
    };
    
    std::string getModeName() {
        return mModelName;
    };
    
private:
    std::string mModelName;
    
};

#endif
