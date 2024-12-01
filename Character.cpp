#include "include/Character.hpp"

Character::Character() {
    name = " ";
    exp = 0;
    level = 1;
    health = 150;
    attack = 10;
    defense = 15;
    speed = 20;

    weapon = nullptr;
    armorSet = new Armor*[4];
    
    for (int i = 0; i < 4; i++) {
        armorSet[i] = nullptr;
    }
}

Character::Character(string name, int health, int attack, int defense, int speed) {
    this->name = name;
    this->health = health;
    this->attack = attack;
    this->defense = defense;
    this->speed = speed;
    exp = 0;
    level = 1;

    weapon = nullptr;
    armorSet = new Armor*[4];
    
    for (int i = 0; i < 4; i++) {
        armorSet[i] = nullptr;
    }
}

void Character::setName(string name) {
    this->name = name;
}

void Character::setExp() {
    this->exp = exp;
}

void Character::setHealth(int health) {
    this->health = health;
}

void Character::setAttack(int attack) {
    this->attack = attack;
}

void Character::setDefense(int defense) {
    this->defense = defense;
}

void Character::setSpeed(int speed) {
    this->speed = speed;
}

void Character::setWeapon(Weapon weapon) {
    this->weapon = &weapon;
}

void Character::setArmor(Armor armor) {
    switch (armor.getType()) {
        case Armor::Type::HELMET:
            armorSet[0] = &armor;
            break;
        
        case Armor::Type::CHESTPLATE:
            armorSet[1] = &armor;
            break;

        case Armor::Type::LEGGINGS:
            armorSet[2] = &armor;
            break;

        case Armor::Type::BOOTS:
            armorSet[3] = &armor;
            break;
        
        default:
            break;
    }
}

string Character::getName() {
    return name;
}

int Character::getLevel() {
    return level;
}

int Character::getExp() {
    return exp;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

Weapon* Character::getWeapon() {
    return weapon;
}

Armor** Character::getArmor() {
    return armorSet;
}

Character::~Character() {
    for (int i = 0; i < 4; i++) {
        delete armorSet[i];
    }
    delete[] armorSet;
    delete weapon;
}