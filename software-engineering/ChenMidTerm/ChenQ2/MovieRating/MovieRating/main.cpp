//
//  main.cpp
//  MovieRating
//
//  Created by rOugher on 10/12/16.
//  Copyright (c) 2016 rOugher. All rights reserved.
//

#include <iostream>

using namespace std;

class Patron {
    private:
    int age;
    
    public:
    void setAge(int a){
        age = a;
    }
    
    int getAge() {
        return age;
    }

};

/*interface of Movie*/
class IMovie {
private:
    string name;
    string rating;
    
public:
    virtual void printName() = 0;
    virtual void printRating() = 0;
    virtual void printEligibility(Patron p) = 0;
    
    IMovie(string n, string r) {
        name = n;
        rating = r;
    }
    
    void setName(string n){
        name = n;
    }
    
    void setRating(string r) {
        rating = r;
    }
    
    string getName() {
        return name;
    }
    
    string getRating() {
        return rating;
    }
};

class Movie : public IMovie {
public:
    Movie(string n, string r):IMovie(n, r){
        //setName(name);
        //setRating(rating);
    }
    
    void printName() {
        cout << getName() << endl;
    }
    
    void printRating() {
        cout << getRating() << endl;
    }
    
    void printEligibility(Patron p) {
        string r = getRating();
        int age = p.getAge();
        int res = 0;
        
        if (r == "G") {
            if (age > 0) {
                res = 1;
            }
        }
        else if (r == "PG") {
            if (age >= 13) {
                res = 1;
            }
        }
        else if (r == "R" ) {
            if (age >= 18) {
                res = 1;
            }
        }
        
        if (res == 0) {
            cout << "Partron not allowed watching movie." << endl;
        } else {
            cout << "Partron can watch movie." << endl;
        }
    }
};


int main(int argc, const char * argv[]) {
    string input;
    int age;
    
    Patron patron;
    Movie m1("Kungfu Panda", "G");
    Movie m2("Harry Potter", "PG");
    Movie m3("Spy", "R");
    
    while (1) {
        cout << "Enter age of Patrion: " << endl;
        getline(cin, input);
        age = atoi(input.c_str());
        
        patron.setAge(age);
        cout << "Movie Name:" << endl;
        m1.printName();
        m1.printRating();
        m1.printEligibility(patron);
        m2.printName();
        m2.printRating();
        m2.printEligibility(patron);
        m3.printName();
        m3.printRating();
        m3.printEligibility(patron);
    }
    
    return 0;
}
