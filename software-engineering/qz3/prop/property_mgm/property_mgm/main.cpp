//
//  main.cpp
//  property_mgm
//
//  Created by rOugher on 9/7/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <iostream>

using namespace std;

class Employee {

private:
    string mName;
    string mPhone;
    
public:
    void setName(string name){
        mName = name;
    };
    
    string getName() {
        return mName;
    };
    
    void setPhone(string phone) {
        mPhone = phone;
    };
    
    string getPhone() {
        return mPhone;
    };
};


int main(int argc, const char * argv[]) {
    Employee ep;
    
    cout << "Input name of employee:" << endl;
    string name;
    getline(cin, name);
    ep.setName(name);
    
    cout << "Input phone of employee:" << endl;
    string phone;
    getline(cin, phone);
    ep.setPhone(phone);
    
    cout << "Name: " + ep.getName() << endl;
    cout << "Phone: " + ep.getPhone() << endl;
    
    return 0;
}
