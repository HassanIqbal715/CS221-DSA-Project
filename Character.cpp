#include "include/Character.hpp"

Character::Character() {
    name = " ";
    exp = 0;
    targetExp = 200;
    level = 1;
    health = 150;
    maxHealth = 150;
    attack = 10;
    baseAttack = 10;
    defense = 15;
    baseAttack = 15;
    speed = 20;
    baseSpeed = 20;

    weapon = nullptr;
    armorSet = new Armor*[4];
    
    for (int i = 0; i < 4; i++) {
        armorSet[i] = nullptr;
    }
}

Character::Character(string name, int health, int attack, int defense, int speed) {
    this->name = name;
    this->health = health;
    this->maxHealth = health;
    this->attack = attack;
    this->baseAttack = attack;
    this->defense = defense;
    this->baseDefense = defense;
    this->speed = speed;
    this->baseSpeed = speed;
    exp = 0;
    targetExp = 200;
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

void Character::setExp(int exp) {
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

void Character::setWeapon(Weapon &weapon) {
    this->weapon = &weapon;
    attack = baseAttack + this->weapon->getAttack();
}

void Character::setArmor(Armor &armor) {
    switch (armor.getType()) {
        case Armor::Type::HELMET:
            if (armorSet[0] != nullptr)
                defense -= armorSet[0]->getDefense();
            armorSet[0] = &armor;
            defense += armorSet[0]->getDefense();
            break;
        
        case Armor::Type::CHESTPLATE:
            if (armorSet[1] != nullptr)
                defense -= armorSet[1]->getDefense();
            armorSet[1] = &armor;
            defense += armorSet[1]->getDefense();
            break;

        case Armor::Type::LEGGINGS:
            if (armorSet[2] != nullptr)
                defense -= armorSet[2]->getDefense();
            armorSet[2] = &armor;
            defense += armorSet[2]->getDefense();
            break;

        case Armor::Type::BOOTS:
            if (armorSet[3] != nullptr)
                defense -= armorSet[3]->getDefense();
            armorSet[3] = &armor;
            defense += armorSet[3]->getDefense();
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

int Character::getMaxHealth() {
    return maxHealth;
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

bool Character::checkLevelUp() {
    return (exp >= targetExp);
}

void Character::levelUp() {
    float levelUpFactor = 1.2;
    ++level;
    exp -= targetExp;
    attack -= baseAttack;
    defense -= baseDefense;
    speed -= baseSpeed;

    maxHealth *= levelUpFactor;
    baseAttack *= levelUpFactor;
    baseDefense *= levelUpFactor;
    baseSpeed *= levelUpFactor;

    health = maxHealth;
    attack += baseAttack;
    defense += baseDefense;
    speed += baseDefense;
    cout << maxHealth << " " << baseAttack;
}

void Character::consumeItem(Food &food) {
    if (health + food.getHealth() >= maxHealth) {
        health = maxHealth;
    }
    else {
        health += food.getHealth();
    }
}

Character::~Character() {
    for (int i = 0; i < 4; i++) {
        delete armorSet[i];
    }
    delete[] armorSet;
    delete weapon;
}