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

Character::Character(string name, int health, int attack, int defense, int speed, int level, int exp, int targetExp) {
    this->name = name;
    this->health = health;
    this->maxHealth = health;
    this->attack = attack;
    this->baseAttack = attack;
    this->defense = defense;
    this->baseDefense = defense;
    this->speed = speed;
    this->baseSpeed = speed;
    this->level = level;
    this->exp = exp;
    this->targetExp = targetExp; 
    levelUp();
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

int Character::getTargetExp() {
    return targetExp;
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

int Character::getBaseAttack() {
    return baseAttack;
}

int Character::getDefense() {
    return defense;
}

int Character::getBaseDefense() {
    return baseDefense;
}

int Character::getSpeed() {
    return speed;
}

int Character::getBaseSpeed() {
    return baseSpeed;
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

bool Character::checkDead() {
    return health <= 0;
}

void Character::levelUp() {
    while (exp >= targetExp) {
        ++level;
        exp -= targetExp;
        attack -= baseAttack;
        defense -= baseDefense;
        speed -= baseSpeed;

        targetExp *= 1.5;
        if (level <= 5) {
            maxHealth += 100;
            baseAttack += 10;
            baseDefense += 5;
            baseSpeed += 2;
        }
        else if (level <= 10) {
            maxHealth += 150;
            baseAttack += 20;
            baseDefense += 10;
            baseSpeed += 4;
        }
        else if (level <= 15) {
            maxHealth += 200;
            baseAttack += 30;
            baseDefense += 15;
            baseSpeed += 6;
        }
        else if (level <= 20) {
            maxHealth += 250;
            baseAttack += 40;
            baseDefense += 20;
            baseSpeed += 8;
        }
        else if (level <= 25) {
            maxHealth += 300;
            baseAttack += 50;
            baseDefense += 25;
            baseSpeed += 10;
        }
        else if (level <= 30) {
            maxHealth += 350;
            baseAttack += 60;
            baseDefense += 30;
            baseSpeed += 12;
        }
        else if (level <= 35) {
            maxHealth += 400;
            baseAttack += 70;
            baseDefense += 35;
            baseSpeed += 14;
        }
        else if (level <= 40) {
            maxHealth += 450;
            baseAttack += 80;
            baseDefense += 40;
            baseSpeed += 16;
        }
        else if (level <= 45) {
            maxHealth += 500;
            baseAttack += 90;
            baseDefense += 45;
            baseSpeed += 18;
        }
        else if (level <= 50) {
            maxHealth += 550;
            baseAttack += 100;
            baseDefense += 50;
            baseSpeed += 20;
        }

        health = maxHealth;
        attack = baseAttack;
        defense = baseDefense;
        speed = baseSpeed;
    }
}

int Character::takeDamage(int damage) {
    damage = (damage  + rand() % 100) - 0.25 * defense;
    if (damage < 0)
        damage = 5;
    health = health - damage;
    return damage;
}

void Character::consumeItem(Food &food) {
    if (health + food.getHealth() >= maxHealth) {
        cout << "You gained " << maxHealth - health << " health!\n";
        health = maxHealth;
        cout << "Your health is full now!\n";
    }
    else {
        health += food.getHealth();
        cout << "You gained " << food.getHealth() << " health!\n";
    }
}

void Character::gainExp(int exp) {
    this->exp += exp;
}

void Character::printLevelUpMessage() {
    cout << "Level Up! New Stats: " << endl;
    cout << "Level: " << level << endl;
    cout << "Health: " << maxHealth << endl;
    cout << "Attack: " << attack << endl;
    cout << "Defense: " << defense << endl;
    cout << "Speed: " << speed << endl;
}

void Character::printEquipment() {
    cout << "Armor: \n";
    cout << "\tHelmet: \n";
    if (armorSet[0] != nullptr) {
        cout << "\t\tName: " << armorSet[0]->getName() << '\n';
        cout << "\t\tDefense: " << armorSet[0]->getDefense() << '\n'; 
        cout << "\t\tPrice: " << armorSet[0]->getPrice() << '\n';
    }
    else {
        cout << "\t\tNone\n";
    }

    cout << "\tChestplate: \n";
    if (armorSet[1] != nullptr) {
        cout << "\t\tName: " << armorSet[1]->getName() << '\n';
        cout << "\t\tDefense: " << armorSet[1]->getDefense() << '\n'; 
        cout << "\t\tPrice: " << armorSet[1]->getPrice() << '\n';
    }
    else {
        cout << "\t\tNone\n";
    }

    cout << "\tLeggings: \n";
    if (armorSet[2] != nullptr) {
        cout << "\t\tName: " << armorSet[2]->getName() << '\n';
        cout << "\t\tDefense: " << armorSet[2]->getDefense() << '\n'; 
        cout << "\t\tPrice: " << armorSet[2]->getPrice() << '\n';
    }
    else {
        cout << "\t\tNone\n";
    }

    cout << "\tBoots: \n";
    if (armorSet[3] != nullptr) {
        cout << "\t\tName: " << armorSet[3]->getName() << '\n';
        cout << "\t\tDefense: " << armorSet[3]->getDefense() << '\n'; 
        cout << "\t\tPrice: " << armorSet[3]->getPrice() << '\n';
    }
    else {
        cout << "\t\tNone\n";
    }

    cout << "\nWeapon: \n";
    if (weapon == nullptr) {
        cout << "\tNone";
        return;
    }
    cout << "\tName: " << weapon->getName() << '\n';
    cout << "\tType: ";
    if (weapon->getType() == Weapon::Type::AXE)
        cout << "AXE";
    else if (weapon->getType() == Weapon::Type::BOW)
        cout << "BOW";
    else if (weapon->getType() == Weapon::Type::POLEARM)
        cout << "POLEARM";
    else if (weapon->getType() == Weapon::Type::STAFF)
        cout << "STAFF";
    else if (weapon->getType() == Weapon::Type::SWORD)
        cout << "SWORD";
    else
        cout << "NONE";
    cout << '\n';
    cout << "\tAttack: " << weapon->getAttack() << '\n';
    cout << "\tSpeed: " << weapon->getSpeed() << '\n';
}

Character::~Character() {
    for (int i = 0; i < 4; i++) {
        delete armorSet[i];
    }
    delete[] armorSet;
    delete weapon;
}