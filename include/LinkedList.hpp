#pragma once
template <class T>
class LinkedList {
private:
    friend class Inventory;
    
    bool isEmpty() {
        return size == 0;
    }

    struct Node {
        Node (T val) : data{val}, next{nullptr}, prev{nullptr} {}
        T data;
        Node* next;
        Node* prev;
    };


    Node* head;
    Node* tail;
    Node* iterator;
    int size;

public:

    LinkedList() {
        head = nullptr;
        tail = nullptr;
        iterator = nullptr;
        size = 0;
    }
    
    void push_front(T val) {
        Node* newNode {new Node(val)};

        if (isEmpty()) {
            tail = newNode;
        }
        else {
            head->prev = newNode;
        }

        newNode->next = head;
        tail->next = newNode;
        newNode->prev = tail;
        head = newNode;

        ++size;
    }

    void push_back(T value) {
        Node* newNode {new Node(value)};

        if (isEmpty()) {
            head = newNode;
        }
        else {
            tail->next = newNode;
        }

        newNode->prev = tail;
        head->prev = newNode;
        newNode->next = head;
        tail = newNode;

        ++size;
    }

    void pop_front() {
        if (isEmpty())
            return;
        
        Node* tempNode = head;
        head = head->next;
        delete tempNode;
        --size;

        if (!isEmpty()) {
            head->prev = tail;
            tail->next = head;
        }
        else {
            head = nullptr;
            tail = nullptr;
        }
    }

    void pop_back() {
        if (isEmpty())
            return;
        
        Node* tempNode = tail;
        tail = tail->prev;

        delete tempNode;
        --size;

        if (!isEmpty()) {
            head->prev = tail;
            tail->next = head;
        }
        else {
            head = nullptr;
            tail = nullptr;
        }
    }

    void insertAtIndex(T value, int index) {
        if (isEmpty() || index < 0 || index > size)
            return;
        
        if (index == 0) {
            push_front(value);
            return;
        }
        else if (index == size) {
            push_back(value);
            return;
        }

        Node* newNode = new Node(value);
        Node* tempNode = head;

        for (int i = 0; i < index - 1; i++) {
            tempNode = tempNode->next;
        }

        newNode->next = tempNode->next;
        newNode->prev = tempNode;
        tempNode->next = newNode;
        tempNode = newNode->next;
        tempNode->prev = newNode;

        ++size;
    }

    Node* searchNodeByIndex(int index) {
        if (isEmpty() || index < 0 || index >= size)
            return nullptr;
        
        Node* tempNode = head;
        for (int i = 0; i < index; i++) {
            tempNode = tempNode->next;
        }

        return tempNode;
    }

    Node* searchNodeByValue(T value) {
        if (isEmpty())
            return nullptr;
        if (head->data == value)
            return head;

        bool isFound = false;
        Node* tempNode = head;
        
        for (int i = 0; i < size; i++) {
            tempNode = tempNode->next;
            if (tempNode->data == value) {
                isFound = true;
                break;
            }
        }

        if (isFound)
            return tempNode;
        else
            return nullptr;
    }

    void deleteNodeByIndex(int index) {
        if (isEmpty() || index < 0 || index >= size)
            return;
        
        if (index == 0) {
            pop_front();
            return;
        }
        else if (index == size - 1) {
            pop_back();
            return;
        }

        Node* tempNode = searchNodeByIndex(index);
        Node* previousNode = tempNode->prev;

        previousNode->next = tempNode->next;

        delete tempNode;
        
        tempNode = previousNode->next;
        tempNode->prev = previousNode;
        --size;
    }

    void deleteNodeByValue(T value) {
        if (isEmpty())
            return;
    }

    int getSize() {
        return size;
    }

    void startIterator() {
        if (isEmpty())
            return;

        iterator = head;
    }

    Node* iterateOnce() {
        if (isEmpty())
            return nullptr;

        iterator = iterator->next;
        return iterator;
    }

    Node* getIterator() {
        if (isEmpty())
            return nullptr;

        return iterator;
    }

    void resetIterator() {
        iterator = head;
    }

    Node* begin() {
        if (isEmpty())
            return nullptr;
        return head;
    }

    Node* end() {
        if (isEmpty())
            return nullptr;
        return tail;
    }

    void release() {
        while (!isEmpty()) {
            pop_front();
        }
        iterator = nullptr;
    }

    ~LinkedList() {
        release();
    }

};