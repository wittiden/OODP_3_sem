#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <algorithm>
#include <fstream>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include "input_check.h"

class bsuir;
class institution {
public:
    virtual void AddInf(std::string type) = 0;
    virtual void DeleteInf(std::string type) = 0;
    virtual void ChangeInf(std::string type) = 0;
    virtual void ShowInf(std::string type) = 0;
    virtual void SortInf(std::string type) = 0;
    virtual void SearchInf(std::string type) = 0;
    virtual void FilterInf(std::string type) = 0;
    virtual ~institution() = 0;
};
institution::~institution() {}

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
};

class bsuir : public institution {
private:
    std::string fullname;
    std::string faculty;
    std::string major;
    int id;

    static int count;
    static bsuir* students_array;
    static int student_array_size;
    static std::vector<bsuir> students_vector;
    static MyList<bsuir> students_list;
public:
    bsuir() { fullname = ""; faculty = ""; major = ""; id = 0; }
    bsuir(std::string fullname) :bsuir() { this->fullname = fullname; }
    bsuir(std::string fullname, std::string faculty) :bsuir(fullname) { this->faculty = faculty; }
    bsuir(std::string fullname, std::string faculty, std::string major) :bsuir(fullname, faculty) { this->major = major; }

    bsuir(const bsuir& other) : fullname(other.fullname), faculty(other.faculty), major(other.major), id(other.id) {}
    ~bsuir() override {}

    std::string GetFullname() const { return fullname; }
    std::string GetFaculty() const { return faculty; }
    std::string GetMajor() const { return major; }
    int GetId() const { return id; }
    void SetFullname(std::string fullname) { this->fullname = fullname; }
    void SetFaculty(std::string faculty) { this->faculty = faculty; }
    void SetMajor(std::string major) { this->major = major; }
    void SetId(int id) { this->id = id; }

    friend std::istream& operator>>(std::istream& is, bsuir& student) {
        std::cout << "ФИО: ";
        std::getline(is, student.fullname);
        std::cout << "Факультет: ";
        std::getline(is, student.faculty);
        std::cout << "Специальность: ";
        std::getline(is, student.major);
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const bsuir& student) {
        os << "ID: " << student.id << ", ФИО: " << student.fullname << ", Факультет: " << student.faculty << ", Специальность: " << student.major;
        return os;
    }

    void AddInf(std::string type) override {
        if (type == "array") {
            unsigned add_choice;
            unsigned students_to_add;
            std::cout << "Введите количество студентов, которое вы хотите добавить: ";
            number_filteredInput<unsigned>(students_to_add);

            if (students_array == nullptr) {
                students_array = new bsuir[0];
                student_array_size = 0;
            }

            for (int i = 0; i < students_to_add; i++) {
                std::cout << "\n=== ДОБАВЛЕНИЕ СТУДЕНТА " << (i + 1) << " (ARRAY) ===\n\n";

                bsuir newStudent;
                std::cin >> newStudent;

                count++;
                newStudent.SetId(count);

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Добавить в начало\n";
                std::cout << "2 - Добавить в конец\n";
                std::cout << "3 - Добавить по индексу\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(add_choice);

                if (add_choice == 1) {
                    push_up(students_array, student_array_size, newStudent);
                    std::cout << "Студент добавлен в начало массива!\n";
                }
                else if (add_choice == 2) {
                    push_back(students_array, student_array_size, newStudent);
                    std::cout << "Студент добавлен в конец массива!\n";
                }
                else if (add_choice == 3) {
                    unsigned index;
                    std::cout << "Введите индекс для добавления (0-" << student_array_size << "): ";
                    number_filteredInput<unsigned>(index);
                    if (index >= 0 && index <= student_array_size) {
                        insert(students_array, student_array_size, newStudent, index);
                        std::cout << "Студент добавлен на позицию " << index << "!\n";
                    }
                    else {
                        std::cout << "Неверный индекс!\n";
                        i--;
                    }
                }
                else {
                    std::cout << "Неверный выбор!\n";
                    i--;
                }

                std::cout << "Студент добавлен успешно! ID: " << newStudent.GetId() << "\n";
            }
            std::cout << std::endl;
            system("pause");
        }
        else if (type == "vector") {
            unsigned add_choice;
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ СТУДЕНТА (VECTOR) ===\n";

                bsuir newStudent;
                std::cin >> newStudent;

                count++;
                newStudent.SetId(count);

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Добавить в начало\n";
                std::cout << "2 - Добавить в конец\n";
                std::cout << "3 - Добавить по индексу\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(add_choice);

                if (add_choice == 1) {
                    students_vector.insert(students_vector.begin(), newStudent);
                    std::cout << "Студент добавлен в начало вектора!\n";
                }
                else if (add_choice == 2) {
                    students_vector.push_back(newStudent);
                    std::cout << "Студент добавлен в конец вектора!\n";
                }
                else if (add_choice == 3) {
                    unsigned index;
                    std::cout << "Введите индекс для добавления (0-" << students_vector.size() << "): ";
                    number_filteredInput<unsigned>(index);

                    if (index >= 0 && index <= students_vector.size()) {
                        students_vector.insert(students_vector.begin() + index, newStudent);
                        std::cout << "Студент добавлен на позицию " << index << "!\n";
                    }
                    else {
                        std::cout << "Неверный индекс!\n";
                    }
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                std::cout << "Студент добавлен успешно! ID: " << newStudent.GetId() << "\n";

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать вектор\n";
                    std::cout << "2 - Продолжить создание\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(add_final_choice);
                    std::cout << std::endl;

                    if (add_final_choice == 1) {
                        ShowInf("vector");
                    }
                    else if (add_final_choice == 2) {
                        break;
                    }
                    else if (add_final_choice == 3) {
                        break;
                    }
                } while (true);

            } while (add_final_choice != 3);
        }
        else if (type == "list") {
            unsigned add_choice;
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ СТУДЕНТА (LIST) ===\n";

                bsuir newStudent;
                std::cin >> newStudent;

                count++;
                newStudent.SetId(count);

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Добавить в начало\n";
                std::cout << "2 - Добавить в конец\n";
                std::cout << "3 - Добавить по индексу\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(add_choice);

                if (add_choice == 1) {
                    students_list.push_front(newStudent);
                    std::cout << "Студент добавлен в начало списка!\n";
                }
                else if (add_choice == 2) {
                    students_list.push_back(newStudent);
                    std::cout << "Студент добавлен в конец списка!\n";
                }
                else if (add_choice == 3) {
                    unsigned index;
                    std::cout << "Введите индекс для добавления (0-" << students_list.GetSize() << "): ";
                    number_filteredInput<unsigned>(index);
                    if (index >= 0 && index <= students_list.GetSize()) {
                        students_list.insert(newStudent, index);
                        std::cout << "Студент добавлен на позицию " << index << "!\n";
                    }
                    else {
                        std::cout << "Неверный индекс!\n";
                    }
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                std::cout << "Студент добавлен успешно! ID: " << newStudent.GetId() << "\n";

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать список\n";
                    std::cout << "2 - Продолжить создание\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(add_final_choice);
                    std::cout << std::endl;

                    if (add_final_choice == 1) {
                        ShowInf("list");
                    }
                    else if (add_final_choice == 2) {
                        break;
                    }
                    else if (add_final_choice == 3) {
                        break;
                    }
                } while (true);

            } while (add_final_choice != 3);
        }
    }

    void DeleteInf(std::string type) override {
        if (type == "array") {
            if (student_array_size == 0) return;

            unsigned del_choice;
            unsigned del_final_choice;

            do {
                std::cout << "=== УДАЛЕНИЕ СТУДЕНТА (ARRAY) ===\n";
                ShowInf("array");

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Удалить из начала\n";
                std::cout << "2 - Удалить из конца\n";
                std::cout << "3 - Удалить по индексу\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(del_choice);

                if (del_choice == 1) {
                    pop_up(students_array, student_array_size);
                    std::cout << "Студент удален из начала массива!\n";
                }
                else if (del_choice == 2) {
                    pop_back(students_array, student_array_size);
                    std::cout << "Студент удален из конца массива!\n";
                }
                else if (del_choice == 3) {
                    unsigned index;
                    std::cout << "Введите индекс для удаления (0-" << student_array_size - 1 << "): ";
                    number_filteredInput<unsigned>(index);
                    if (index >= 0 && index < student_array_size) {
                        erase(students_array, student_array_size, index);
                        std::cout << "Студент удален с позиции " << index << "!\n";
                    }
                    else {
                        std::cout << "Неверный индекс!\n";
                    }
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                std::cout << "Студент удален успешно!\n";

                if (student_array_size == 0) {
                    std::cout << "Массив теперь пуст.\n";
                    return;
                }
                else {
                    do {
                        std::cout << "\nВыберите действие:\n";
                        std::cout << "1 - Продолжить удаление\n";
                        std::cout << "2 - Выйти\n";

                        std::cout << "Номер действия: ";
                        number_filteredInput<unsigned>(del_final_choice);

                        if (del_final_choice == 1) {
                            break;
                        }
                        else if (del_final_choice == 2) {
                            break;
                        }
                    } while (true);
                }
            } while (del_final_choice != 2);
        }
        else if (type == "vector") {
            if (students_vector.empty()) return;

            unsigned del_choice;
            unsigned del_final_choice;

            do {
                std::cout << "=== УДАЛЕНИЕ СТУДЕНТА (VECTOR) ===\n";
                ShowInf("vector");

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Удалить из начала\n";
                std::cout << "2 - Удалить из конца\n";
                std::cout << "3 - Удалить по индексу\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(del_choice);

                if (del_choice == 1) {
                    students_vector.erase(students_vector.begin());
                    std::cout << "Студент удален из начала вектора!\n";
                }
                else if (del_choice == 2) {
                    students_vector.pop_back();
                    std::cout << "Студент удален из конца вектора!\n";
                }
                else if (del_choice == 3) {
                    unsigned index;
                    std::cout << "Введите индекс для удаления (0-" << students_vector.size() - 1 << "): ";
                    number_filteredInput<unsigned>(index);
                    if (index >= 0 && index < students_vector.size()) {
                        students_vector.erase(students_vector.begin() + index);
                        std::cout << "Студент удален с позиции " << index << "!\n";
                    }
                    else {
                        std::cout << "Неверный индекс!\n";
                    }
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                std::cout << "Студент удален успешно!\n";
                if (students_vector.empty()) return;
                else {
                    do {
                        std::cout << "\nВыберите действие:\n";
                        std::cout << "1 - Продолжить удаление\n";
                        std::cout << "2 - Выйти\n";

                        std::cout << "Номер действия: ";
                        number_filteredInput<unsigned>(del_final_choice);
                        std::cout << std::endl;

                        if (del_final_choice == 1) {
                            break;
                        }
                        else if (del_final_choice == 2) {
                            break;
                        }
                    } while (true);
                }
            } while (del_final_choice != 2);
        }
        else if (type == "list") {
            if (students_list.GetSize() == 0) return;

            unsigned del_choice;
            unsigned del_final_choice;

            do {
                std::cout << "=== УДАЛЕНИЕ СТУДЕНТА (LIST) ===\n";
                ShowInf("list");

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Удалить из начала\n";
                std::cout << "2 - Удалить из конца\n";
                std::cout << "3 - Удалить по индексу\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(del_choice);

                if (del_choice == 1) {
                    students_list.pop_front();
                    std::cout << "Студент удален из начала списка!\n";
                }
                else if (del_choice == 2) {
                    students_list.pop_back();
                    std::cout << "Студент удален из конца списка!\n";
                }
                else if (del_choice == 3) {
                    unsigned index;
                    std::cout << "Введите индекс для удаления (0-" << students_list.GetSize() - 1 << "): ";
                    number_filteredInput<unsigned>(index);
                    if (index >= 0 && index < students_list.GetSize()) {
                        students_list.removeAt(index);
                        std::cout << "Студент удален с позиции " << index << "!\n";
                    }
                    else {
                        std::cout << "Неверный индекс!\n";
                    }
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                std::cout << "Студент удален успешно!\n";
                if (students_list.GetSize() == 0) return;
                else {
                    do {
                        std::cout << "\nВыберите действие:\n";
                        std::cout << "1 - Продолжить удаление\n";
                        std::cout << "2 - Выйти\n";

                        std::cout << "Номер действия: ";
                        number_filteredInput<unsigned>(del_final_choice);
                        std::cout << std::endl;

                        if (del_final_choice == 1) {
                            break;
                        }
                        else if (del_final_choice == 2) {
                            break;
                        }
                    } while (true);
                }
            } while (del_final_choice != 2);
        }
    }

    void ChangeInf(std::string type) override {
        if (type == "array") {
            if (student_array_size == 0) return;

            unsigned change_id;
            unsigned change_final_choice;

            do {
                std::cout << "=== ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА (ARRAY) ===\n";
                ShowInf("array");

                std::cout << "Введите ID студента: ";
                number_filteredInput<unsigned>(change_id);

                int found_index = -1;
                for (int i = 0; i < student_array_size; i++) {
                    if (students_array[i].GetId() == change_id) {
                        found_index = i;
                        break;
                    }
                }

                if (found_index == -1) {
                    std::cout << "\nСтудент с ID " << change_id << " не найден!\n";
                }
                else {
                    std::cout << "\nНайден студент: " << students_array[found_index] << std::endl;

                    bsuir updatedStudent;
                    std::cout << "\nВведите новые данные:\n";
                    std::cin >> updatedStudent;
                    updatedStudent.SetId(change_id);
                    students_array[found_index] = updatedStudent;

                    std::cout << "Информация изменена успешно!\n";
                    std::cout << "Обновленные данные: " << students_array[found_index] << std::endl;
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить изменение\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(change_final_choice);

                    if (change_final_choice == 1 || change_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (change_final_choice == 1);
        }
        else if (type == "vector") {
            if (students_vector.empty()) return;

            unsigned change_id;
            unsigned change_final_choice;

            do {
                std::cout << "=== ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА (VECTOR) ===\n";
                ShowInf("vector");

                std::cout << "Введите ID студента: ";
                number_filteredInput<unsigned>(change_id);

                int found_index = -1;
                for (size_t i = 0; i < students_vector.size(); i++) {
                    if (students_vector[i].GetId() == change_id) {
                        found_index = i;
                        break;
                    }
                }

                if (found_index == -1) {
                    std::cout << "\nСтудент с ID " << change_id << " не найден!\n";
                }
                else {
                    std::cout << "\nНайден студент: " << students_vector[found_index] << std::endl;

                    bsuir updatedStudent;
                    std::cout << "\nВведите новые данные:\n";
                    std::cin >> updatedStudent;
                    updatedStudent.SetId(change_id);
                    students_vector[found_index] = updatedStudent;

                    std::cout << "Информация изменена успешно!\n";
                    std::cout << "Обновленные данные: " << students_vector[found_index] << std::endl;
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить изменение\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(change_final_choice);

                    if (change_final_choice == 1 || change_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (change_final_choice == 1);
        }
        else if (type == "list") {
            if (students_list.GetSize() == 0) return;

            unsigned change_id;
            unsigned change_final_choice;

            do {
                std::cout << "=== ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА (LIST) ===\n";
                ShowInf("list");

                std::cout << "Введите ID студента: ";
                number_filteredInput<unsigned>(change_id);

                int found_index = -1;
                for (int i = 0; i < students_list.GetSize(); i++) {
                    if (students_list[i].GetId() == change_id) {
                        found_index = i;
                        break;
                    }
                }

                if (found_index == -1) {
                    std::cout << "\nСтудент с ID " << change_id << " не найден!\n";
                }
                else {
                    std::cout << "\nНайден студент: " << students_list[found_index] << std::endl;

                    bsuir updatedStudent;
                    std::cout << "\nВведите новые данные:\n";
                    std::cin >> updatedStudent;
                    updatedStudent.SetId(change_id);
                    students_list[found_index] = updatedStudent;

                    std::cout << "Информация изменена успешно!\n";
                    std::cout << "Обновленные данные: " << students_list[found_index] << std::endl;
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить изменение\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(change_final_choice);

                    if (change_final_choice == 1 || change_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (change_final_choice == 1);
        }
    }

    void ShowInf(std::string type) override {
        if (type == "array") {
            if (student_array_size == 0) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (ARRAY) ===\n";
            for (int i = 0; i < student_array_size; i++) {
                std::cout << i << ": " << students_array[i] << std::endl;
            }
        }
        else if (type == "vector") {
            if (students_vector.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (VECTOR) ===\n";
            for (size_t i = 0; i < students_vector.size(); i++) {
                std::cout << i << ": " << students_vector[i] << std::endl;
            }
        }
        else if (type == "list") {
            if (students_list.GetSize() == 0) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (LIST) ===\n";
            for (int i = 0; i < students_list.GetSize(); i++) {
                std::cout << i << ": " << students_list[i] << std::endl;
            }
        }
    }

    void SortInf(std::string type) override {

        if (type == "array") {
            if (student_array_size < 2) { return; }

            unsigned sort_choice;
            std::cout << "=== СОРТИРОВКА СТУДЕНТОВ (" << type << ") ===\n";
            std::cout << "1 - По возрастанию ID\n";
            std::cout << "2 - По убыванию ID\n";
            std::cout << "Выберите тип сортировки: ";
            number_filteredInput<unsigned>(sort_choice);

            bsuir* sorted_array = new bsuir[student_array_size];
            for (int i = 0; i < student_array_size; i++) {
                sorted_array[i] = students_array[i];
            }
            if (sort_choice == 1) {
                bubbleSortAscending(sorted_array, student_array_size);
                std::cout << "Копия массива отсортирована по возрастанию ID!\n";
            }
            else if (sort_choice == 2) {
                bubbleSortDescending(sorted_array, student_array_size);
                std::cout << "Копия массива отсортирована по убыванию ID!\n";
            }
            else {
                std::cout << "Неверный выбор!\n";
                delete[] sorted_array;
                return;
            }

            std::cout << "\n=== ОРИГИНАЛЬНЫЙ МАССИВ ===\n";
            for (int i = 0; i < student_array_size; i++) {
                std::cout << i << ": " << students_array[i] << std::endl;
            }

            std::cout << "\n=== ОТСОРТИРОВАННАЯ КОПИЯ ===\n";
            for (int i = 0; i < student_array_size; i++) {
                std::cout << i << ": " << sorted_array[i] << std::endl;
            }
            system("pause");

            delete[] sorted_array;
        }
        else if (type == "vector") {
            if (students_vector.size() < 2) { return; }

            unsigned sort_choice;
            std::cout << "=== СОРТИРОВКА СТУДЕНТОВ (" << type << ") ===\n";
            std::cout << "1 - По возрастанию ID\n";
            std::cout << "2 - По убыванию ID\n";
            std::cout << "Выберите тип сортировки: ";
            number_filteredInput<unsigned>(sort_choice);

            std::vector<bsuir> sorted_vector = students_vector;
            if (sort_choice == 1) {
                std::sort(sorted_vector.begin(), sorted_vector.end(),
                    [](const bsuir& a, const bsuir& b) { return a.GetId() < b.GetId(); });
                std::cout << "Копия вектора отсортирована по возрастанию ID!\n";
            }
            else if (sort_choice == 2) {
                std::sort(sorted_vector.begin(), sorted_vector.end(),
                    [](const bsuir& a, const bsuir& b) { return a.GetId() > b.GetId(); });
                std::cout << "Копия вектора отсортирована по убыванию ID!\n";
            }
            else {
                std::cout << "Неверный выбор!\n";
                return;
            }

            std::cout << "\n=== ОРИГИНАЛЬНЫЙ ВЕКТОР ===\n";
            for (size_t i = 0; i < students_vector.size(); i++) {
                std::cout << i << ": " << students_vector[i] << std::endl;
            }

            std::cout << "\n=== ОТСОРТИРОВАННАЯ КОПИЯ ===\n";
            for (size_t i = 0; i < sorted_vector.size(); i++) {
                std::cout << i << ": " << sorted_vector[i] << std::endl;
            }
            system("pause");

        }
        else if (type == "list") {
            if (students_list.GetSize() < 2) { return; }

            unsigned sort_choice;
            std::cout << "=== СОРТИРОВКА СТУДЕНТОВ (" << type << ") ===\n";
            std::cout << "1 - По возрастанию ID\n";
            std::cout << "2 - По убыванию ID\n";
            std::cout << "Выберите тип сортировки: ";
            number_filteredInput<unsigned>(sort_choice);

            MyList<bsuir> sorted_list;
            for (int i = 0; i < students_list.GetSize(); i++) {
                sorted_list.push_back(students_list[i]);
            }
            if (sort_choice == 1) {
                bubbleSortListAscending(sorted_list);
                std::cout << "Копия списка отсортирована по возрастанию ID!\n";
            }
            else if (sort_choice == 2) {
                bubbleSortListDescending(sorted_list);
                std::cout << "Копия списка отсортирована по убыванию ID!\n";
            }
            else {
                std::cout << "Неверный выбор!\n";
                return;
            }

            std::cout << "\n=== ОРИГИНАЛЬНЫЙ СПИСОК ===\n";
            for (int i = 0; i < students_list.GetSize(); i++) {
                std::cout << i << ": " << students_list[i] << std::endl;
            }

            std::cout << "\n=== ОТСОРТИРОВАННАЯ КОПИЯ ===\n";
            for (int i = 0; i < sorted_list.GetSize(); i++) {
                std::cout << i << ": " << sorted_list[i] << std::endl;
            }
            system("pause");

        }
    }

    void SearchInf(std::string type) override {
        if (type == "array") {
            if (student_array_size == 0) return;
            std::cout << "\n=== ПОИСК СТУДЕНТОВ ===\n";

            unsigned search_id;
            std::cout << "Введите ID студента для поиска: ";
            number_filteredInput<unsigned>(search_id);

            bool found = false;
            for (int i = 0; i < student_array_size; i++) {
                if (students_array[i].GetId() == search_id) {
                    std::cout << "Студент найден!\n";
                    std::cout << students_array[i] << std::endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Студент с ID " << search_id << " не найден!\n";
            }
        }
        else if (type == "vector") {
            if (students_vector.empty()) return;
            std::cout << "\n=== ПОИСК СТУДЕНТОВ ===\n";

            unsigned search_id;
            std::cout << "Введите ID студента для поиска: ";
            number_filteredInput<unsigned>(search_id);

            bool found = false;
            for (size_t i = 0; i < students_vector.size(); i++) {
                if (students_vector[i].GetId() == search_id) {
                    std::cout << "Студент найден!\n";
                    std::cout << students_vector[i] << std::endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Студент с ID " << search_id << " не найден!\n";
            }
        }
        else if (type == "list") {
            if (students_list.GetSize() == 0) return;
            std::cout << "\n=== ПОИСК СТУДЕНТОВ ===\n";

            unsigned search_id;
            std::cout << "Введите ID студента для поиска: ";
            number_filteredInput<unsigned>(search_id);

            bool found = false;
            for (int i = 0; i < students_list.GetSize(); i++) {
                if (students_list[i].GetId() == search_id) {
                    std::cout << "Студент найден!\n";
                    std::cout << students_list[i] << std::endl;
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << "Студент с ID " << search_id << " не найден!\n";
            }
        }

        std::cout << std::endl;
        system("pause");
    }

    void FilterInf(std::string type) override {
        if (type == "array") {
            if (student_array_size == 0) return;
            std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";

            unsigned field_choice;
            std::cout << "Выберите поле для фильтрации:\n";
            std::cout << "1 - ФИО\n";
            std::cout << "2 - Факультет\n";
            std::cout << "3 - Специальность\n";
            std::cout << "Номер действия: ";
            number_filteredInput<unsigned>(field_choice);

            std::string filter_value;
            std::cout << "Введите значение для фильтрации: ";
            std::getline(std::cin, filter_value);

            std::cout << "\n=== РЕЗУЛЬТАТЫ ФИЛЬТРАЦИИ (ARRAY) ===\n";
            bool found = false;
            for (int i = 0; i < student_array_size; i++) {
                bool match = false;
                if (field_choice == 1 && students_array[i].GetFullname().find(filter_value) != std::string::npos) {
                    match = true;
                }
                else if (field_choice == 2 && students_array[i].GetFaculty().find(filter_value) != std::string::npos) {
                    match = true;
                }
                else if (field_choice == 3 && students_array[i].GetMajor().find(filter_value) != std::string::npos) {
                    match = true;
                }

                if (match) {
                    std::cout << students_array[i] << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "Студенты по заданному критерию не найдены!\n";
            }
        }
        else if (type == "vector") {
            if (students_vector.empty()) return;
            std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";

            unsigned field_choice;
            std::cout << "Выберите поле для фильтрации:\n";
            std::cout << "1 - ФИО\n";
            std::cout << "2 - Факультет\n";
            std::cout << "3 - Специальность\n";
            std::cout << "Номер действия: ";
            number_filteredInput<unsigned>(field_choice);

            std::string filter_value;
            std::cout << "Введите значение для фильтрации: ";
            std::getline(std::cin, filter_value);

            std::cout << "\n=== РЕЗУЛЬТАТЫ ФИЛЬТРАЦИИ (VECTOR) ===\n";
            bool found = false;
            for (size_t i = 0; i < students_vector.size(); i++) {
                bool match = false;
                if (field_choice == 1 && students_vector[i].GetFullname().find(filter_value) != std::string::npos) {
                    match = true;
                }
                else if (field_choice == 2 && students_vector[i].GetFaculty().find(filter_value) != std::string::npos) {
                    match = true;
                }
                else if (field_choice == 3 && students_vector[i].GetMajor().find(filter_value) != std::string::npos) {
                    match = true;
                }

                if (match) {
                    std::cout << students_vector[i] << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "Студенты по заданному критерию не найдены!\n";
            }
        }
        else if (type == "list") {
            if (students_list.GetSize() == 0) return;
            std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";

            unsigned field_choice;
            std::cout << "Выберите поле для фильтрации:\n";
            std::cout << "1 - ФИО\n";
            std::cout << "2 - Факультет\n";
            std::cout << "3 - Специальность\n";
            std::cout << "Номер действия: ";
            number_filteredInput<unsigned>(field_choice);

            std::string filter_value;
            std::cout << "Введите значение для фильтрации: ";
            std::getline(std::cin, filter_value);

            std::cout << "\n=== РЕЗУЛЬТАТЫ ФИЛЬТРАЦИИ (LIST) ===\n";
            bool found = false;
            for (int i = 0; i < students_list.GetSize(); i++) {
                bool match = false;
                if (field_choice == 1 && students_list[i].GetFullname().find(filter_value) != std::string::npos) {
                    match = true;
                }
                else if (field_choice == 2 && students_list[i].GetFaculty().find(filter_value) != std::string::npos) {
                    match = true;
                }
                else if (field_choice == 3 && students_list[i].GetMajor().find(filter_value) != std::string::npos) {
                    match = true;
                }

                if (match) {
                    std::cout << students_list[i] << std::endl;
                    found = true;
                }
            }

            if (!found) {
                std::cout << "Студенты по заданному критерию не найдены!\n";
            }
        }

        std::cout << std::endl;
        system("pause");
    }

private:
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
    void swap(bsuir& a, bsuir& b) {
        bsuir temp = a;
        a = b;
        b = temp;
    }
    void bubbleSortAscending(bsuir* arr, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j].GetId() > arr[j + 1].GetId()) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    void bubbleSortDescending(bsuir* arr, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j].GetId() < arr[j + 1].GetId()) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
    void bubbleSortListAscending(MyList<bsuir>& list) {
        int n = list.GetSize();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (list[j].GetId() > list[j + 1].GetId()) {
                    bsuir temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }
    }
    void bubbleSortListDescending(MyList<bsuir>& list) {
        int n = list.GetSize();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (list[j].GetId() < list[j + 1].GetId()) {
                    bsuir temp = list[j];
                    list[j] = list[j + 1];
                    list[j + 1] = temp;
                }
            }
        }
    }
};
int bsuir::count = 0;
bsuir* bsuir::students_array = nullptr;
int bsuir::student_array_size = 0;
std::vector<bsuir> bsuir::students_vector;
MyList<bsuir> bsuir::students_list;