//
//  main.cpp
//  CircleCalc
//
//  Created by rOugher on 10/12/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <iostream>

using namespace std;

class Circle {
    
private:
    long radius;
    double pi = 3.14f;
    
public:
    void setRadius(long r) {
        radius = r;
    };
    
    double getArea() {
        return pi * radius * radius;
    };
    
    double getCircumference() {
        return 2 * pi * radius;
    };
    
};

class Menu {

private:
    Circle cir;
    
public:
    void show() {
        string opt;
        int op;
        int res = 0;
        
        while (res == 0) {
            cout << "1. Enter the radius" << endl;
            cout << "2. Compute the Area" << endl;
            cout << "3. Compute the Circumference" << endl;
            cout << "4. Quit" << endl;
        
            getline(cin, opt);
            op = atoi(opt.c_str());
        
            res = listen(op);
        }
    };
    
    int listen(int op) {
        
        if (op == 1) {
            string val;
            long r;
            
            cout << "Input the radius: " << endl;
            getline(cin, val);
            r = atol(val.c_str());
            if (r < 0 || r > 1000000000) {
                cout << "Incorrect value range." << endl;
            }
            else {
                cir.setRadius(r);
            }
            
        } else if (op == 2) {
            cout << "Area: " << endl;
            cout << cir.getArea() << endl;
        } else if (op == 3) {
            cout << "Cirumeference: " << endl;
            cout << cir.getCircumference() << endl;
        } else if (op == 4) {
            return 1;
        } else {
            cout << "Invalid option." << endl;
        }
        return 0;
    };
};

int main(int argc, const char * argv[]) {

    Menu menu;
    
    try {
        menu.show();
    } catch (std::exception &fail) {
        cout << "failure:" << endl;
        cout << fail.what() << endl;
    }
    return 0;
}
