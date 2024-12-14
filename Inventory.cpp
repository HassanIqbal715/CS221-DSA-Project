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
