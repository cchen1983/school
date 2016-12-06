//
//  IDriver.cpp
//  InterfaceUtilizing
//
//  Created by rOugher on 9/11/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <stdio.h>
#include <string>

#ifndef __H_IDRIVER__
#define __H_IDRIVER__


class IDriver {
public:
    //virtual ~IDriver(){}
    virtual void Drive() = 0;
    
    IDriver(std::string name, int age, int exp) {
        mName = name;
        mAge = age;
        mYearsOfExperience = exp;
    }
    
    void setName(std::string name) {
        mName = name;
    }
    
    std::string getName() {
        return mName;
    }
    
    void setAge(int age) {
        mAge = age;
    }
    
    int getAge() {
        return mAge;
    }
    
    void setYearsOfExperience(int exp) {
        mYearsOfExperience = exp;
    }
    
    int getYearsOfExperience() {
        return mYearsOfExperience;
    }
    
private:
    std::string mName;
    int mAge;
    int mYearsOfExperience;
    
};

#endif