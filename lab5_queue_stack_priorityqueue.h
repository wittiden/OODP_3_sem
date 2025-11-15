#pragma once
template<typename T>
class Queue {
    template<typename T>
    class Node {
    public:
        Node* pNext;
        T data;
        Node(T data = T(), Node* pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };

    int Size;
    Node<T>* head;
    Node<T>* tail;

public:
    Queue();
    ~Queue();

    void enqueue(T data);
    void dequeue();
    T& front();
    T& back();
    bool empty() const;
    int getSize() const { return Size; }


    void clear();
    bool update(int index, T newData);
    void sort(bool ascending = true);
    Queue<T> filter(bool (*predicate)(T));

    T& operator[](const int index);
    void print() const;

private:
    void swap(Node<T>* a, Node<T>* b);
};

template<typename T>
Queue<T>::Queue() {
    Size = 0;
    head = nullptr;
    tail = nullptr;
}

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
void Queue<T>::enqueue(T data) {
    Node<T>* newNode = new Node<T>(data);

    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->pNext = newNode;
        tail = newNode;
    }
    Size++;
}

template<typename T>
void Queue<T>::dequeue() {
    if (head == nullptr) return;

    Node<T>* toDelete = head;
    head = head->pNext;

    if (head == nullptr) {
        tail = nullptr;
    }

    delete toDelete;
    Size--;
}

template<typename T>
T& Queue<T>::front() {
    if (head == nullptr) {
        throw std::runtime_error("Queue is empty");
    }
    return head->data;
}

template<typename T>
T& Queue<T>::back() {
    if (tail == nullptr) {
        throw std::runtime_error("Queue is empty");
    }
    return tail->data;
}

template<typename T>
bool Queue<T>::empty() const {
    return head == nullptr;
}

template<typename T>
void Queue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
T& Queue<T>::operator[](const int index) {
    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    }

    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->pNext;
    }
    return current->data;
}

template<typename T>
bool Queue<T>::update(int index, T newData) {
    if (index < 0 || index >= Size) {
        return false;
    }

    Node<T>* current = head;
    for (int i = 0; i < index; i++) {
        current = current->pNext;
    }

    current->data = newData;
    return true;
}

template<typename T>
Queue<T> Queue<T>::filter(bool (*predicate)(T)) {
    Queue<T> result;
    Node<T>* current = head;

    while (current != nullptr) {
        if (predicate(current->data)) {
            result.enqueue(current->data);
        }
        current = current->pNext;
    }

    return result;
}

template<typename T>
void Queue<T>::print() const {
    if (empty()) {
        std::cout << "Queue is empty" << std::endl;
        return;
    }

    Node<T>* current = head;
    std::cout << "Queue (" << Size << " elements): ";
    while (current != nullptr) {
        std::cout << current->data;
        if (current->pNext != nullptr) {
            std::cout << " -> ";
        }
        current = current->pNext;
    }
    std::cout << std::endl;
}

template<typename T>
void Queue<T>::swap(Node<T>* a, Node<T>* b) {
    T temp = a->data;
    a->data = b->data;
    b->data = temp;
}
