#include "include/Inventory.hpp"

Inventory::Inventory() {

}

void Inventory::insertItem(Item item) {
    items.push_back(&item);
}

Item* Inventory::searchItemByIndex(int index) {
    return items.searchNodeByIndex(index)->data;
}

void Inventory::print() {
    items.startIterator();
    cout << "Inventory: !\n";
    cout << "Sr.\tName\t\tQuantity";

    for (int i = 0; i < items.getSize(); i++) {
        if (i >= 0 && i <= 9)
            cout << 0;
        cout << i << "\t";
        cout << items.getIterator()->data->getName() << "\t";
        items.iterateOnce();
    }

    items.resetIterator();     
}