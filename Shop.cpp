#include "include/Shop.hpp"

Shop* Shop::sInstance = nullptr;

Shop::Shop() {
    addArmor("Iron Helmet", 200, Armor::Type::HELMET, 10);
    addArmor("Iron Chestplate", 500, Armor::Type::CHESTPLATE, 30);
    addArmor("Iron Leggings", 300, Armor::Type::LEGGINGS, 20);
    addArmor("Iron Boots", 200, Armor::Type::BOOTS, 10);
    addFood("Apple", 50, 20);
    addWeapon("Iron Sword", 500, Weapon::Type::SWORD, 10, 80);
    addWeapon("Iron Spear", 500, Weapon::Type::POLEARM, 10, 50);
    addWeapon("Hunting Bow", 500, Weapon::Type::BOW, 15, 20);
    addWeapon("Wooden Staff ", 500, Weapon::Type::STAFF, 40, 30);
    addWeapon("Iron Axe", 500, Weapon::Type::AXE, 40, 30);
}

Shop::~Shop() {

}

Shop* Shop::instance() {
    if (sInstance == nullptr)
        sInstance = new Shop();
    return sInstance;
}

void Shop::addArmor(string name, int price, Armor::Type type, int defense) {
    items.push_back(new Armor(name, price, type, defense));
}

void Shop::addFood(string name, int price, int health) {
    items.push_back(new Food(name, price, health));
}

void Shop::addWeapon(string name, int price, Weapon::Type type, int attack, int speed) {
    items.push_back(new Weapon(name, price, type, attack, speed));
}

void Shop::removeItemByIndex(int index) {
    items.deleteNodeByIndex(index);
}

Item* Shop::getItemByIndex(int index) {
    return items.searchNodeByIndex(index)->data;
}

Item* Shop::getItemByName(string name) {
    items.startIterator();
    
    for (int i = 0; i <= items.getSize(); i++) {
        if (items.getIterator()->data->getName().compare(name) == 0) {
            Item* tempItem = items.getIterator()->data;
            items.resetIterator();
            return tempItem;
        }     
        items.iterateOnce();
    }

    items.resetIterator();
    return nullptr;
}

void Shop::print() {
    items.startIterator();
    cout << "Welcome to the shop!\n";
    cout << "ID\tName\t\tPrice\n";

    for (int i = 0; i < items.getSize(); i++) {
        cout << items.getIterator()->data->getID() << "\t";
        cout << items.getIterator()->data->getName() << "\t";
        cout << items.getIterator()->data->getPrice() << endl;
        items.iterateOnce();
    }

    items.resetIterator();  // Reset to head after iteration
}


void Shop::releaseElements() {
    items.release();
}

void Shop::release() {
    sInstance->releaseElements();
    delete sInstance;
    sInstance = nullptr;
}