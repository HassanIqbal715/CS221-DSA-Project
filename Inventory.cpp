#include "include/Inventory.hpp"

Inventory* Inventory::sInstance = nullptr;

Inventory::Inventory() {
    Armor* armor = new Armor("Chestplate", 100, Armor::Type::CHESTPLATE, 100);
    Armor* armor1 = new Armor("Chestplate2", 100, Armor::Type::CHESTPLATE, 100);
    insertItem(armor);
    insertItem(armor1);
}

Inventory::~Inventory() {
    release();
}

Inventory* Inventory::instance() {
    if (sInstance == nullptr)
        sInstance = new Inventory();
    return sInstance;
}

void Inventory::release() {
    instance()->items.release();
    delete sInstance;
    sInstance = nullptr;
}

void Inventory::insertItem(Item *item) {
    items.push_back(item);
}

void Inventory::removeItem(Item* item) {
    if (item == nullptr) {
        cout << "Cannot remove a null item.\n";
        return;
    }

    // Start the iterator
    items.startIterator();

    for (int i = 0; i < items.getSize(); ++i) {
        if (items.getIterator()->data == item) { // Found the item
            cout << "Removing item: " << item->getName() << endl;
            items.deleteNodeByIndex(i);
            items.resetIterator(); // Reset the iterator after modifying the list
            return;
        }
        items.iterateOnce();
    }

    items.resetIterator(); // Reset the iterator even if not found
    cout << "Item not found in inventory.\n";
}

Item* Inventory::searchItemByIndex(int index) {
    return items.searchNodeByIndex(index)->data;
}

void Inventory::printItems() {
    items.startIterator();
    cout << "Sr.\tName\t\tQuantity\n";

    for (int i = 0; i < items.getSize(); i++) {
        if (i >= 0 && i <= 9)
            cout << 0;
        cout << i << "\t";
        cout << items.getIterator()->data->getName() << "\t";
        cout << endl;
        items.iterateOnce();
    }

    items.resetIterator();
}

void Inventory::printOptions() {
    cout << "------------------------------\n";
    cout << "1. Search by Index\n";
    cout << "2. Search by ID\n";
    cout << "3. Search by Name\n";
    cout << "0. Exit\n";
}

void Inventory::printSubOptions() {
    cout << "1. Use Item\n";
    cout << "2. Item Description\n";
    cout << "3. Discard Item\n";
    cout << "0. Exit\n";
}

void Inventory::input(Character* character) {
    static int option = 0;
    cin >> option;
    switch (option) {
        case 1:
            int index;
            cout << "Enter index: ";
            cin >> index;
            auto* temp = items.searchNodeByIndex(index);

            if (temp == nullptr || temp->data == nullptr) {
                cout << "Item not found.\n";
                return;
            }

            printSubOptions();
            inputSubOptions(character, temp->data);
            break;
    }
}

void Inventory::inputSubOptions(Character* character, Item* item) {
    static int option = 0;
    cin >> option;

    switch (option) {
        case 1:
            if (Armor* armor = dynamic_cast<Armor*>(item)) {
                cout << "Using Armor: " << armor->getName() << endl;
                if (armor->getType() == Armor::Type::HELMET) {
                    if (character->getArmor()[0] != nullptr) {
                        insertItem(character->getArmor()[0]);
                    }
                }
                else if (armor->getType() == Armor::Type::CHESTPLATE) {
                    if (character->getArmor()[1] != nullptr) {
                        insertItem(character->getArmor()[1]);
                    }
                }
                character->setArmor(*armor);
                removeItem(item);
            }
            break;

        case 2:
            cout << "Item: " << item->getName() << ", Price: " << item->getPrice() << endl;
            break;

        case 3:
            cout << "Discarding item: " << item->getName() << endl;
            break;

        case 0:
            cout << "Exiting...\n";
            return;

        default:
            cout << "Invalid option.\n";
    }
}
