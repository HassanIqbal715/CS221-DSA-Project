#include <iostream>
#include "include/Enemy.hpp"

Enemy::Enemy() {
    health = 150;
    maxHealth = 150;
    attack = 10;
    baseAttack = 10;
    defense = 15;
    baseAttack = 15;
    speed = 20;
    baseSpeed = 20;
    drop = nullptr;
    coins = 10;
}

Enemy::Enemy(string name, int health, int attack, int speed, int defense, Item* drop, int coins) {
    this->name = name;
    this->health = health;
    this->maxHealth = health;
    this->attack = attack;
    this->baseAttack = attack;
    this->defense = defense;
    this->baseDefense = defense;
    this->speed = speed;
    this->baseSpeed = speed;
    this->drop = drop;
    this->coins = coins;
}

void Enemy::setName(string name) {
    this->name = name;
}

void Enemy::setAttack(int attack) {
    this->attack = attack;
}

void Enemy::setDefense(int defense) {
    this->defense = defense;
}

void Enemy::setHealth(int health) {
    this->health = health;
}

void Enemy::setSpeed(int speed) {
    this->speed = speed;
}

void Enemy::setDropItem(Item* drop) {
    this->drop = drop;
}

void Enemy::setDropCoins(int coins) {
    this->coins = coins;
}

string Enemy::getName() {
    return name;
}

int Enemy::getAttack() {
    return attack;
}

int Enemy::getDefense() {
    return defense;
}

int Enemy::getHealth() {
    return health;
}

int Enemy::getMaxHealth() {
    return maxHealth;
}

int Enemy::getSpeed() {
    return speed;
}

Item* Enemy::getDropItem() {
    return drop;
}

int Enemy::getDropCoins() {
    return coins;
}

void Enemy::scaleStats(int level) {
    if (level <= 5) {
        health += (level * 30);
        maxHealth += (level * 30);
        attack += (level * 5);
        defense += (level * 2);
        speed += (level * 1);
        coins += (level * 10);
    } 
    else if (level <= 10) {
        health += (level * 40);
        maxHealth += (level * 40);
        attack += (level * 10);
        defense += (level * 3);
        speed += (level * 2);
        coins += (level * 15);
    } 
    else if (level <= 15) {
        health += (level * 50);
        maxHealth += (level * 50);
        attack += (level * 15);
        defense += (level * 4);
        speed += (level * 3);
        coins += (level * 20);
    } 
    else if (level <= 20) {
        health += (level * 60);
        maxHealth += (level * 60);
        attack += (level * 20);
        defense += (level * 5);
        speed += (level * 4);
        coins += (level * 25);
    } 
    else if (level <= 25) {
        health += (level * 70);
        maxHealth += (level * 70);
        attack += (level * 25);
        defense += (level * 6);
        speed += (level * 5);
        coins += (level * 30);
    } 
    else if (level <= 30) {
        health += (level * 80);
        maxHealth += (level * 80);
        attack += (level * 30);
        defense += (level * 7);
        speed += (level * 6);
        coins += (level * 35);
    }
    else if (level <= 35) {
        health += (level * 90);
        maxHealth += (level * 90);
        attack += (level * 35);
        defense += (level * 8);
        speed += (level * 7);
        coins += (level * 40);
    } 
    else if (level <= 40) {
        health += (level * 100);
        maxHealth += (level * 100);
        attack += (level * 40);
        defense += (level * 9);
        speed += (level * 8);
        coins += (level * 45);
    } 
    else if (level <= 45) {
        health += (level * 110);
        maxHealth += (level * 110);
        attack += (level * 45);
        defense += (level * 10);
        speed += (level * 9);
        coins += (level * 50);
    } 
    else {
        health += (level * 120);
        maxHealth += (level * 120);
        attack += (level * 50) + (level * level);
        defense += (level * 11);
        speed += (level * 10);
        coins += (level * 60);
    }
}

int Enemy::takeDamage(int damage) {
    damage = (damage + rand() % 100) - 0.25 * defense;
    if (damage < 0)
        damage = 5;
    health = health - damage;
    return damage;
}

bool Enemy::checkDead() {
    return health <= 0;
}

Enemy::~Enemy() { }