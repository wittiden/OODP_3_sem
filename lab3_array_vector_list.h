#pragma once
template<typename T>
class MyList {
    class Node {
    public:
        T data;
        Node* pNext;
        Node* pPrev;

        Node(T data, Node* pNext = nullptr, Node* pPrev = nullptr) {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
        ~Node() {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    MyList() { size = 0; head = nullptr; tail = nullptr; }
    ~MyList() { clear(); }
    int GetSize() const { return size; }

    T& operator[](const int index) {
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

    void push_back(T data) {
        if (head == nullptr) {
            head = new Node(data);
            tail = head;
        }
        else {
            Node* current = new Node(data, nullptr, tail);
            tail->pNext = current;
            tail = current;
        }
        size++;
    }

    void push_front(T data) {
        if (head == nullptr) {
            head = new Node(data);
            tail = head;
        }
        else {
            Node* current = new Node(data, head, nullptr);
            head->pPrev = current;
            head = current;
        }
        size++;
    }

    void pop_front() {
        if (head == nullptr) return;
        Node* temp = this->head;
        head = head->pNext;
        if (head != nullptr) {
            head->pPrev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    void pop_back() {
        if (tail == nullptr) return;
        if (head == tail) {
            pop_front();
            return;
        }
        Node* temp = tail;
        tail = tail->pPrev;
        tail->pNext = nullptr;
        delete temp;
        size--;
    }

    void insert(T data, int index) {
        if (index == 0) {
            push_front(data);
            return;
        }
        if (index == size) {
            push_back(data);
            return;
        }
        Node* current = this->head;
        for (int i = 0; i < index; i++) {
            current = current->pNext;
        }
        Node* newNode = new Node(data, current, current->pPrev);
        current->pPrev->pNext = newNode;
        current->pPrev = newNode;
        size++;
    }

    void removeAt(int index) {
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == size - 1) {
            pop_back();
            return;
        }
        Node* current = this->head;
        for (int i = 0; i < index; i++) {
            current = current->pNext;
        }
        current->pPrev->pNext = current->pNext;
        if (current->pNext != nullptr) {
            current->pNext->pPrev = current->pPrev;
        }
        delete current;
        size--;
    }

    void clear() {
        while (size) {
            pop_front();
        }
    }

    template<typename T>
    friend void bubbleSortListAscending(MyList<T>& list) {
        int n = list.GetSize();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (list[j].GetId() > list[j + 1].GetId()) {
                    T temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }
    }
    template<typename T>
    friend void bubbleSortListDescending(MyList<T>& list) {
        int n = list.GetSize();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (list[j].GetId() < list[j + 1].GetId()) {
                    T temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }
    }
};

//array & vector 
template<typename T>
void push_up(T*& arr, int& size, const T& element) {
    T* newarr = new T[size + 1];
    newarr[0] = element;
    for (int i = 0; i < size; i++) {
        newarr[i + 1] = arr[i];
    }
    delete[] arr;
    arr = newarr;
    size++;
}
template<typename T>
void push_back(T*& arr, int& size, const T& element) {
    T* newarr = new T[size + 1];
    for (int i = 0; i < size; i++) {
        newarr[i] = arr[i];
    }
    newarr[size] = element;
    delete[] arr;
    arr = newarr;
    size++;
}
template<typename T>
void insert(T*& arr, int& size, const T& element, int index) {
    if (index < 0 || index > size) return;
    T* newarr = new T[size + 1];
    for (int i = 0; i < size + 1; i++) {
        if (i < index) newarr[i] = arr[i];
        else if (i == index) newarr[i] = element;
        else newarr[i] = arr[i - 1];
    }
    delete[] arr;
    arr = newarr;
    size++;
}
template<typename T>
void pop_up(T*& arr, int& size) {
    if (size <= 0 || arr == nullptr) return;
    if (size == 1) {
        delete[] arr;
        arr = nullptr;
        size = 0;
        return;
    }
    T* newarr = new T[size - 1];
    for (int i = 0; i < size - 1; i++) {
        newarr[i] = arr[i + 1];
    }
    delete[] arr;
    arr = newarr;
    size--;
}
template<typename T>
void pop_back(T*& arr, int& size) {
    if (size <= 0 || arr == nullptr) return;
    if (size == 1) {
        delete[] arr;
        arr = nullptr;
        size = 0;
        return;
    }
    T* newarr = new T[size - 1];
    for (int i = 0; i < size - 1; i++) {
        newarr[i] = arr[i];
    }
    delete[] arr;
    arr = newarr;
    size--;
}
template<typename T>
void erase(T*& arr, int& size, int index) {
    if (index < 0 || index >= size || arr == nullptr) return;
    if (size == 1) {
        delete[] arr;
        arr = nullptr;
        size = 0;
        return;
    }
    T* newarr = new T[size - 1];
    for (int i = 0; i < size - 1; i++) {
        if (i < index) newarr[i] = arr[i];
        else newarr[i] = arr[i + 1];
    }
    delete[] arr;
    arr = newarr;
    size--;
}
template<typename T>
void bubbleSortAscending(T* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].GetId() > arr[j + 1].GetId()) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}
template<typename T>
void bubbleSortDescending(T* arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j].GetId() < arr[j + 1].GetId()) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}