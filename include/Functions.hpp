#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "GlobalVariables.hpp"
#include "Character.hpp"
#include "Inventory.hpp"
#include "Shop.hpp"
using namespace std;

void printTitle();
void printUserBalance();
void printHealthBar(int currentHealth, int maxHealth);
void fixStringCase(string& text);
void cleanSaveFiles();
void saveCharacterData(Character *&character);
vector<Character*> loadCharacterData();