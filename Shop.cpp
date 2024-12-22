#include "include/Shop.hpp"

Shop* Shop::sInstance = nullptr;

Shop::Shop() {
    loadItemsFromFile();
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

void Shop::loadItemsFromFile() {
    ifstream file("database/items.txt");
    string line;

    while (std::getline(file, line)) {
        stringstream ss(line);
        string type;
        std::getline(ss, type, ',');

        if (type == "Armor") {
            string name, armorType;
            int price, defense;

            std::getline(ss, name, ',');
            ss >> price;
            ss.ignore(); // Skip comma
            std::getline(ss, armorType, ',');
            ss >> defense;

            Armor::Type typeEnum;
            if (armorType == "HELMET") {
                typeEnum = Armor::HELMET;
            } else if (armorType == "CHESTPLATE") {
                typeEnum = Armor::CHESTPLATE;
            } else if (armorType == "LEGGINGS") {
                typeEnum = Armor::LEGGINGS;
            } else if (armorType == "BOOTS") {
                typeEnum = Armor::BOOTS;
            }

            addArmor(name, price, typeEnum, defense);
        } else if (type == "Food") {
            string name;
            int price, health;

            std::getline(ss, name, ',');
            ss >> price;
            ss.ignore(); // Skip comma
            ss >> health;

            addFood(name, price, health);
        } else if (type == "Weapon") {
            string name, weaponType;
            int price, attack, speed;

            std::getline(ss, name, ',');
            ss >> price;
            ss.ignore(); // Skip comma
            std::getline(ss, weaponType, ',');
            ss >> attack;
            ss.ignore(); // Skip comma
            ss >> speed;

            Weapon::Type typeEnum;
            if (weaponType == "SWORD") {
                typeEnum = Weapon::SWORD;
            } else if (weaponType == "AXE") {
                typeEnum = Weapon::AXE;
            } else if (weaponType == "STAFF") {
                typeEnum = Weapon::STAFF;
            } else if (weaponType == "BOW") {
                typeEnum = Weapon::BOW;
            }

            addWeapon(name, price, typeEnum, attack, speed);
        }
    }
}

void Shop::removeItemByIndex(int index) {
    items.deleteNodeByIndex(index);
}

Item* Shop::getItemByIndex(int index) {
    if (index >= items.getSize() || index < 0) {
        cout << "Index is out of bounds.\n";
        return nullptr;
    }
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
    cout << "===========================================\n";
    cout << "        Welcome to the Shop!\n";
    cout << "===========================================\n";
    cout << left << setw(5) << "ID" << setw(20) << "Name" << setw(10) << "Type" << setw(10) << "Price\n";
    cout << "-------------------------------------------\n";

    for (int i = 0; i < items.getSize(); i++) {
        Item* currentItem = items.getIterator()->data;

        string itemType = "Unknown";
        if (dynamic_cast<Armor*>(currentItem)) {
            itemType = "Armor";
        } else if (dynamic_cast<Weapon*>(currentItem)) {
            itemType = "Weapon";
        } else if (dynamic_cast<Food*>(currentItem)) {
            itemType = "Food";
        }

        cout << left << setw(5) << currentItem->getID() 
             << setw(20) << currentItem->getName() 
             << setw(10) << itemType 
             << setw(10) << currentItem->getPrice() << endl;

        items.iterateOnce();
    }

    items.resetIterator();
    cout << "===========================================\n";
}


void Shop::printOptions() {
    cout << "1. Purchase Item by Index\n";
    cout << "2. Purchase Item by Name\n";
    cout << "3. Check Balance\n";
    cout << "4. Check current equipment\n";
    cout << "5. Sell Item by Index\n";
    cout << "6. Sell Item by Name\n";
    cout << "7. Minigame purchase random item for 1000Rs\n";
    cout << "0. Exit\n";
}

int Shop::input(Character *&character) {
    static int option;
    static int index;
    static string name;
    static Item* item;

    cin >> option;
    switch(option) {
        case 1:
            cout << "Enter index: ";
            cin >> index;
            item = getItemByIndex(index);
            if (userBalance >= item->getPrice()) {
                cout << "Item purchased successfully.\n";
                purchase(item);
                userBalance -= item->getPrice();
            }
            else {
                cout << "Insufficient funds.\n";
            }
            break;
        
        case 2:
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            fixStringCase(name);
            cout << name;
            item = getItemByName(name);
            if (item != nullptr) {
                if (userBalance >= item->getPrice()) {
                    cout << "Item purchased successfully.\n";
                    purchase(item);
                    userBalance -= item->getPrice();
                }
                else {
                    cout << "Insufficient funds.\n";
                }
            }
            else {
                cout << "Item not found.\n";
            }
            break;

        case 3:
            printUserBalance();
            break;

        case 4:
            character->printEquipment();
            break;

        case 5:
            cout << "Enter index: ";
            cin >> index;
            item = Inventory::instance()->searchItemByIndex(index);
            if (item != nullptr) {
                cout << "Item sold successfully.\n";
                sell(item);
                userBalance += item->getPrice();
            }
            else {
                cout << "Item not found.\n";
            }
            break;
        
        case 6:
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);
            fixStringCase(name);
            item = Inventory::instance()->searchItemByName(name);
            if (item != nullptr) {
                cout << "Item sold successfully.\n";
                sell(item);
                userBalance += item->getPrice();
            }
            else {
                cout << "Item not found\n";
            }
            break;

        case 7:
            if (userBalance < 1000) {
                cout << "Insufficient funds.\n";
                break;
            }

            index = rand() % items.getSize();
            cout << "You got";
            //Sleep(1000);
            cout << ".";
            //Sleep(1000);
            cout << ".";
            //Sleep(1000);
            cout << ".";
            item = getItemByIndex(index);

            if (Armor* armor = dynamic_cast<Armor*>(item)) {
                cout << " " << armor->getName() << "\n";
                Inventory::instance()->insertItem(armor);
            }
            else if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
                cout << " " << weapon->getName() << "\n";
                Inventory::instance()->insertItem(weapon);
            }
            else if (Food* food = dynamic_cast<Food*>(item)) {
                cout << " " << food->getName() << "\n";
                Inventory::instance()->insertItem(food);
            }
            cout << '\n';
            //Sleep(1000);
            break;

        case 0:
            return 0;
            break;

        default:
            cout << "Invalid input.\n";
            break;
    }
    return 1;
}

void Shop::purchase(Item* item) {
    Inventory::instance()->insertItem(item);
}

void Shop::sell(Item* item) {
    Inventory::instance()->removeItem(item);
}

void Shop::releaseElements() {
    items.release();
}

void Shop::release() {
    sInstance->releaseElements();
    delete sInstance;
    sInstance = nullptr;
}