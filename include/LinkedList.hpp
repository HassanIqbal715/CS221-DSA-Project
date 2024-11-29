template <class T>
class LinkedList {
private:
    struct Node {
        Node (T val) : data{val}, next{nullptr}, prev{nullptr} {}
        T data;
        Node* next;
        Node* prev;
    };

    bool isEmpty() {

    }

private:
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

};