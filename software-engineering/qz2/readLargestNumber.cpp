#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <exception>

using namespace std;

static string getFileName() {
    string line;
    cout << "filename:" << endl;
    getline(std::cin, line);
    return line;    
}

static void getNumbers(string filename, int *a, int *b, int *c) {
    //ifstream input( filename );
    std::ifstream istream;
    istream.exceptions ( ifstream::failbit | ifstream::badbit );
    try {
    istream.open( filename.c_str() );
    string line;
    getline(istream, line);
    *a = atoi(line.c_str());
    getline(istream, line);
    *b = atoi(line.c_str());
    getline(istream, line);
    *c = atoi(line.c_str());
    } catch (std::ios_base::failure &fail) {
        cout << "exp" << endl;
        cout << fail.what() << endl;
    }
}

static int findLargest(int a, int b, int c) {
    if (a > b) {
        if (a > c) return a;
        else return c; 
    }
    else {
        if (b > c) return b;
        else return c;
    }
}

int main() {
    string fname = getFileName();
    int a = 0;
    int b = 0;
    int c = 0;
    int res = 0;
    getNumbers(fname, &a, &b, &c);
    res = findLargest(a, b, c);
    cout << "largest: " << endl;  
    cout << res << endl;  
}
