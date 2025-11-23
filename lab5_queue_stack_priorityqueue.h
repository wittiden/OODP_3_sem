#pragma once
//Queue & priority_Queue
template<typename T>
class Queue {
    class Node {
    public:
        Node* pNext;
        T data;
        int priority;

        Node(T data = T(), int priority = 0, Node* pNext = nullptr) {
            this->data = data;
            this->priority = priority;
            this->pNext = pNext;
        }
    };

    int Size;
    Node* head;
    Node* tail;
    bool isPriorityQueue;
public:
    Queue(bool isPriority = false);
    ~Queue();

    void enqueue(T data, int priority = 0);
    void dequeue();
    T& front();
    T& back();
    bool empty() const;
    int getSize() const { return Size; }
    void clear();

    int getPriority(int index) const;

    bool isPriority() const { return isPriorityQueue; }
    void setPriorityMode(bool isPriority) {
        if (!empty()) {
            throw std::runtime_error("Cannot change mode on non-empty queue");
        }
        isPriorityQueue = isPriority;
    }

    T& operator[](const int index);

    Queue<T> filterByIdRange(int start_id, int end_id) const;
private:
    void insertPriority(Node* newNode);
};

template<typename T>
Queue<T>::Queue(bool isPriority) {
    Size = 0;
    head = nullptr;
    tail = nullptr;
    isPriorityQueue = isPriority;
}

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
void Queue<T>::enqueue(T data, int priority) {
    Node* newNode = new Node(data, priority);

    if (isPriorityQueue) {
        insertPriority(newNode);
    }
    else {
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->pNext = newNode;
            tail = newNode;
        }
    }
    Size++;
}

template<typename T>
void Queue<T>::insertPriority(Node* newNode) {
    if (head == nullptr) {
        head = tail = newNode;
        return;
    }

    if (newNode->priority > head->priority) {
        newNode->pNext = head;
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->pNext != nullptr &&
        current->pNext->priority >= newNode->priority) {
        current = current->pNext;
    }

    newNode->pNext = current->pNext;
    current->pNext = newNode;

    if (newNode->pNext == nullptr) {
        tail = newNode;
    }
}

template<typename T>
void Queue<T>::dequeue() {
    if (head == nullptr) return;

    Node* toDelete = head;
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
    if (isPriorityQueue) {
        throw std::runtime_error("Back() not supported for priority queue");
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

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->pNext;
    }
    return current->data;
}

template<typename T>
Queue<T> Queue<T>::filterByIdRange(int min_id, int max_id) const {
    Queue<T> result(isPriorityQueue);

    Node* current = head;
    while (current != nullptr) {
        int current_id = current->data.GetId();
        if (current_id >= min_id && current_id <= max_id) {
            result.enqueue(current->data, current->priority);
        }
        current = current->pNext;
    }

    return result;
}

template<typename T>
int Queue<T>::getPriority(int index) const {
    if (!isPriorityQueue) {
        throw std::runtime_error("getPriority only available for priority queue");
    }

    if (index < 0 || index >= Size) {
        throw std::out_of_range("Index out of range");
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->pNext;
    }

    return current->priority;
}

// Stack 
template<typename T>
class Stack {
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
    Node* head;
public:
    Stack();
    ~Stack();
    int GetSize() { return Size; }
    T& operator[](const int index);
    void pop_front();
    void clear();
    void push_front(T data);
    bool empty() const;
    Stack<T> filterByIdRange(int min_id, int max_id) const;
};

template<typename T>
Stack<T>::Stack() {
    Size = 0;
    head = nullptr;
}

template<typename T>
Stack<T>::~Stack() {
    clear();
}

template<typename T>
T& Stack<T>::operator[](const int index) {
    int counter = 0;
    Node* current = this->head;
    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
    throw std::out_of_range("Index out of range");
}

template<typename T>
void Stack<T>::pop_front() {
    if (head == nullptr) return;

    Node* temp = head;
    head = head->pNext;
    delete temp;
    Size--;
}

template<typename T>
void Stack<T>::clear() {
    while (Size) {
        pop_front();
    }
}

template<typename T>
void Stack<T>::push_front(T data) {
    head = new Node(data, head);
    Size++;
}

template<typename T>
bool Stack<T>::empty() const {
    return head == nullptr;
}
template<typename T>
Stack<T> Stack<T>::filterByIdRange(int min_id, int max_id) const {
    Stack<T> temp;
    Stack<T> result;

    Node* current = head;
    while (current != nullptr) {
        int current_id = current->data.GetId();
        if (current_id >= min_id && current_id <= max_id) {
            temp.push_front(current->data);
        }
        current = current->pNext;
    }
    while (!temp.empty()) {
        result.push_front(temp[0]);
        temp.pop_front();
    }

    return result;
}