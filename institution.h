#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include "input_check.h"
#include "threads_options.h"

#include "lab3_array_vector_list.h"
#include "lab4_map_set_hashtable.h"
#include "lab5_queue_stack_priorityqueue.h"

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
    virtual void addFileInfo(std::string type) = 0;
    virtual ~institution() = 0;
};
institution::~institution() {}

class bsuir : public institution {
private:
    std::string fullname;
    std::string faculty;
    std::string major;
    int id;
    static int count;
    //lab3
    static bsuir* students_array;
    static int student_array_size;
    static std::vector<bsuir> students_vector;
    static MyList<bsuir> students_list;
    //lab4
    static BinaryTree<int> students_set;
    static BinaryTree<int> students_multiset;
    static BinaryTreeMap<int, std::string> students_map;
    static BinaryTreeMap<int, std::string> students_multimap;
    static unordered_map<int, bsuir> students_unordered_map;
    //lab5
    static Queue<bsuir> students_queue;
    static Queue<bsuir> students_priority_queue;
    static Stack<bsuir> students_stack;
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

    void addFileInfo(std::string type) {
        std::ofstream os("MyFILE.txt", std::ios::trunc);

        if (type == "queue") {
            if (students_queue.empty()) return;

            os << "=== QUEUE ===" << std::endl;
            for (size_t i = 0; i < students_queue.getSize(); i++) {
                os << students_queue[i] << std::endl;
            }
        }
        else if (type == "priority_queue") {
            if (students_priority_queue.empty()) return;

            os << "=== PRIORITY_QUEUE ===" << std::endl;
            for (int i = 0; i < students_priority_queue.getSize(); i++) {
                int priority = students_priority_queue.getPriority(i);
                os << i << ": " << students_priority_queue[i] << " [Приоритет: " << priority << "]" << std::endl;
            }
        }
        if (type == "stack") {
            if (students_stack.empty()) return;

            os << "=== STACK ===" << std::endl;
            for (size_t i = 0; i < students_stack.GetSize(); i++) {
                os << students_stack[i] << std::endl;
            }
        }

        std::cout << "Добавляем в файл";
        loadingImitation();
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
        else if (type == "set") {
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ ЭЛЕМЕНТА В SET ===\n";

                unsigned key;
                std::cout << "Введите порядковый номер студента для добавления в дерево: ";
                number_filteredInput<unsigned>(key);

                if (students_set.contains(key)) {
                    std::cout << "Элемент " << key << " уже существует в дереве!\n";
                }
                else {
                    students_set.insert(key);
                    std::cout << "Элемент " << key << " успешно добавлен в дерево!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить добавление\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(add_final_choice);
                    std::cout << std::endl;

                    if (add_final_choice == 1) {
                        break;
                    }
                    else if (add_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (add_final_choice != 2);
        }
        else if (type == "multiset") {
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ ЭЛЕМЕНТА В MULTISET ===\n";

                unsigned key;
                std::cout << "Введите порядковый номер студента для добавления в дерево: ";
                number_filteredInput<unsigned>(key);

                students_multiset.insert(key);
                std::cout << "Элемент " << key << " успешно добавлен в дерево!\n";

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить добавление\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(add_final_choice);
                    std::cout << std::endl;

                    if (add_final_choice == 1) {
                        break;
                    }
                    else if (add_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (add_final_choice != 2);
        }
        else if (type == "map") {
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ ЭЛЕМЕНТА В MAP ===\n";

                unsigned key;
                std::string value;

                std::cout << "Введите ключ: ";
                number_filteredInput<unsigned>(key);

                if (students_map.contains(key)) {
                    std::cout << "Элемент " << key << " уже существует!\n";
                }
                else {
                    std::cout << "Введите значение (Фамилия студента): ";
                    letter_filteredInput<std::string>(value, 0, 1);

                    students_map.insert(key, value);
                    std::cout << "Элемент " << key << " : " << value << " успешно добавлен в map!\n";
                }
                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить добавление\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(add_final_choice);
                    std::cout << std::endl;

                    if (add_final_choice == 1) {
                        break;
                    }
                    else if (add_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (add_final_choice != 2);
        }
        else if (type == "multimap") {
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ ЭЛЕМЕНТА В MULTIMAP ===\n";

                unsigned key;
                std::string value;

                std::cout << "Введите ключ: ";
                number_filteredInput<unsigned>(key);

                std::cout << "Введите значение (Фамилия студента): ";
                letter_filteredInput<std::string>(value, 0, 1);

                students_multimap.insert(key, value);
                std::cout << "Элемент " << key << " : " << value << " успешно добавлен в map!\n";
                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить добавление\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(add_final_choice);
                    std::cout << std::endl;

                    if (add_final_choice == 1) {
                        break;
                    }
                    else if (add_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (add_final_choice != 2);

        }
        else if (type == "unordered_map") {
            unsigned students_to_add;
            std::cout << "Введите количество студентов, которое вы хотите добавить: ";
            number_filteredInput<unsigned>(students_to_add);

            for (int i = 0; i < students_to_add; i++) {
                std::cout << "\n=== ДОБАВЛЕНИЕ СТУДЕНТА " << (i + 1) << " (UNORDERED_MAP) ===\n\n";

                bsuir newStudent;
                std::cin >> newStudent;

                count++;
                newStudent.SetId(count);

                students_unordered_map.insert(newStudent.GetId(), newStudent);

                std::cout << "Студент добавлен успешно! ID: " << newStudent.GetId() << "\n";
            }

            std::cout << std::endl;
            system("pause");
        }
        else if (type == "queue") {
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ СТУДЕНТА (QUEUE) ===\n";

                bsuir newStudent;
                std::cin >> newStudent;

                count++;
                newStudent.SetId(count);

                students_queue.enqueue(newStudent);
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
                        ShowInf("queue");
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
        else if (type == "priority_queue") {
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ СТУДЕНТА (PRIORITY_QUEUE) ===\n";

                bsuir newStudent;
                std::cin >> newStudent;

                count++;
                newStudent.SetId(count);

                int priority;
                bool priority_flag = false;
                do {
                    std::cout << "Введите приоритет студента [1-3]: ";
                    number_filteredInput<int>(priority);
                    if (priority > 0 && priority <= 3) {
                        priority_flag = true;
                    }
                    else {
                        std::cout << "Некорректное значение!\n";
                    }
                } while (!priority_flag);


                students_priority_queue.enqueue(newStudent, priority);
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
                        ShowInf("priority_queue");
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
        else if (type == "stack") {
            unsigned add_final_choice;

            do {
                std::cout << "=== ДОБАВЛЕНИЕ СТУДЕНТА (STACK) ===\n";

                bsuir newStudent;
                std::cin >> newStudent;

                count++;
                newStudent.SetId(count);

                students_stack.push_front(newStudent);
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
                        ShowInf("stack");
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
        else if (type == "set") {
            if (students_set.empty()) {
                std::cout << "Дерево пустое! Нечего удалять.\n";
                system("pause");
                return;
            }

            unsigned del_final_choice;

            do {
                std::cout << "=== УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ SET ===\n";
                students_set.printTree();

                unsigned key_to_delete;
                std::cout << "Введите число для удаления: ";
                number_filteredInput<unsigned>(key_to_delete);

                if (students_set.erase(key_to_delete)) {
                    std::cout << "Элемент " << key_to_delete << " успешно удален из дерева!\n";
                }
                else {
                    std::cout << "Элемент " << key_to_delete << " не найден в дереве!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать обновленное дерево\n";
                    std::cout << "2 - Продолжить удаление\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(del_final_choice);
                    std::cout << std::endl;

                    if (del_final_choice == 1) {
                        students_set.printTree();
                        if (students_set.empty()) {
                            std::cout << "Дерево теперь пустое!\n";
                        }
                    }
                    else if (del_final_choice == 2) {
                        break;
                    }
                    else if (del_final_choice == 3) {
                        break;
                    }
                } while (del_final_choice == 1);

            } while (del_final_choice != 3);
        }
        else if (type == "multiset") {
            if (students_multiset.empty()) {
                std::cout << "Дерево пустое! Нечего удалять.\n";
                system("pause");
                return;
            }

            unsigned del_final_choice;

            do {
                std::cout << "=== УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ MULTISET ===\n";
                students_multiset.printTree();

                unsigned key_to_delete;
                std::cout << "Введите число для удаления: ";
                number_filteredInput<unsigned>(key_to_delete);

                if (students_multiset.multiset_erase(key_to_delete)) {
                    std::cout << "Элемент " << key_to_delete << " успешно удален из multiset!\n";
                }
                else {
                    std::cout << "Элемент " << key_to_delete << " не найден в multiset!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать обновленное дерево\n";
                    std::cout << "2 - Продолжить удаление\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(del_final_choice);
                    std::cout << std::endl;

                    if (del_final_choice == 1) {
                        students_multiset.printTree();
                        if (students_multiset.empty()) {
                            std::cout << "Multiset теперь пустой!\n";
                        }
                    }
                    else if (del_final_choice == 2) {
                        break;
                    }
                    else if (del_final_choice == 3) {
                        break;
                    }
                } while (del_final_choice == 1);

            } while (del_final_choice != 3);
        }
        else if (type == "map") {
            if (students_map.empty()) {
                std::cout << "Map пустой! Нечего удалять.\n";
                system("pause");
                return;
            }

            unsigned del_final_choice;

            do {
                std::cout << "=== УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ MAP ===\n";
                students_map.printMap();

                int key_to_delete;
                std::cout << "\nВведите ключ для удаления: ";
                number_filteredInput<int>(key_to_delete);

                if (students_map.erase(key_to_delete)) {
                    std::cout << "Элемент с ключом " << key_to_delete << " успешно удален из map!\n";
                }
                else {
                    std::cout << "Элемент с ключом " << key_to_delete << " не найден в map!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать обновленный map\n";
                    std::cout << "2 - Продолжить удаление\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(del_final_choice);
                    std::cout << std::endl;

                    if (del_final_choice == 1) {
                        students_map.printMap();
                    }
                    else if (del_final_choice == 2) {
                        break;
                    }
                    else if (del_final_choice == 3) {
                        break;
                    }
                } while (true);

            } while (del_final_choice != 3);
        }
        else if (type == "multimap") {
            if (students_multimap.empty()) {
                std::cout << "Map пустой! Нечего удалять.\n";
                system("pause");
                return;
            }

            unsigned del_final_choice;

            do {
                std::cout << "=== УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ MAP ===\n";
                students_multimap.printMap();

                int key_to_delete;
                std::cout << "\nВведите ключ для удаления: ";
                number_filteredInput<int>(key_to_delete);

                if (students_multimap.erase(key_to_delete)) {
                    std::cout << "Элемент с ключом " << key_to_delete << " успешно удален из map!\n";
                }
                else {
                    std::cout << "Элемент с ключом " << key_to_delete << " не найден в map!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать обновленный map\n";
                    std::cout << "2 - Продолжить удаление\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(del_final_choice);
                    std::cout << std::endl;

                    if (del_final_choice == 1) {
                        students_multimap.printMap();
                    }
                    else if (del_final_choice == 2) {
                        break;
                    }
                    else if (del_final_choice == 3) {
                        break;
                    }
                } while (true);

            } while (del_final_choice != 3);
            }
        else if (type == "unordered_map") {
            std::cout << "\n=== УДАЛЕНИЕ ИЗ UNORDERED_MAP ===\n";

            if (students_unordered_map.empty()) {
                std::cout << "Unordered_map пуст!\n";
                return;
            }

            unsigned delete_choice;
            std::cout << "Выберите действие:\n";
            std::cout << "1 - Удалить по ID\n";
            std::cout << "2 - Очистить весь unordered_map\n";
            std::cout << "Номер действия: ";
            number_filteredInput<unsigned>(delete_choice);

            if (delete_choice == 1) {
                int id_to_delete;
                std::cout << "Введите ID студента для удаления: ";
                number_filteredInput<int>(id_to_delete);

                if (students_unordered_map.erase(id_to_delete)) {
                    std::cout << "Студент с ID " << id_to_delete << " удален!\n";
                }
                else {
                    std::cout << "Студент с ID " << id_to_delete << " не найден!\n";
                }
            }
            else if (delete_choice == 2) {
                students_unordered_map.clear();
                std::cout << "Unordered_map полностью очищен!\n";
            }
            else {
                std::cout << "Неверный выбор!\n";
            }
        }
        else if (type == "queue") {
            if (students_queue.empty()) {
                std::cout << "Очередь пуста!\n";
                system("pause");
                return;
            }

            unsigned del_choice;
            unsigned del_final_choice;

            do {
                std::cout << "\n=== УДАЛЕНИЕ ИЗ QUEUE ===\n";
                ShowInf("queue");

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Удалить 1 элемент\n";
                std::cout << "2 - Удалить всю очередь\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(del_choice);

                if (del_choice == 1) {
                    students_queue.dequeue();
                    std::cout << "Студент удален из очереди!\n";
                }
                else if (del_choice == 2) {
                    students_queue.clear();
                    std::cout << "Очередь полностью удалена!\n";
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                if (students_queue.empty()) {
                    system("pause");
                    std::cout << "Очередь пуста!\n";
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
        else if (type == "priority_queue") {
            if (students_priority_queue.empty()) {
                std::cout << "Очередь с приоритетом пуста!\n";
                system("pause");
                return;
            }

            unsigned del_choice;
            unsigned del_final_choice;

            do {
                std::cout << "\n=== УДАЛЕНИЕ ИЗ PRIORITY_QUEUE ===\n";
                ShowInf("priority_queue");

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Удалить 1 элемент\n";
                std::cout << "2 - Удалить всю очередь\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(del_choice);

                if (del_choice == 1) {
                    students_priority_queue.dequeue();
                    std::cout << "Студент удален из очереди с приоритетом!\n";
                }
                else if (del_choice == 2) {
                    students_priority_queue.clear();
                    std::cout << "Очередь с приоритетом полностью удалена!\n";
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                if (students_priority_queue.empty()) {
                    system("pause");
                    std::cout << "Очередь с приоритетом пуста!\n";
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
        else if (type == "stack") {
            if (students_stack.empty()) {
                std::cout << "Очередь с приоритетом пуста!\n";
                system("pause");
                return;
            }

            unsigned del_choice;
            unsigned del_final_choice;

            do {
                std::cout << "\n=== УДАЛЕНИЕ ИЗ STACK ===\n";
                ShowInf("stack");

                std::cout << "\nВыберите действие:\n";
                std::cout << "1 - Удалить 1 элемент\n";
                std::cout << "2 - Удалить весь stack\n";

                std::cout << "Номер действия: ";
                number_filteredInput<unsigned>(del_choice);

                if (del_choice == 1) {
                    students_stack.pop_front();
                    std::cout << "Студент удален!\n";
                }
                else if (del_choice == 2) {
                    students_stack.clear();
                    std::cout << "Stack полностью удален!\n";
                }
                else {
                    std::cout << "Неверный выбор!\n";
                }

                if (students_stack.empty()) {
                    system("pause");
                    std::cout << "Stack пуст!\n";
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
        else if (type == "map") {
            if (students_map.empty()) {
                std::cout << "Map пустой!\n";
                system("pause");
                return;
            }

            unsigned change_final_choice;

            do {
                std::cout << "=== ИЗМЕНЕНИЕ ЗНАЧЕНИЯ В MAP ===\n";
                students_map.printMap();

                int key;
                std::string new_value;

                std::cout << "\nВведите ключ для изменения: ";
                number_filteredInput<int>(key);


                if (students_map.contains(key)) {
                    std::cout << "Введите новое значение: ";
                    letter_filteredInput<std::string>(new_value, 0, 1);
                }

                if (students_map.update(key, new_value)) {
                    std::cout << "Значение для ключа " << key << " успешно обновлено!\n";
                }
                else {
                    std::cout << "Ключ " << key << " не найден в map!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать обновленный map\n";
                    std::cout << "2 - Продолжить изменение\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(change_final_choice);
                    std::cout << std::endl;

                    if (change_final_choice == 1) {
                        students_map.printMap();
                    }
                    else if (change_final_choice == 2) {
                        break;
                    }
                    else if (change_final_choice == 3) {
                        break;
                    }
                } while (true);

            } while (change_final_choice != 3);
        }
        else if (type == "multimap") {
            if (students_multimap.empty()) {
                std::cout << "MultiMap пустой!\n";
                system("pause");
                return;
            }

            unsigned change_final_choice;

            do {
                std::cout << "=== ИЗМЕНЕНИЕ ЗНАЧЕНИЯ В MULTIMAP ===\n";
                students_multimap.printMap();

                int key;
                std::string old_value, new_value;

                std::cout << "\nВведите ключ для изменения: ";
                number_filteredInput<int>(key);

                students_multimap.findAndPrint(key);

                std::cout << "Введите старое значение, которое нужно изменить: ";
                letter_filteredInput<std::string>(old_value);

                std::cout << "Введите новое значение: ";
                std::getline(std::cin, new_value);

                if (students_multimap.update(key, old_value, new_value)) {
                    std::cout << "Значение для ключа " << key << " успешно изменено!\n";
                    std::cout << "Было: " << old_value << " -> Стало: " << new_value << std::endl;
                }
                else {
                    std::cout << "Ключ " << key << " со значением '" << old_value << "' не найден в multimap!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Показать обновленный multimap\n";
                    std::cout << "2 - Продолжить изменение\n";
                    std::cout << "3 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(change_final_choice);
                    std::cout << std::endl;

                    if (change_final_choice == 1) {
                        students_multimap.printMap();
                    }
                    else if (change_final_choice == 2) {
                        break;
                    }
                    else if (change_final_choice == 3) {
                        break;
                    }
                } while (true);

            } while (change_final_choice != 3);
        }
        else if (type == "unordered_map") {
            std::cout << "\n=== РЕДАКТИРОВАНИЕ В UNORDERED_MAP ===\n";

            if (students_unordered_map.empty()) {
                std::cout << "Unordered_map пуст!\n";
                return;
            }

            unsigned change_final_choice;

            do {
                students_unordered_map.printAll();

                int id_to_change;
                std::cout << "Введите ID студента для редактирования: ";
                number_filteredInput<int>(id_to_change);

                auto node = students_unordered_map.find(id_to_change);
                if (node) {
                    std::cout << "Найден студент:\n";
                    std::cout << node->value << std::endl;

                    bsuir updatedStudent;
                    std::cout << "\nВведите новые данные:\n";
                    std::cin >> updatedStudent;
                    updatedStudent.SetId(id_to_change);

                    students_unordered_map.insert(id_to_change, updatedStudent);

                    std::cout << "Информация изменена успешно!\n";
                    std::cout << "Обновленные данные: " << updatedStudent << std::endl;
                }
                else {
                    std::cout << "Студент с ID " << id_to_change << " не найден!\n";
                }

                do {
                    std::cout << "\nВыберите действие:\n";
                    std::cout << "1 - Продолжить редактирование\n";
                    std::cout << "2 - Выйти\n";

                    std::cout << "Номер действия: ";
                    number_filteredInput<unsigned>(change_final_choice);

                    if (change_final_choice == 1 || change_final_choice == 2) {
                        break;
                    }
                } while (true);

            } while (change_final_choice == 1);
        }
        else if (type == "queue") {
            if (students_queue.getSize() == 0) return;

            unsigned change_id;
            unsigned change_final_choice;

            do {
                std::cout << "=== ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА (QUEUE) ===\n";
                ShowInf("queue");

                std::cout << "Введите ID студента: ";
                number_filteredInput<unsigned>(change_id);

                int found_index = -1;
                for (int i = 0; i < students_queue.getSize(); i++) {
                    if (students_queue[i].GetId() == change_id) {
                        found_index = i;
                        break;
                    }
                }

                if (found_index == -1) {
                    std::cout << "\nСтудент с ID " << change_id << " не найден!\n";
                }
                else {
                    std::cout << "\nНайден студент: " << students_queue[found_index] << std::endl;

                    bsuir updatedStudent;
                    std::cout << "\nВведите новые данные:\n";
                    std::cin >> updatedStudent;
                    updatedStudent.SetId(change_id);
                    students_queue[found_index] = updatedStudent;

                    std::cout << "Информация изменена успешно!\n";
                    std::cout << "Обновленные данные: " << students_queue[found_index] << std::endl;
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
        else if (type == "stack") {
            if (students_stack.empty()) {
                std::cout << "Стек пуст!\n";
                return;
            }

            unsigned change_final_choice;

            do {
                std::cout << "=== ИЗМЕНЕНИЕ ДАННЫХ СТУДЕНТА (STACK) ===\n";
                ShowInf("stack");

                bsuir updatedStudent;
                std::cout << "\nВведите новые данные для изменения верхнего элемента:\n";
                std::cin >> updatedStudent;
                updatedStudent.SetId(0);

                students_stack[0] = updatedStudent;

                std::cout << "Информация изменена успешно!\n";
                std::cout << "Обновленные данные: " << students_stack[0] << std::endl;

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
        else if (type == "set") {
            if (students_set.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (SET) ===\n";
            students_set.printTree();
            std::cout << std::endl;
            system("pause");
        }
        else if (type == "multiset") {
            if (students_multiset.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (MULTISET) ===\n";
            students_multiset.printTree();
            std::cout << std::endl;
            system("pause");
        }
        else if (type == "map") {
            if (students_map.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (MAP) ===\n";
            students_map.printMap();
            std::cout << std::endl;
            system("pause");
        }
        else if (type == "multimap") {
            if (students_multimap.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (MULTIMAP) ===\n";
            students_multimap.printMap();
            std::cout << std::endl;
            system("pause");
        }
        else if (type == "unordered_map") {
            std::cout << "\n=== UNORDERED_MAP СТУДЕНТОВ ===\n";
            std::cout << "Размер: " << students_unordered_map.size() << " элементов\n\n";

            if (students_unordered_map.empty()) {
                std::cout << "Unordered_map пуст!\n";
            }
            else {
                students_unordered_map.printAll();

                std::cout << "\n=== СТРУКТУРА ХЕШ-ТАБЛИЦЫ ===\n";
                students_unordered_map.printTable();
            }
        }
        else if (type == "queue") {
            if (students_queue.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (QUEUE) ===\n";
            for (size_t i = 0; i < students_queue.getSize(); i++) {
                std::cout << i << ": " << students_queue[i] << std::endl;
            }
        }
        else if (type == "priority_queue") {
            if (students_priority_queue.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (PRIORITY_QUEUE) ===\n";
            for (int i = 0; i < students_priority_queue.getSize(); i++) {
                int priority = students_priority_queue.getPriority(i);
                std::cout << i << ": " << students_priority_queue[i] << " [Приоритет: " << priority << "]" << std::endl;
            }
        }
        else if (type == "stack") {
            if (students_stack.empty()) return;

            std::cout << "\n=== СПИСОК СТУДЕНТОВ (STACK) ===\n";
            for (size_t i = 0; i < students_stack.GetSize(); i++) {
                std::cout << i << ": " << students_stack[i] << std::endl;
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
        else if (type == "unordered_map") {
            std::cout << "\n=== СОРТИРОВКА UNORDERED_MAP ===\n";

            if (students_unordered_map.empty()) {
                std::cout << "Unordered_map пуст!\n";
                system("pause");
                return;
            }

            unsigned sort_choice;
            std::cout << "Выберите тип сортировки:\n";
            std::cout << "1 - По возрастанию ID\n";
            std::cout << "2 - По убыванию ID\n";
            std::cout << "3 - По ФИО (алфавитный порядок)\n";
            std::cout << "4 - По факультету (алфавитный порядок)\n";
            std::cout << "Номер действия: ";
            number_filteredInput<unsigned>(sort_choice);

            auto keys = students_unordered_map.getKeys();

            std::vector<std::pair<int, bsuir>> sorted_elements;
            for (int key : keys) {
                auto node = students_unordered_map.find(key);
                if (node) {
                    sorted_elements.push_back({ key, node->value });
                }
            }

            if (sort_choice == 1) {
                for (size_t i = 0; i < sorted_elements.size() - 1; i++) {
                    for (size_t j = 0; j < sorted_elements.size() - i - 1; j++) {
                        if (sorted_elements[j].first > sorted_elements[j + 1].first) {
                            std::swap(sorted_elements[j], sorted_elements[j + 1]);
                        }
                    }
                }
                std::cout << "Элементы отсортированы по возрастанию ID!\n";
            }
            else if (sort_choice == 2) {
                for (size_t i = 0; i < sorted_elements.size() - 1; i++) {
                    for (size_t j = 0; j < sorted_elements.size() - i - 1; j++) {
                        if (sorted_elements[j].first < sorted_elements[j + 1].first) {
                            std::swap(sorted_elements[j], sorted_elements[j + 1]);
                        }
                    }
                }
                std::cout << "Элементы отсортированы по убыванию ID!\n";
            }
            else if (sort_choice == 3) {
                for (size_t i = 0; i < sorted_elements.size() - 1; i++) {
                    for (size_t j = 0; j < sorted_elements.size() - i - 1; j++) {
                        if (sorted_elements[j].second.GetFullname() > sorted_elements[j + 1].second.GetFullname()) {
                            std::swap(sorted_elements[j], sorted_elements[j + 1]);
                        }
                    }
                }
                std::cout << "Элементы отсортированы по ФИО (алфавитный порядок)!\n";
            }
            else if (sort_choice == 4) {
                for (size_t i = 0; i < sorted_elements.size() - 1; i++) {
                    for (size_t j = 0; j < sorted_elements.size() - i - 1; j++) {
                        if (sorted_elements[j].second.GetFaculty() > sorted_elements[j + 1].second.GetFaculty()) {
                            std::swap(sorted_elements[j], sorted_elements[j + 1]);
                        }
                    }
                }
                std::cout << "Элементы отсортированы по факультету (алфавитный порядок)!\n";
            }
            else {
                std::cout << "Неверный выбор!\n";
                return;
            }
            std::cout << "\n=== ОТСОРТИРОВАННЫЕ ЭЛЕМЕНТЫ ===\n";
            for (size_t i = 0; i < sorted_elements.size(); i++) {
                std::cout << i + 1 << ". " << sorted_elements[i].second << std::endl;
            }
            std::cout << "\n=== ОРИГИНАЛЬНЫЙ UNORDERED_MAP (не отсортирован) ===\n";
            students_unordered_map.printAll();
            system("pause");

        }
        else if (type == "queue") {
            if (students_queue.getSize() < 2) {
                std::cout << "В очереди недостаточно элементов для сортировки!\n";
                system("pause");
                return;
            }

            std::cout << "=== СОРТИРОВКА ОЧЕРЕДИ ===\n";
            std::cout << "По убыванию ID\n";

            std::cout << "\n=== ИСХОДНАЯ ОЧЕРЕДЬ ===\n";
            ShowInf("queue");

            std::vector<bsuir> elements;
            for (size_t i = 0; i < students_queue.getSize(); i++) {
                elements.push_back(students_queue[i]);
            }
            std::sort(elements.begin(), elements.end(),
                [](const bsuir& a, const bsuir& b) { return a.GetId() > b.GetId(); });

            std::cout << "\n=== ОТСОРТИРОВАННАЯ КОПИЯ ===\n";
            for (size_t i = 0; i < elements.size(); i++) {
                std::cout << i << ": " << elements[i] << std::endl;
            }
            system("pause");
        }
        else if (type == "priority_queue") {
            if (students_priority_queue.getSize() < 2) {
                std::cout << "В очереди с приоритетом недостаточно элементов для сортировки!\n";
                system("pause");
                return;
            }

            std::cout << "=== СОРТИРОВКА ОЧЕРЕДИ С ПРИОРИТЕТОМ ===\n";
            std::cout << "По убыванию ID (приоритет не учитывается)\n";

            std::cout << "\n=== ИСХОДНАЯ ОЧЕРЕДЬ С ПРИОРИТЕТОМ ===\n";
            ShowInf("priority_queue");

            std::vector<bsuir> elements;
            for (int i = 0; i < students_priority_queue.getSize(); i++) {
                elements.push_back(students_priority_queue[i]);
            }

            std::sort(elements.begin(), elements.end(),
                [](const bsuir& a, const bsuir& b) { return a.GetId() > b.GetId(); });

            std::cout << "\n=== ОТСОРТИРОВАННАЯ КОПИЯ ===\n";
            for (size_t i = 0; i < elements.size(); i++) {
                std::cout << i << ": " << elements[i] << std::endl;
            }
            system("pause");
        }
        else if (type == "stack") {
            if (students_stack.GetSize() < 2) {
                std::cout << "В стеке недостаточно элементов для сортировки!\n";
                system("pause");
                return;
            }

            std::cout << "=== СОРТИРОВКА СТЕКА ===\n";
            std::cout << "По возрастанию ID\n";

            std::cout << "\n=== ИСХОДНЫЙ СТЕК ===\n";
            ShowInf("stack");

            std::vector<bsuir> elements;
            for (size_t i = 0; i < students_stack.GetSize(); i++) {
                elements.push_back(students_stack[i]);
            }

            std::sort(elements.begin(), elements.end(),
                [](const bsuir& a, const bsuir& b) { return a.GetId() < b.GetId(); });

            std::cout << "\n=== ОТСОРТИРОВАННАЯ КОПИЯ ===\n";
            for (size_t i = 0; i < elements.size(); i++) {
                std::cout << i << ": " << elements[i] << std::endl;
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
        else if (type == "set") {
            if (students_set.empty()) {
                std::cout << "Set пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ПОИСК В SET ===\n";
            students_set.printTree();

            int search_key;
            std::cout << "Введите число для поиска: ";
            number_filteredInput<int>(search_key);

            if (students_set.find(search_key)) {
                std::cout << "Элемент " << search_key << " найден в set!\n";
            }
            else {
                std::cout << "Элемент " << search_key << " не найден в set!\n";
            }
            system("pause");
        }
        else if (type == "multiset") { 
            if (students_multiset.empty()) {
                std::cout << "Multiset пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ПОИСК В MULTISET ===\n";
            students_multiset.printTree();

            int search_key;
            std::cout << "Введите число для поиска: ";
            number_filteredInput<int>(search_key);

            if (students_multiset.find(search_key)) {
                std::cout << "Элемент " << search_key << " найден в multiset!\n";
            }
            else {
                std::cout << "Элемент " << search_key << " не найден в multiset!\n";
            }
        }
        else if (type == "map") {
            if (students_map.empty()) {
                std::cout << "Map пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ПОИСК В MAP ===\n";
            std::cout << "Поиск по ключу:\n";

            int search_key;
            std::cout << "Введите ключ для поиска: ";
            number_filteredInput<int>(search_key);
            students_map.findAndPrint(search_key);
            system("pause");
        }
        else if (type == "multimap") {
            if (students_multimap.empty()) {
                std::cout << "MultiMap пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ПОИСК В MULTIMAP ===\n";
            std::cout << "Поиск по ключу:\n";

            int search_key;
            std::cout << "Введите ключ для поиска: ";
            number_filteredInput<int>(search_key);
            students_multimap.findAndPrint(search_key);
            system("pause");
    }
    if (type == "unordered_map") {
        std::cout << "\n=== ПОИСК В UNORDERED_MAP ===\n";

        if (students_unordered_map.empty()) {
            std::cout << "Unordered_map пуст!\n";
            return;
        }

        int id_to_find;
        std::cout << "Введите ID студента для поиска: ";
        number_filteredInput<int>(id_to_find);

        auto node = students_unordered_map.find(id_to_find);
        if (node) {
            std::cout << "Студент найден:\n";
            std::cout << node->value << std::endl;
        }
        else {
            std::cout << "Студент с ID " << id_to_find << " не найден!\n";
        }
        system("pause");
    }
    if (type == "queue") {
        if (students_queue.empty()) return;
        std::cout << "\n=== ПОИСК СТУДЕНТОВ ===\n";

        unsigned search_id;
        std::cout << "Введите ID студента для поиска: ";
        number_filteredInput<unsigned>(search_id);

        bool found = false;
        for (int i = 0; i < students_queue.getSize(); i++) {
            if (students_queue[i].GetId() == search_id) {
                std::cout << "Студент найден!\n";
                std::cout << students_queue[i] << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Студент с ID " << search_id << " не найден!\n";
        }
        system("pause");
    }
    if (type == "priority_queue") {
        if (students_priority_queue.empty()) return;
        std::cout << "\n=== ПОИСК СТУДЕНТОВ ===\n";

        unsigned search_id;
        std::cout << "Введите ID студента для поиска: ";
        number_filteredInput<unsigned>(search_id);

        bool found = false;
        for (int i = 0; i < students_priority_queue.getSize(); i++) {
            if (students_priority_queue[i].GetId() == search_id) {
                std::cout << "Студент найден!\n";
                std::cout << students_priority_queue[i] << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Студент с ID " << search_id << " не найден!\n";
        }
        system("pause");
    }
    if (type == "stack") {
        if (students_stack.empty()) return;
        std::cout << "\n=== ПОИСК СТУДЕНТОВ ===\n";

        unsigned search_id;
        std::cout << "Введите ID студента для поиска: ";
        number_filteredInput<unsigned>(search_id);

        bool found = false;
        for (int i = 0; i < students_stack.GetSize(); i++) {
            if (students_stack[i].GetId() == search_id) {
                std::cout << "Студент найден!\n";
                std::cout << students_stack[i] << std::endl;
                found = true;
                break;
            }
        }

        if (!found) {
            std::cout << "Студент с ID " << search_id << " не найден!\n";
        }
        system("pause");
    }
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
        if (type == "set") {
            if (students_set.empty()) {
                std::cout << "Set пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ФИЛЬТРАЦИЯ SET ===\n";

            int min_val, max_val;
            std::cout << "Введите минимальное значение: ";
            number_filteredInput<int>(min_val);
            std::cout << "Введите максимальное значение: ";
            number_filteredInput<int>(max_val);

            auto filtered = students_set.filterRange(min_val, max_val);
            if (filtered.empty()) {
                std::cout << "Элементы в диапазоне [" << min_val << ", " << max_val << "] не найдены!\n";
            }
            else {
                std::cout << "Элементы в диапазоне [" << min_val << ", " << max_val << "]: ";
                for (size_t i = 0; i < filtered.size(); i++) {
                    std::cout << filtered[i];
                    if (i < filtered.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
        }
        else if (type == "multiset") {
            if (students_multiset.empty()) {
                std::cout << "Multiset пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ФИЛЬТРАЦИЯ MULTISET ===\n";

            int min_val, max_val;
            std::cout << "Введите минимальное значение: ";
            number_filteredInput<int>(min_val);
            std::cout << "Введите максимальное значение: ";
            number_filteredInput<int>(max_val);

            auto filtered = students_multiset.filterRange(min_val, max_val);
            if (filtered.empty()) {
                std::cout << "Элементы в диапазоне [" << min_val << ", " << max_val << "] не найдены!\n";
            }
            else {
                std::cout << "Элементы в диапазоне [" << min_val << ", " << max_val << "]: ";
                for (size_t i = 0; i < filtered.size(); i++) {
                    std::cout << filtered[i];
                    if (i < filtered.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
        }
        else if (type == "map") {
            if (students_map.empty()) {
                std::cout << "Map пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ФИЛЬТРАЦИЯ MAP ===\n";

            int min_key, max_key;
            std::cout << "Введите минимальный ключ: ";
            number_filteredInput<int>(min_key);
            std::cout << "Введите максимальный ключ: ";
            number_filteredInput<int>(max_key);

            auto filtered = students_map.filterByKeyRange(min_key, max_key);
            if (filtered.empty()) {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "] не найдены!\n";
            }
            else {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "]:\n";
                for (const auto& pair : filtered) {
                    std::cout << pair.first << " : " << pair.second << std::endl;
                }
            }
        }
        else if (type == "multimap") {
            if (students_multimap.empty()) {
                std::cout << "MultiMap пустой!\n";
                system("pause");
                return;
            }

            std::cout << "=== ФИЛЬТРАЦИЯ MULTIMAP ===\n";

            int min_key, max_key;
            std::cout << "Введите минимальный ключ: ";
            number_filteredInput<int>(min_key);
            std::cout << "Введите максимальный ключ: ";
            number_filteredInput<int>(max_key);

            auto filtered = students_multimap.filterByKeyRange(min_key, max_key);
            if (filtered.empty()) {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "] не найдены!\n";
            }
            else {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "]:\n";
                for (const auto& pair : filtered) {
                    std::cout << pair.first << " : " << pair.second << std::endl;
                }
            }
        }
        else if (type == "unordered_map") {
            std::cout << "\n=== ФИЛЬТРАЦИЯ UNORDERED_MAP ===\n";

            if (students_unordered_map.empty()) {
                std::cout << "Unordered_map пуст!\n";
                return;
            }

            unsigned filter_choice;
            std::cout << "Выберите критерий фильтрации:\n";
            std::cout << "1 - По ФИО\n";
            std::cout << "2 - По факультету\n";
            std::cout << "3 - По специальности\n";
            std::cout << "4 - По диапазону ID\n";
            std::cout << "Номер действия: ";
            number_filteredInput<unsigned>(filter_choice);

            auto keys = students_unordered_map.getKeys();
            std::vector<std::pair<int, bsuir>> filtered_elements;

            if (filter_choice == 1 || filter_choice == 2 || filter_choice == 3) {
                std::string filter_value;
                std::cout << "Введите значение для фильтрации: ";
                std::getline(std::cin, filter_value);

                for (int key : keys) {
                    auto node = students_unordered_map.find(key);
                    if (node) {
                        bool match = false;
                        if (filter_choice == 1 && node->value.GetFullname().find(filter_value) != std::string::npos) {
                            match = true;
                        }
                        else if (filter_choice == 2 && node->value.GetFaculty().find(filter_value) != std::string::npos) {
                            match = true;
                        }
                        else if (filter_choice == 3 && node->value.GetMajor().find(filter_value) != std::string::npos) {
                            match = true;
                        }

                        if (match) {
                            filtered_elements.push_back({ key, node->value });
                        }
                    }
                }
            }
            else if (filter_choice == 4) {
                int min_id, max_id;
                std::cout << "Введите минимальный ID: ";
                number_filteredInput<int>(min_id);
                std::cout << "Введите максимальный ID: ";
                number_filteredInput<int>(max_id);

                for (int key : keys) {
                    if (key >= min_id && key <= max_id) {
                        auto node = students_unordered_map.find(key);
                        if (node) {
                            filtered_elements.push_back({ key, node->value });
                        }
                    }
                }
            }
            else {
                std::cout << "Неверный выбор!\n";
                return;
            }
            if (filtered_elements.empty()) {
                std::cout << "\nЭлементы по заданному критерию не найдены!\n";
            }
            else {
                std::cout << "\n=== РЕЗУЛЬТАТЫ ФИЛЬТРАЦИИ (" << filtered_elements.size() << " элементов) ===\n";
                for (size_t i = 0; i < filtered_elements.size(); i++) {
                    std::cout << i + 1 << ". " << filtered_elements[i].second << std::endl;
                }
            }
        }
        else if (type == "queue") {
            if (students_queue.empty()) return;
            std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";

            int min_key, max_key;
            std::cout << "Введите минимальный id: ";
            number_filteredInput<int>(min_key);
            std::cout << "Введите максимальный id: ";
            number_filteredInput<int>(max_key);

            auto filtered = students_queue.filterByIdRange(min_key, max_key);
            if (filtered.empty()) {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "] не найдены!\n";
            }
            else {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "]:\n";
                for (size_t i = 0; i < filtered.getSize(); i++) {
                    std::cout << filtered[i] << std::endl;
                }
            }
        }
        else if (type == "priority_queue") {
            if (students_priority_queue.empty()) return;
            std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";

            int min_key, max_key;
            std::cout << "Введите минимальный id: ";
            number_filteredInput<int>(min_key);
            std::cout << "Введите максимальный id: ";
            number_filteredInput<int>(max_key);

            auto filtered = students_priority_queue.filterByIdRange(min_key, max_key);
            if (filtered.empty()) {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "] не найдены!\n";
            }
            else {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "]:\n";
                for (size_t i = 0; i < filtered.getSize(); i++) {
                    std::cout << filtered[i] << std::endl;
                }
            }
            }
        else if (type == "stack") {
            if (students_stack.empty()) return;
            std::cout << "\n=== ФИЛЬТРАЦИЯ СТУДЕНТОВ ===\n";

            int min_key, max_key;
            std::cout << "Введите минимальный id: ";
            number_filteredInput<int>(min_key);
            std::cout << "Введите максимальный id: ";
            number_filteredInput<int>(max_key);

            auto filtered = students_stack.filterByIdRange(min_key, max_key);
            if (filtered.empty()) {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "] не найдены!\n";
            }
            else {
                std::cout << "Элементы с ключами в диапазоне [" << min_key << ", " << max_key << "]:\n";
                for (size_t i = 0; i < filtered.GetSize(); i++) {
                    std::cout << filtered[i] << std::endl;
                }
            }
        }
        std::cout << std::endl;
        system("pause");
    }
};
int bsuir::count = 0;
//lab3
bsuir* bsuir::students_array = nullptr;
int bsuir::student_array_size = 0;
std::vector<bsuir> bsuir::students_vector;
MyList<bsuir> bsuir::students_list;
//lab4
BinaryTree<int> bsuir::students_set;
BinaryTree<int> bsuir::students_multiset;
BinaryTreeMap<int, std::string> bsuir::students_map;
BinaryTreeMap<int, std::string> bsuir::students_multimap;
unordered_map<int, bsuir> bsuir::students_unordered_map;
//lab5
Queue<bsuir> bsuir::students_queue;
Queue<bsuir> bsuir::students_priority_queue{true};
Stack<bsuir> bsuir::students_stack;