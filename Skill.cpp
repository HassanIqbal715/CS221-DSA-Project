#include "include/Skill.hpp"

Skill::Skill() {
    ID = -1; 
    name = " ";
    description = " ";
    skillFactor = 1;
}

Skill::Skill(int ID, string name, string description, int skillFactor) :
    ID(ID), name(name), description(description), skillFactor(skillFactor){}

Skill::~Skill() {

}

void Skill::setSkillFactor(int newFactor){
        skillFactor = newFactor;
}

int Skill::getSkillFactor(){
        return skillFactor;
}

AttackSkill::AttackSkill(int ID, string name, string description, int skillFactor) :
    Skill(ID, name, description, skillFactor){}

BuffSkill::BuffSkill() {
    ID = -1; 
    name = " ";
    description = " ";
    skillFactor = 1;
    buffType = DEFENSE;
}

BuffSkill::BuffSkill(int ID, string name, string description, int skillFactor,
    Buff buffType) : Skill(ID, name, description, skillFactor), 
    buffType(buffType){}

void BuffSkill::applySkill (Character *&character){
    switch(buffType){
        case ATTACK:
            character->setAttack(character->getAttack()*skillFactor);
            break;
        case DEFENSE:
            character->setDefense(character->getDefense()*skillFactor);
            break;
        case HEALTH:
            character->setHealth(character->getHealth()*skillFactor);
            break;
        case SPEED:
            character->setSpeed(character->getSpeed()*skillFactor);
            break;
    }
}

void BuffSkill::removeSkill (Character *&character) {
    switch(buffType){
    case ATTACK:
        character->setAttack(character->getAttack()/skillFactor);
        break;
    case DEFENSE:
        character->setDefense(character->getDefense()/skillFactor);
        break;
    case HEALTH:
        character->setHealth(character->getHealth()/skillFactor);
        break;
    case SPEED:
        character->setSpeed(character->getSpeed()/skillFactor);
        break;
    }   
}