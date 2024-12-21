#pragma once
#include <iostream>
#include "Character.hpp"
#include "Enemy.hpp"
using namespace std;

class Skill {
protected:

    int ID;

    string name;
    string description;

    // The skillFactor decides what amount of an action it will do
    // For example, if its an attack skill, the skill factor would decide
    // how much damage the skill would do. Similiarly for a buffing skill
    // skill factor would decide how much to buff the parameter
    int skillFactor;


public:

    Skill();
    Skill(int ID, string name, string descrption, int skillFactor);

    void setSkillFactor(int newFactor);

    int getSkillFactor();

    ~Skill();
};

class AttackSkill : public Skill{
public:
    void attack(Enemy& enemy){
        enemy.setHealth(enemy.getHealth() - skillFactor);
    }
};

class BuffSkill : public Skill{
public:
    enum Buff{ATTACK, HEALTH, DEFENSE, SPEED};

protected:

    Buff buffType;

public:

    
    BuffSkill();
    BuffSkill(int ID, string name, string descrption, int skillFactor,
    Buff buffType);

    void applySkill (Character& character);

};