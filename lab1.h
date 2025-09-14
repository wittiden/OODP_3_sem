#pragma once
#include<iostream>
#include<string>
#include<vector>
#include "cursor_menu.h"
#include "cursor_visibility.h"
#include"input_check.h"

enum Flowers {
    rose, tulip, sunflower, lily, carnation, hyacint
};

class Product {
public:
    virtual void addPr() = 0;
    virtual void deletePr() = 0;
    virtual void showPr() = 0;
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
};

class Wrapper : public Product {
    bool colored;
    bool  drawing;
    bool wrapperSelect;
    std::vector<Wrapper> allWrappers;
    int wrapperId;
    static int wrapperCount;
public:
    Wrapper() { colored = 0; drawing = 0; wrapperSelect = 0; wrapperCount++; wrapperId = wrapperCount; }
    Wrapper(bool colored) :Wrapper() { this->colored = colored; }
    Wrapper(bool drawing, bool colored) :Wrapper(colored) { this->drawing = drawing; }

    Wrapper(const Wrapper& other) :colored(other.colored), drawing(other.drawing), wrapperSelect(other.wrapperSelect), allWrappers(other.allWrappers), wrapperId(other.wrapperId) {}
    ~Wrapper() override { allWrappers.clear(); }

    bool GetColored() const { return colored; }
    bool GetDrawing() const { return drawing; }
    int GetWrapperId() const { return wrapperId; }
    void SetColored(bool colored) { this->colored = colored; }
    void SetDrawing(bool drawing) { this->drawing = drawing; }

    void addPr() override;
    void deletePr() override;
    void showPr();
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
};

int Bouquet::bouquetCount = 0;

void Bouquet::addPr() {
    flowers.clear();

    std::cout.setf(std::ios::right);
    std::cout.width(50);
    std::cout << "\n===! �������� ������ !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    std::cout << "������� ���������� ������ � ������: ";
    while (true) {
        std::cin >> flowersAmount;
        if (!std::cin.fail() && flowersAmount > 0) {
            break;
        }
        std::cin.clear();
        std::cout << "������������ ���� ������\n";
        std::cin.ignore(10, '\n');
    }

    float flowerPrices[]{ 150.0f, 100.0f, 120.0f, 130.0f, 90.0f, 110.0f };
    std::string flowersNames[]{ "����", "�������", "���������", "�����", "��������", "�������" };

    for (int i = 0; i < flowersAmount; i++) {
        std::cout << "\n�������� ������ " << i + 1 << " �� " << flowersAmount << ":" << std::endl;
        std::cout << "0 - ���� (150 ���.)" << std::endl;
        std::cout << "1 - ������� (100 ���.)" << std::endl;
        std::cout << "2 - ��������� (120 ���.)" << std::endl;
        std::cout << "3 - ����� (130 ���.)" << std::endl;
        std::cout << "4 - �������� (90 ���.)" << std::endl;
        std::cout << "5 - ������� (110 ���.)" << std::endl;

        int choice;
        std::cout << "��� �����: ";
        while (true) {
            std::cin >> choice;
            if (std::cin.good()) {
                break;
            }
            std::cin.clear();
            std::cout << "������������ ���� ������\n";
            std::cin.ignore(10, '\n');
        }

        if (choice >= 0 && choice <= 5) {
            Flowers selectFlower = (Flowers)choice;
            flowers.push_back(selectFlower);

            cost += flowerPrices[choice];
        }
        else {
            std::cout << "�������� �����! ���������� ���� ������." << std::endl;
            i--;
        }
    }
    std::cout << "�������� ���������: " << cost << " ���." << std::endl;
    std::cout << "���������� ������: " << flowersAmount << std::endl;
}

void Bouquet::deletePr() {
    if (!flowers.empty()) {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! �������� �����A !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        flowers.clear();
        flowersAmount = 0;
        cost = 0.0f;
    }
    else {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ����� ���� !===" << std::endl;
        std::cout.unsetf(std::ios::right);
    }
}

void Bouquet::showPr() {
    std::cout << "\n========================\n";
    std::cout << "\n=== ����� #" << bouquetId << " ===" << std::endl;
    std::cout << "������: " << flowersAmount << std::endl;
    std::cout << "���������: " << cost << " ���." << std::endl;

    std::string flowerNames[] = { "����", "�������", "���������", "�����", "��������", "�������" };

    std::cout << "������: ";
    for (int i = 0; i < flowers.size(); i++) {
        std::cout << flowerNames[flowers[i]];
        if (i < flowers.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}

int Wrapper::wrapperCount = 0;

void Wrapper::addPr() {
    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! �������� �������? !===" << std::endl;
    std::cout.unsetf(std::ios::right);
    std::cout << "1 - ��, 0 - ���: ";
    number_filteredInput<bool>(wrapperSelect);
    if (wrapperSelect) {

        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ���������� ������� !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        std::cout << "������� ����� �������? (1 - ��, 0 - ���): ";
        number_filteredInput<bool>(colored);
        std::cout << "������� ����� c ��������? (1 - ��, 0 - ���): ";
        number_filteredInput<bool>(drawing);

        Wrapper newWrapper(colored, drawing);
        allWrappers.push_back(newWrapper);
        std::cout << "������� ������� ���������!";
    }
    else {
        return;
    }
}

void Wrapper::deletePr() {
    if (!allWrappers.empty()) {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! �������� ������� !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        allWrappers.clear();
    }
    else {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ���� ������� ����� !===" << std::endl;
        std::cout.unsetf(std::ios::right);
    }
}

void Wrapper::showPr() {
    if (wrapperSelect) {
        std::cout << "\n=== ������� ===" << std::endl;
        std::cout << "�������: " << (colored ? "��" : "���") << std::endl;
        std::cout << "� ��������: " << (drawing ? "��" : "���") << std::endl;
    }
}

int Customer::count = 0;

void Customer::addCustomer(std::vector<Customer>& obj) {
    std::string name, city, email;

    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! ���������� ������ ������� !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    std::cout << "\n������� ���: ";
    letter_filteredInput<std::string>(name, 0, 1);
    std::cout << "������� �����: ";
    letter_filteredInput<std::string>(city, 0, 1);
    std::cout << "������� email: ";
    letter_filteredInput<std::string>(email, 1, 0, 1);

    obj.push_back(Customer(name, city, email));
}

void Customer::deleteCustomer(std::vector<Customer>& obj) {
    if (!obj.empty()) obj.pop_back();
}

void Customer::showCustomer(std::vector<Customer>& obj) {
    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! ������ ������� !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    for (int i = 0; i < obj.size(); i++) {
        std::cout << "���: " << obj[i].name << std::endl;
        std::cout << "�����: " << obj[i].city << std::endl;
        std::cout << "Email: " << obj[i].email << std::endl;
        std::cout << "ID: " << obj[i].id << std::endl;
    }
}