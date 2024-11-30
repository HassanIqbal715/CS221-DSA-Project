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
        return head == nullptr;
    }

private:
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head {nullptr};
        tail {nullptr};
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
    }

    void push_back() {
        
    }
};