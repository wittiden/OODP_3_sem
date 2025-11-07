#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include"input_check.h"

const std::string fileName = "myFile.txt";

enum Flowers { rose, tulip, sunflower, lily, carnation, hyacint };

class Product {
public:
    virtual void addPr() = 0;
    virtual void showPr() = 0;
    virtual void addToFile() = 0;
    virtual ~Product() {}
};

class Bouquet : public Product {
    float cost;
    int flowersAmount;
    std::vector<Flowers> flowers;
    int bouquetId;
    static int bouquetCount;
public:
    Bouquet() { cost = 0.0f; flowersAmount = 0; bouquetCount++; bouquetId = bouquetCount; }
    Bouquet(float cost) :Bouquet() { this->cost = cost; }
    Bouquet(float cost, int flowersAmount) :Bouquet(cost) { this->flowersAmount = flowersAmount; }
    Bouquet(float cost, int flowersAmount, const std::vector<Flowers>& flowers) : Bouquet(cost, flowersAmount) { this->flowers = flowers; }

    Bouquet(const Bouquet& other) :cost(other.cost), flowers(other.flowers), flowersAmount(other.flowersAmount), bouquetId(other.bouquetId) {}
    ~Bouquet() override { flowers.clear(); }

    float GetCost() const { return cost; }
    int GetFlowersAmount() const { return flowersAmount; }
    int GetBouquetId() const { return bouquetId; }
    void SetCost(float cost) { this->cost = cost; }
    void SetFlowersAmount(int flowersamount) { this->flowersAmount = flowersamount; }

    void addPr() override;
    void showPr() override;
    void addToFile() override;
    void showFileInfo();
    void removeByIndex(int index);
    void deletePr(std::vector<Bouquet>& obj, int  index);
};

class Wrapper : public Product {
    bool colored;
    bool  drawing;
    std::vector<Wrapper> allWrappers;
public:
    Wrapper() { colored = 0; drawing = 0; }
    Wrapper(bool colored) :Wrapper() { this->colored = colored; }
    Wrapper(bool drawing, bool colored) :Wrapper(colored) { this->drawing = drawing; }

    Wrapper(const Wrapper& other) :colored(other.colored), drawing(other.drawing) {}
    ~Wrapper() override { allWrappers.clear(); }

    bool GetColored() const { return colored; }
    bool GetDrawing() const { return drawing; }
    void SetColored(bool colored) { this->colored = colored; }
    void SetDrawing(bool drawing) { this->drawing = drawing; }

    void addPr() override;
    void showPr() override;
    void addToFile() override;

    friend class Bouquet;
};

class Customer {
    std::string name;
    std::string city;
    std::string email;
    int id;
    static int count;
public:
    Customer() { name = "anonim"; city = "default"; email = "default"; count++; id = count; }
    Customer(std::string name) :Customer() { this->name = name; }
    Customer(std::string name, std::string city) :Customer(name) { this->city = city; }
    Customer(std::string name, std::string city, std::string email) :Customer(name, city) { this->email = email; }

    Customer(const Customer& other) :name(other.name), city(other.city), email(other.email), id(other.id) {}
    ~Customer() {}

    std::string GetName() const { return name; }
    std::string GetCity() const { return city; }
    std::string GetEmail() const { return email; }
    int GetId() const { return id; }
    void SetName(std::string name) { this->name = name; }
    void SetCity(std::string city) { this->city = city; }
    void SetEmail(std::string email) { this->email = email; }

    static void addCustomer(std::vector<Customer>& obj);
    static void deleteCustomer(std::vector<Customer>& obj);
    static void showCustomer(std::vector<Customer>& obj);
    static void addCustomerToFile(std::vector<Customer>& obj);
    static void showCustomerFileInfo();
    void removCustomerByIndex(int index);

    friend std::ostream& operator<<(std::ostream& os, const Customer& obj);
};

int Bouquet::bouquetCount = 0;
int Customer::count = 0;

void Bouquet::addPr() {
    flowers.clear();

    std::cout << std::endl;
    std::cout.setf(std::ios::right);
    std::cout.width(40);
    std::cout << "===! СОЗДАНИЕ БУКЕТА !===";
    std::cout.unsetf(std::ios::right);
    std::cout << std::endl;
    // endl = \n + fflush()
    std::cout << "\nВведите количество цветов в букете: ";
    while (true) {
        std::cin >> flowersAmount;
        if (!std::cin.fail() && flowersAmount > 0) {
            break;
        }
        std::cin.clear();
        std::cerr << "Неправильный ввод данных\n";
        std::cin.ignore(10, '\n');
    }

    float flowerPrices[]{ 150.0f, 100.0f, 120.0f, 130.0f, 90.0f, 110.0f };
    std::string flowersNames[]{ "Роза", "Тюльпан", "Подсолнух", "Лилия", "Гвоздика", "Гиацинт" };

    for (size_t i = 0; i < flowersAmount; i++) {
        std::cout << "\nВыберите цветок " << i + 1 << " из " << flowersAmount << ":" << std::endl;
        std::cout << "0 - Роза (150 руб.)" << std::endl;
        std::cout << "1 - Тюльпан (100 руб.)" << std::endl;
        std::cout << "2 - Подсолнух (120 руб.)" << std::endl;
        std::cout << "3 - Лилия (130 руб.)" << std::endl;
        std::cout << "4 - Гвоздика (90 руб.)" << std::endl;
        std::cout << "5 - Гиацинт (110 руб.)" << std::endl; 

        int choice;
        std::cout << "Ваш выбор: ";
        while (true) {
            std::cin >> choice;
            if (std::cin.good()) {
                break;
            }
            std::cin.clear();
            std::cerr << "Неправильный ввод данных\n";
            std::cin.ignore(10, '\n');
        }

        if (choice >= 0 && choice <= 5) {
            Flowers selectFlower = (Flowers)choice;
            flowers.push_back(selectFlower);

            cost += flowerPrices[choice];
        }
        else {
            std::cout << "Неверный выбор! Пропускаем этот цветок." << std::endl;
            i--;
        }
    }
    std::cout << "Итоговая стоимость: " << cost << " руб." << std::endl;
    std::cout << "Количество цветов: " << flowersAmount << std::endl;

    Bouquet::addToFile();
}

void Bouquet::showPr() {
    std::ios::fmtflags originalFlags = std::cout.flags();

    std::cout << "\n\n\n";

    std::cout << "                      БУКЕТ #" << GetBouquetId() << std::endl;
    std::cout << "======================================================" << std::endl;

    std::cout << "Количество цветов: " << GetFlowersAmount() << std::endl;
    std::cout << "Стоимость:        " << GetCost() << " руб." << std::endl;

    std::string flowerNames[] = { "Роза", "Тюльпан", "Подсолнух", "Лилия", "Гвоздика", "Гиацинт" };

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Состав букета:" << std::endl;

    for (size_t i = 0; i < flowers.size(); i++) {
        std::cout << "- " << flowerNames[flowers[i]];
        if (i < flowers.size() - 1) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "======================================================" << std::endl;

    std::cout.flags(originalFlags);
}
void Bouquet::addToFile() {
    std::ofstream os(fileName, std::ofstream::app);

    if (!os.is_open()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        os << "\n===! Bouquet #" << GetBouquetId() << " !===" << std::endl;
        os << "Flowers amount: " << GetFlowersAmount() << std::endl;
        os << "Price: " << GetCost() << " rub." << std::endl;
        os << "Id: " << GetBouquetId() << std::endl;

        std::string flowerNames_[] = { "Rose", "tulip", "sunflower", "lily", "carnation", "hyacint" };

        os << "compound: ";
        for (size_t i = 0; i < flowers.size(); i++) {
            os << flowerNames_[flowers[i]];
            if (i < flowers.size() - 1) {
                os << ", ";
            }
        }
        os << std::endl;
    }
}

void Bouquet::showFileInfo() {
    std::ifstream is(fileName);

    if (is.fail()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        bool mySelection = false;

        while (!is.eof()) {
            std::string line;
            line = "";
            std::getline(is, line);

            if (line.find("===! Bouquet #") != std::string::npos || line.find("===! WRAPPER !===") != std::string::npos) {
                mySelection = true;
                continue;
            }
            if (mySelection) {
                if (line.find("===! CUSTOMER DATA #") != std::string::npos) {
                    mySelection = false;
                }
                else {
                    std::cout << line;
                }
                std::cout << std::endl;

            }
        }
    }
}

void Bouquet::removeByIndex(int index) {
    std::ifstream is(fileName);
    if (!is.is_open()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        std::vector<std::string> lines;
        std::string line;
        line = "";
        int count = 0;
        bool skip = false;

        while (std::getline(is,line)) {
            if (line.find("===! Bouquet #") != std::string::npos) {
                count++;
                if (count == index) {
                    skip = true;
                    continue;
                }
            }
            if (skip && line.find("===! WRAPPER !===") != std::string::npos) {
                skip = true;
                continue;
            }
            if (skip && line.find("===") != std::string::npos) {
                skip = false;
            }
            if (!skip) {
                lines.push_back(line);
            }
        }
        is.close();

        std::ofstream os(fileName);
        for (const auto& container : lines) {
            os << container << std::endl;
        }
    }
}

void Wrapper::addPr() {
    std::cout << std::endl;
    std::cout.setf(std::ios::right);
    std::cout.width(40);
    std::cout << "===! ДОБАВЛЕНИЕ ОБЕРТКИ !===";
    std::cout.unsetf(std::ios::right);
    std::cout << std::endl;

    std::cout << "\nОбертка будет цветной? (1 - Да, 0 - Нет): ";
    number_filteredInput<bool>(colored);
    std::cout << "Обертка будет c рисунком? (1 - Да, 0 - Нет): ";
    number_filteredInput<bool>(drawing);

    Wrapper newWrapper(drawing,colored);
    allWrappers.push_back(newWrapper);
    Wrapper::addToFile();
}

void Wrapper::showPr() {
    std::ios::fmtflags originalFlags = std::cout.flags();

    std::cout << "                       ОБЕРТКА" << std::endl;
    std::cout << "======================================================" << std::endl;

    std::cout << "Цветная:   " << (GetColored() ? "Да" : "Нет") << std::endl;
    std::cout << "С рисунком: " << (GetDrawing() ? "Да" : "Нет") << std::endl;

    std::cout << "======================================================" << std::endl;

    std::cout.flags(originalFlags);
}

void Wrapper::addToFile() {
    std::ofstream os(fileName, std::ofstream::app);

    if (os.fail()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        os << "\n===! WRAPPER !===" << std::endl;
        os << "Colored: " << (GetColored() ? "Yes" : "No") << std::endl;
        os << "Drawing: " << (GetDrawing() ? "Yes" : "No") << std::endl;
    }
}

void Customer::addCustomer(std::vector<Customer>& obj) {
    std::string name, city, email;

    std::cout << std::endl;
    std::cout.setf(std::ios::right);
    std::cout.width(40);
    std::cout << "===! ДОБАВЛЕНИЕ ДАННЫХ КЛИЕНТА !===";
    std::cout.unsetf(std::ios::right);    

    std::cout << "\nВведите имя: ";
    letter_filteredInput<std::string>(name, 0, 1);
    std::cout << "Введите город: ";
    letter_filteredInput<std::string>(city, 0, 1);
    std::cout << "Введите email: ";
    letter_filteredInput<std::string>(email);

    obj.push_back(Customer(name, city, email));
    addCustomerToFile(obj);
}

void Customer::deleteCustomer(std::vector<Customer>& obj) {
    if (!obj.empty()) {
        obj.pop_back();
    }
    else {
        std::cout << std::endl;
        std::cout.setf(std::ios::right);
        std::cout.width(40);
        std::cout << "===! СПИСОК ЗАКАЗЧКОВ ПУСТ !===";
        std::cout.unsetf(std::ios::right);
        std::cout << std::endl;
    }
}

void Customer::showCustomer(std::vector<Customer>& obj) {
    std::ios::fmtflags originalFlags = std::cout.flags();

    std::cout << "\n\n\n\n";
    std::cout << "       ДАННЫЕ КЛИЕНТА" << std::endl;
    std::cout << "============================" << std::endl;

    for (const auto& container : obj) {
        std::cout << "ID:    " << container.id << std::endl;
        std::cout << "Имя:   " << container.GetName() << std::endl;
        std::cout << "Город: " << container.GetCity() << std::endl;
        std::cout << "Email: " << container.GetEmail() << std::endl;
        std::cout << "============================" << std::endl;
    }

    std::cout.flags(originalFlags);
}

void Customer::addCustomerToFile(std::vector<Customer>& obj) {
    std::ofstream os(fileName, std::ofstream::app);

    if (!os.is_open()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        for (const auto& container : obj) {
            os << container;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Customer& obj) {

    os << "\n===! CUSTOMER DATA #" << obj.GetId() << " !===" << std::endl;
    os << "Name: " << obj.GetName() << std::endl;
    os << "City: " << obj.GetCity() << std::endl;
    os << "Email: " << obj.GetEmail() << std::endl;

    return os;
}

std::ifstream& operator>>(std::ifstream& is, const Customer& obj) {
    return is;
}

void Customer::showCustomerFileInfo() {
    std::ifstream is(fileName);

    if (is.bad()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        bool mySelection = false;
          
        while (!is.eof()) {
            std::string line;
            line = "";
            std::getline(is, line);

            if (line.find("===! CUSTOMER DATA #") != std::string::npos) {
                mySelection = true;
                continue;
            }
            if (mySelection) {
                if (line.empty() || line.find("===! Bouquet #") != std::string::npos || line.find("===! WRAPPER !===") != std::string::npos) {
                    mySelection = false;
                }
                else {
                    std::cout << line;
                }
                std::cout << std::endl;
            }
        }
    }
}

void Customer::removCustomerByIndex(int index) {
    std::ifstream is(fileName);
    if (is.fail()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        std::vector<std::string> lines;
        std::string line;
        line = "";
        int count = 0;
        bool skip = false;

        while (std::getline(is, line)) {
            if (line.find("===! CUSTOMER DATA") != std::string::npos) {
                count++;
                if (count == index) {
                    skip = true;
                    continue;
                }
            }
            if (skip && line.find("===") != std::string::npos) {
                skip = false;
            }
            if (!skip) {
                lines.push_back(line);
            }
        }
        is.close();

        std::ofstream os(fileName);
        for (const auto& container : lines) {
            os << container << std::endl;
        }
    }
}

void swap(Bouquet& a, Bouquet& b) {
    Bouquet temp = a;
    a = b;
    b = temp;
}

void bubbleSort(std::vector<Bouquet>& obj) {
    int n = obj.size();
    for (size_t i = 0; i < n - 1; i++) {
        for (size_t j = 0; j < n - i - 1; j++) {
            if (obj[j].GetFlowersAmount() > obj[j + 1].GetFlowersAmount()) {
                swap(obj[j], obj[j + 1]);
            }
        }
    }
}

void clearFile() {
    std::ofstream os(fileName, std::ofstream::trunc);
    os.close();
}

bool fileEmptyChecker() {
    std::ifstream is(fileName);

    if (!is.is_open()) {
        return true;
    }

    is.seekg(0, std::ios::end);
    bool isEmpty = (is.tellg() == 0);

    is.close();

    return isEmpty;
}

void Bouquet::deletePr(std::vector<Bouquet>& obj, int index) {
    std::ios::fmtflags originalFlags = std::cout.flags();

    std::cout << "\n\n\n";

    std::cout << "                      БУКЕТ #" << GetBouquetId() << std::endl;
    std::cout << "======================================================" << std::endl;

    std::cout << "Количество цветов: " << GetFlowersAmount() << std::endl;
    std::cout << "Стоимость:        " << GetCost() << " руб." << std::endl;

    std::string flowerNames[] = { "Роза", "Тюльпан", "Подсолнух", "Лилия", "Гвоздика", "Гиацинт" };

    std::cout << "------------------------------------------------------" << std::endl;
    std::cout << "Состав букета:" << std::endl;

    for (size_t i = 0; i < flowers.size(); i++) {
        std::cout << "- " << flowerNames[flowers[i]];
        if (i < flowers.size() - 1) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << "======================================================" << std::endl;

    std::cout.flags(originalFlags);

    obj.erase(obj.begin() + index-1);

}