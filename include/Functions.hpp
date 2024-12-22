#pragma once
#include <iostream>
#include <fstream>
#include "GlobalVariables.hpp"
#include "Character.hpp"
#include "Inventory.hpp"
using namespace std;

void printTitle();
void printUserBalance();
void printHealthBar(int currentHealth, int maxHealth);
void fixStringCase(string& text);
void cleanSaveFile();
void saveCharacterData(Character *&character);