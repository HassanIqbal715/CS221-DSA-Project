#include "include/Inventory.hpp"

Inventory* Inventory::sInstance = nullptr;

Inventory::Inventory() {
    Armor* armor = new Armor("Chestplate", 100, Armor::Type::CHESTPLATE, 100);
    Armor* armor1 = new Armor("Chestplate2", 100, Armor::Type::CHESTPLATE, 100);
    Food* apple = new Food("Apple", 50, 20);
    insertItem(armor);
    insertItem(armor1);
    insertItem(apple);
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
    cout << "Inserting item: " << item->getName() << endl;
}

void Inventory::removeItem(Item* item) {
    if (item == nullptr) {
        cout << "Cannot remove an item that doesn't exist.\n";
        return;
    }

    items.startIterator();

    for (int i = 0; i < items.getSize(); ++i) {
        if (items.getIterator()->data == item) {
            items.deleteNodeByIndex(i);
            items.resetIterator();
            return;
        }
        items.iterateOnce();
    }

    items.resetIterator();
    cout << "Item not found in inventory.\n";
}

Item* Inventory::searchItemByIndex(int index) {
    return items.searchNodeByIndex(index)->data;
}

Item* Inventory::searchItemByName(string name) {
    LinkedList<Item*>::Node* temp = items.head;

    fixStringCase(name);

    for (int i = 0; i < items.size; i++) {
        if (temp->data->getName() == name) {
            return temp->data;
        }
        temp = temp->next;
    }

    return nullptr;
}

// LinkedList<Item*>::Node* Inventory::split(LinkedList<Item*>::Node* head){
//     // fast and slow pointer approach to find middle of linked list
//     LinkedList<Item*>::Node* fast = head;
//     LinkedList<Item*>::Node* slow = head;

//     while(fast!=nullptr && fast->next!=nullptr){
//         fast = fast->next->next;
//         if(fast!=nullptr){
//             slow = slow->next;
//         }
//     }

//     LinkedList<Item*>::Node* temp = slow->next;

//     // breaking the list
//     slow->next = nullptr;
//     temp->prev = nullptr;

//     return temp;
// }

// LinkedList<Item*>::Node* Inventory::mergeSort(LinkedList<Item*>::Node* head){
//     if(head == nullptr || head->next == nullptr){
//         return head;
//     }

//     // splitting the list
//     LinkedList<Item*>::Node* second = split(head);

//     // recursive call to keep splitting and merging the list
//     head = Inventory::mergeSort(head);
//     second = Inventory::mergeSort(second);

//     // merging the sorted lists
//     return Inventory::merge(head, second);
// }

// LinkedList<Item*>::Node* Inventory::merge(LinkedList<Item*>::Node* list1, LinkedList<Item*>::Node*list2){

//     LinkedList<Item*>::Node *temp = nullptr, *prevPtr = nullptr;
    
//     if(list1->data->getName() <= list2->data->getName()){
//         temp = list1;
//         list1 = list1 -> next;
//         list1->prev = nullptr;
//     } else {
//         temp = list2;
//         list2 = list2 -> next;
//         list2->prev = nullptr;
//     }

//     // head of merged array
//     LinkedList<Item*>::Node *tempHead = temp;

//     while(list1!=nullptr && list2!=nullptr){
//         if(list1->data->getName() <= list2->data->getName()){
//             temp->next = list1;
//             list1 = list1 -> next;
//         } else {
//             temp -> next = list2;
//             list2 = list2->next;
//         }

//         prevPtr = temp;
//         temp = temp->next;

//         temp->prev = prevPtr;
//     }

//     if(list1!=nullptr){
//         prevPtr = temp;
//         temp->next = list1;
//         temp->prev = prevPtr;
//     } else {
//         prevPtr = temp;
//         temp->next = list2;
//         temp->prev = prevPtr;
//     }

//     temp = temp->next;

//     return tempHead;
// }

// void Inventory::sort(){
//     // removing circular property of the linked list before sorting
//     items.head->prev = nullptr;
//     items.tail->next = nullptr;

//     // sorting and assigning new head
//     items.head = mergeSort(items.head);

//     // assigning new tail

//     LinkedList<Item*>::Node* current = items.head;

//     while(current!=nullptr && current->next!=nullptr)
//         current = current->next;

//     items.tail = current;

//     items.head->prev = items.tail;
//     items.tail->next = items.head;

// }

LinkedList<Item*>::Node* Inventory::split(LinkedList<Item*>::Node* head) {
    if (!head || !head->next) return nullptr; // Handle trivial cases.

    LinkedList<Item*>::Node* fast = head;
    LinkedList<Item*>::Node* slow = head;

    // Using the fast and slow pointer approach to find the middle.
    while (fast->next && fast->next->next) {
        fast = fast->next->next;
        slow = slow->next;
    }

    // Split the list.
    LinkedList<Item*>::Node* temp = slow->next;
    slow->next = nullptr;
    if (temp) temp->prev = nullptr;

    return temp;
}

LinkedList<Item*>::Node* Inventory::merge(LinkedList<Item*>::Node* list1, LinkedList<Item*>::Node* list2) {
    if (!list1) return list2;
    if (!list2) return list1;

    LinkedList<Item*>::Node* head = nullptr;
    LinkedList<Item*>::Node* tail = nullptr;

    // Merge the two lists by comparing data.
    while (list1 && list2) {
        LinkedList<Item*>::Node* nextNode = nullptr;
        if (list1->data->getName() <= list2->data->getName()) {
            nextNode = list1;
            list1 = list1->next;
        } else {
            nextNode = list2;
            list2 = list2->next;
        }

        // Update the linked list.
        if (!head) {
            head = nextNode;
            tail = head;
        } else {
            tail->next = nextNode;
            nextNode->prev = tail;
            tail = nextNode;
        }
    }

    // Append the remaining elements.
    if (list1) {
        tail->next = list1;
        list1->prev = tail;
    }
    if (list2) {
        tail->next = list2;
        list2->prev = tail;
    }

    return head;
}

LinkedList<Item*>::Node* Inventory::mergeSort(LinkedList<Item*>::Node* head) {
    if (!head || !head->next) return head; // Base case: single node or empty list.

    // Split the list.
    LinkedList<Item*>::Node* second = split(head);

    // Recursively sort each half.
    head = mergeSort(head);
    second = mergeSort(second);

    // Merge the sorted halves.
    return merge(head, second);
}

void Inventory::sort() {
    if (!items.head || !items.head->next) return; // Nothing to sort.

    // Break the circular property.
    if (items.head) items.head->prev = nullptr;
    if (items.tail) items.tail->next = nullptr;

    // Sort the linked list.
    items.head = mergeSort(items.head);

    // Update the tail.
    LinkedList<Item*>::Node* current = items.head;
    items.tail = nullptr;

    while (current) {
        items.tail = current;
        current = current->next;
    }

    // Restore the circular property.
    if (items.head && items.tail) {
        items.head->prev = items.tail;
        items.tail->next = items.head;
    }
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
    cout << "1. Search by Index\n";
    cout << "2. Search by Name\n";
    cout << "3. Sort by Name\n";
    cout << "0. Exit\n";
}

void Inventory::printSubOptions() {
    cout << "1. Use Item\n";
    cout << "2. Compare with your equipment\n";
    cout << "3. Item Description\n";
    cout << "4. Discard Item\n";
    cout << "0. Exit\n";
}

int Inventory::input(Character* character) {
    static int option = 0;
    cin >> option;

    switch (option) {
        case 1: {
            int index;

            cout << "Enter index: ";
            cin >> index;

            auto* temp = searchItemByIndex(index);

            cout << "\n";

            if (temp == nullptr) {
                cout << "Item not found.\n";
                break;
            }

            cout << "Item found.\n";
            cout << "\n------------------------------\n";

            printSubOptions();

            cout << "Enter your option: ";
            inputSubOptions(character, temp);

            break;
        }

        case 2: {
            string name;

            cout << "Enter name: ";
            cin.ignore();
            getline(cin, name);

            auto* temp = searchItemByName(name);

            if (temp == nullptr) {
                cout << "Item not found.\n";
                break;
            }

            cout << "Item found.\n";
            cout << "\n------------------------------\n";
            printSubOptions();

            cout << "Enter your option: ";
            inputSubOptions(character, temp);

            break;
        }
        
        case 3: {
            sort();
            break;
        }

        case 0: {
            return 0;
            break;
        }

        default: {
            cout << "Invalid input.\n";
            break;
        }
    }
    return 1;
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
                else if (armor->getType() == Armor::Type::LEGGINGS) {
                    if (character->getArmor()[2] != nullptr) {
                        insertItem(character->getArmor()[2]);
                    }
                }
                else {
                    if (character->getArmor()[3] != nullptr) {
                        insertItem(character->getArmor()[3]);
                    }
                }
                character->setArmor(*armor);
                removeItem(item);
            }
            else if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
                if (character->getWeapon() != nullptr) {
                    insertItem(character->getWeapon());
                }
                character->setWeapon(*weapon);
                removeItem(item);
            }
            else if (Food* food = dynamic_cast<Food*>(item)) {
                if (character->getHealth() < character->getMaxHealth()) {
                    character->consumeItem(*food);
                    removeItem(item);
                }
                else {
                    cout << "Your health is already full.\n";
                }
            }
            break;
        case 2:
            cout << "\n------------------------------\n";
            if (Armor* armor = dynamic_cast<Armor*>(item)) {
                bool isEquipped = false;
                Armor* tempArmor = nullptr;
                if (armor->getType() == Armor::Type::HELMET) {
                    if (character->getArmor()[0] != nullptr) {
                        isEquipped = true;
                        tempArmor = character->getArmor()[0];
                    }
                }
                else if (armor->getType() == Armor::Type::CHESTPLATE) {
                    if (character->getArmor()[1] != nullptr) {
                        isEquipped = true;
                        tempArmor = character->getArmor()[1];
                    }
                }
                else if (armor->getType() == Armor::Type::LEGGINGS) {
                    if (character->getArmor()[2] != nullptr) {
                        isEquipped = true;
                        tempArmor = character->getArmor()[2];
                    }
                }
                else {
                    if (character->getArmor()[3] != nullptr) {
                        isEquipped = true;
                        tempArmor = character->getArmor()[3];
                    }
                }
                if (isEquipped) {
                    cout << "Character: " << "\t\t" << "Inventory Armor: \n";
                    cout << "\n------------------------------\n";
                    cout << tempArmor->getName() << "\tName\t" << armor->getName() << '\n';
                    cout << tempArmor->getPrice() << "   \tPrice   \t" << armor->getPrice() << '\n';
                    cout << tempArmor->getDefense() << "   \tDefense\t   " << armor->getDefense() << '\n';
                }
                else {
                    cout << "You don't have any armor equipped.\n";
                }
            }
            else if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
                cout << "Character: " << "\t  \t" << "Inventory Weapon: \n";
                cout << "----------------------------------------\n";
                if (character->getWeapon() != nullptr) {
                    cout << character->getWeapon()->getName() << "\tName\t" << weapon->getName() << '\n';
                    cout << character->getWeapon()->getPrice() << "\tPrice\t" << weapon->getPrice() << '\n';

                    if (character->getWeapon()->getType() == Weapon::Type::AXE) {
                        cout << "Axe" << "\tType\t";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::SWORD) {
                        cout << "Sword" << "\tType\t";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::POLEARM) {
                        cout << "Polearm" << "\tType\t";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::STAFF) {
                        cout << "Staff" << "\tType\t";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::BOW) {
                        cout << "Bow" << "\tType\t";
                    }

                    if (character->getWeapon()->getType() == Weapon::Type::AXE) {
                        cout << "Axe\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::SWORD) {
                        cout << "Sword\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::POLEARM) {
                        cout << "Polearm\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::STAFF) {
                        cout << "Staff\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::BOW) {
                        cout << "Bow\n";
                    }
                    cout << character->getWeapon()->getAttack() << "\tAttack\t" << weapon->getAttack() << '\n';
                    cout << character->getWeapon()->getSpeed() << "\tSpeed\t" << weapon->getSpeed() << '\n';
                }
                else {
                    cout << "Punch" << "\tName\t" << weapon->getName() << '\n';
                    cout << 0 << "\tPrice\t" << weapon->getPrice() << '\n';
                    cout << "None" << "\tType\t";

                    if (character->getWeapon()->getType() == Weapon::Type::AXE) {
                        cout << "Axe\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::SWORD) {
                        cout << "Sword\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::POLEARM) {
                        cout << "Polearm\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::STAFF) {
                        cout << "Staff\n";
                    }
                    else if (character->getWeapon()->getType() == Weapon::Type::BOW) {
                        cout << "Bow\n";
                    }

                    cout << character->getAttack() << "\tAttack\t" << weapon->getAttack() << '\n'; 
                    cout << character->getSpeed() << "\tSpeed\t" << weapon->getSpeed() << '\n';
                }
            }
            else {
                cout << "Cannot compare food items.\n";
            }
            break;
        
        case 3:
            cout << "Item: " << item->getName() << "\nPrice: " << item->getPrice() << endl;
            if (Armor* armor = dynamic_cast<Armor*>(item)) {
                cout << "Armor Type: " << armor->getType() << endl;
                cout << "Defense: " << armor->getDefense() << endl;
            }
            else if (Weapon* weapon = dynamic_cast<Weapon*>(item)) {
                cout << "Weapon Type: " << weapon->getType() << endl;
                cout << "Attack Power: " << weapon->getAttack() << endl;
                cout << "Speed: " << weapon->getSpeed() << endl;
            }
            else if (Food* food = dynamic_cast<Food*>(item)) {
                cout << "Healing: " << food->getHealth() << endl;
            }
            break;

        case 4:
            cout << "Removed Item: " << item->getName() << endl;
            removeItem(item);
            break;

        case 0:
            break;

        default:
            cout << "Invalid option.\n";
            break;
    }
}
