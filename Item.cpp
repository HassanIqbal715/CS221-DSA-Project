#include "include/Item.hpp"

// Item class

int Item::itemCount = 0;

Item::Item() {
    name = " ";
    price = -1;
    ID = itemCount;
    itemCount++;
}

Item::Item(Item& item) {
    name = item.name;
    price = item.price;
}

Item::Item(string name, int price) : name(name), price(price) {
    ID = itemCount;
    itemCount++;
}

Item::~Item() {
    delete this;
}

void Item::setName(string name) {
    this->name = name;
}

void Item::setPrice(int price) {
    this->price = price;
}

string Item::getName() {
    return name;
}

int Item::getPrice() {
    return price;
}

int Item::getID() {
    return ID;
}

// Armor class
Armor::Armor() {
    type = HELMET;
    defense = -1;
}

Armor::Armor(Armor& armor) : Item(armor) {
    defense = armor.defense;
    type = armor.type;
}

Armor::Armor(string name, int price, Type type, int defense) :
        Item(name, price), type(type), defense(defense) {}

void Armor::setType(Type type) {
    this->type = type;
}

void Armor::setDefense(int defense) {
    this->defense = defense;
}

Armor::Type Armor::getType() {
    return type;
}

int Armor::getDefense() {
    return defense;
}

Armor* Armor::clone() {
    return new Armor(*this);
}

// Food class
Food::Food() {
    int health = -1;
}

Food::Food(Food& food) : Item(food) {
    health = food.health;
}

Food::Food(string name, int price, int health) :
        Item(name, price), health(health) {}

void Food::setHealth(int health) {
    this->health = health;
}

int Food::getHealth() {
    return health;
}

Food* Food::clone() {
    return new Food(*this);
}

// Weapon class
Weapon::Weapon() {
    type = SWORD;
    attack = -1;
    speed = -1;
}

Weapon::Weapon(Weapon& weapon) : Item(weapon) {
    type = weapon.type;
    attack = weapon.attack;
    speed = weapon.speed;
}

Weapon::Weapon(string name, int price, Type type, int attack, int speed) : 
        Item(name, price), type(type), attack(attack), speed(speed) {}

void Weapon::setType(Type type) {
    this->type = type;
}

void Weapon::setAttack(int attack) {
    this->attack = attack;
}

void Weapon::setSpeed(int speed) {
    this->speed = speed;
}

Weapon::Type Weapon::getType() {
    return type;
}

int Weapon::getAttack() {
    return attack;
}

int Weapon::getSpeed() {
    return speed;
}

Weapon* Weapon::clone() {
    return new Weapon(*this);
}