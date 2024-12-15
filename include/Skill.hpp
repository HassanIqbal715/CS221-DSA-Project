#pragma once
#include <iostream>
using namespace std;

class Skill {
private:
    string name;
    string description;
    int buffFactor;

public:
    void buffProperty(int &property);
    Skill();
    Skill(string name, string descrption, int buffFactor);
    ~Skill();
};