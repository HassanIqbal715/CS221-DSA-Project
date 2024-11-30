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
        return size == 0;
    }

private:
    Node* head;
    Node* tail;
    Node* iterator;
    int size;

public:

};