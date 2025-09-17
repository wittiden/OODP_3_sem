#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include"input_check.h"

const std::string fileName = "myFile.txt";

enum Flowers {
    rose, tulip, sunflower, lily, carnation, hyacint
};

class Product {
public:
    virtual void addPr() = 0;
    virtual void deletePr() = 0;
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
    void deletePr() override;
    void showPr() override;
    void addToFile() override;
    void showFileInfo();
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
    void deletePr() override;
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
};

int Bouquet::bouquetCount = 0;
int Customer::count = 0;

void Bouquet::addPr() {
    flowers.clear();

    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! СОЗДАНИЕ БУКЕТА !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    std::cout << "Введите количество цветов в букете: ";
    while (true) {
        std::cin >> flowersAmount;
        if (!std::cin.fail() && flowersAmount > 0) {
            break;
        }
        std::cin.clear();
        std::cout << "Неправильный ввод данных\n";
        std::cin.ignore(10, '\n');
    }

    float flowerPrices[]{ 150.0f, 100.0f, 120.0f, 130.0f, 90.0f, 110.0f };
    std::string flowersNames[]{ "Роза", "Тюльпан", "Подсолнух", "Лилия", "Гвоздика", "Гиацинт" };

    for (int i = 0; i < flowersAmount; i++) {
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
            std::cout << "Неправильный ввод данных\n";
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

void Bouquet::deletePr() {
    if (!flowers.empty()) {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! УДАЛЕНИЕ БУКЕТA !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        flowers.clear();
        flowersAmount = 0;
        cost = 0.0f;
    }
    else {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! БУКЕТ ПУСТ !===" << std::endl;
        std::cout.unsetf(std::ios::right);
    }
}

void Bouquet::showPr() {
    std::cout << "\n===! БУКЕТ #" << GetBouquetId() << " !===" << std::endl;
    std::cout << "Цветов: " << GetFlowersAmount() << std::endl;
    std::cout << "Стоимость: " << GetCost() << " руб." << std::endl;

    std::string flowerNames[] = { "Роза", "Тюльпан", "Подсолнух", "Лилия", "Гвоздика", "Гиацинт" };

    std::cout << "Состав: ";
    for (int i = 0; i < flowers.size(); i++) {
        std::cout << flowerNames[flowers[i]];
        if (i < flowers.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
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
        for (int i = 0; i < flowers.size(); i++) {
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

            if (line.find("===! Bouquet") != std::string::npos || line.find("===! WRAPPER !===") != std::string::npos) {
                mySelection = true;
                continue;
            }
            if (mySelection) {
                if (line.find("===! CUSTOMER DATA !===") != std::string::npos) {
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

void Wrapper::addPr() {
    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! ДОБАВЛЕНИЕ ОБЕРТКИ !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    std::cout << "Обертка будет цветной? (1 - Да, 0 - Нет): ";
    number_filteredInput<bool>(colored);
    std::cout << "Обертка будет c рисунком? (1 - Да, 0 - Нет): ";
    number_filteredInput<bool>(drawing);

    Wrapper newWrapper(drawing,colored);
    allWrappers.push_back(newWrapper);
    Wrapper::addToFile();
}

void Wrapper::deletePr() {
    if (!allWrappers.empty()) {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! УДАЛЕНИЕ ОБЕРТКИ !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        allWrappers.clear();
    }
    else {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! МЕНЮ ОБЕРТОК ПУСТО !===" << std::endl;
        std::cout.unsetf(std::ios::right);
    }
}

void Wrapper::showPr() {
    std::cout << "\n===! ОБЕРТКА !===" << std::endl;
    std::cout << "Цветная: " << (GetColored() ? "Да" : "Нет") << std::endl;
    std::cout << "С рисунком: " << (GetDrawing() ? "Да" : "Нет") << std::endl;
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

    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! ДОБАВЛЕНИЕ ДАННЫХ КЛИЕНТА !===" << std::endl;
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
        while (obj.size() != 0) {
            obj.pop_back();
        }
    }
}

void Customer::showCustomer(std::vector<Customer>& obj) {
    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! ДАННЫЕ КЛИЕНТА !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    for (const auto& container : obj) {
        std::cout << "Имя: " << container.GetName() << std::endl;
        std::cout << "Город: " << container.GetCity() << std::endl;
        std::cout << "Email: " << container.email << std::endl;
        std::cout << "ID: " << container.id << std::endl;
    }
}

void Customer::addCustomerToFile(std::vector<Customer>& obj) {
    std::ofstream os(fileName, std::ofstream::app);

    if (!os.is_open()) {
        std::cerr << "Файл не удалось открыть\n";
        return;
    }
    else {
        os << "\n===! CUSTOMER DATA !===" << std::endl;
        for (const auto& container : obj) {
            os << "Name: " << container.GetName() << std::endl;
            os << "City: " << container.GetCity() << std::endl;
            os << "Email: " << container.GetEmail() << std::endl;
            os << "ID: " << container.GetId() << std::endl;
        }
    }
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

            if (line.find("===! CUSTOMER DATA !===") != std::string::npos) {
                mySelection = true;
                continue;
            }
            if (mySelection) {
                if (line.empty() || line.find("===! Bouquet") != std::string::npos || line.find("===! WRAPPER !===") != std::string::npos) {
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
