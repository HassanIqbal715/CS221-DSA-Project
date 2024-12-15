#include "include/Skill.hpp"

Skill::Skill() { 
    name = " ";
    description = " ";
    buffFactor = 1;
}

Skill::Skill(string name, string descrption, int buffFactor) {
    this->name = name;
    this->description = description;
    this->buffFactor = buffFactor;
}

Skill::~Skill() {

}