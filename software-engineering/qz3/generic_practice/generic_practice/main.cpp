//
//  main.cpp
//  generic_practice
//
//  Created by rOugher on 9/7/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <iostream>

using namespace std;

template <class T>
class Pair {

private:
    T pair[2];
    
public:
    Pair(T a, T b) {
        pair[0] = a;
        pair[1] = b;
    }
    
    T max() {
        return pair[0] > pair[1] ? pair[0] : pair[1];
    }
    
    T min() {
        return pair[0] < pair[1] ? pair[0] : pair[1];
    }
    
    void dump() {
        cout << "Pairs: "<< endl;
        cout << pair[0] << pair[1] << endl;
    }
};

int main(int argc, const char * argv[]) {
    string arg1;
    string arg2;
    string tp;
    
    cout << "Input type of Pair elements:" << endl;
    getline(cin, tp);
    cout << "Input 1st of the Pair: " << endl;
    getline(cin, arg1);
    cout << "Input 2nd of the Pair: " << endl;
    getline(cin, arg2);
    

    if (tp == "int") {
        Pair<int> pr(atoi(arg1.c_str()), atoi(arg2.c_str()));
        cout << "Max: " + to_string(pr.max()) + " Min: " + to_string(pr.min()) << endl;
        pr.dump();
    }
    else {
        Pair<string> pr(arg1, arg2);
        cout << "Max: " + pr.max() + " Min: " + pr.min() << endl;
        pr.dump();
    }
    
    return 0;
}
