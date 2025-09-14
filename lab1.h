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
    std::cout << "\n===! ÑÎÇÄÀÍÈÅ ÁÓÊÅÒÀ !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    std::cout << "Ââåäèòå êîëè÷åñòâî öâåòîâ â áóêåòå: ";
    while (true) {
        std::cin >> flowersAmount;
        if (!std::cin.fail() && flowersAmount > 0) {
            break;
        }
        std::cin.clear();
        std::cout << "Íåïðàâèëüíûé ââîä äàííûõ\n";
        std::cin.ignore(10, '\n');
    }

    float flowerPrices[]{ 150.0f, 100.0f, 120.0f, 130.0f, 90.0f, 110.0f };
    std::string flowersNames[]{ "Ðîçà", "Òþëüïàí", "Ïîäñîëíóõ", "Ëèëèÿ", "Ãâîçäèêà", "Ãèàöèíò" };

    for (int i = 0; i < flowersAmount; i++) {
        std::cout << "\nÂûáåðèòå öâåòîê " << i + 1 << " èç " << flowersAmount << ":" << std::endl;
        std::cout << "0 - Ðîçà (150 ðóá.)" << std::endl;
        std::cout << "1 - Òþëüïàí (100 ðóá.)" << std::endl;
        std::cout << "2 - Ïîäñîëíóõ (120 ðóá.)" << std::endl;
        std::cout << "3 - Ëèëèÿ (130 ðóá.)" << std::endl;
        std::cout << "4 - Ãâîçäèêà (90 ðóá.)" << std::endl;
        std::cout << "5 - Ãèàöèíò (110 ðóá.)" << std::endl;

        int choice;
        std::cout << "Âàø âûáîð: ";
        while (true) {
            std::cin >> choice;
            if (std::cin.good()) {
                break;
            }
            std::cin.clear();
            std::cout << "Íåïðàâèëüíûé ââîä äàííûõ\n";
            std::cin.ignore(10, '\n');
        }

        if (choice >= 0 && choice <= 5) {
            Flowers selectFlower = (Flowers)choice;
            flowers.push_back(selectFlower);

            cost += flowerPrices[choice];
        }
        else {
            std::cout << "Íåâåðíûé âûáîð! Ïðîïóñêàåì ýòîò öâåòîê." << std::endl;
            i--;
        }
    }
    std::cout << "Èòîãîâàÿ ñòîèìîñòü: " << cost << " ðóá." << std::endl;
    std::cout << "Êîëè÷åñòâî öâåòîâ: " << flowersAmount << std::endl;
}

void Bouquet::deletePr() {
    if (!flowers.empty()) {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ÓÄÀËÅÍÈÅ ÁÓÊÅÒA !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        flowers.clear();
        flowersAmount = 0;
        cost = 0.0f;
    }
    else {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ÁÓÊÅÒ ÏÓÑÒ !===" << std::endl;
        std::cout.unsetf(std::ios::right);
    }
}

void Bouquet::showPr() {
    std::cout << "\n========================\n";
    std::cout << "\n=== ÁÓÊÅÒ #" << bouquetId << " ===" << std::endl;
    std::cout << "Öâåòîâ: " << flowersAmount << std::endl;
    std::cout << "Ñòîèìîñòü: " << cost << " ðóá." << std::endl;

    std::string flowerNames[] = { "Ðîçà", "Òþëüïàí", "Ïîäñîëíóõ", "Ëèëèÿ", "Ãâîçäèêà", "Ãèàöèíò" };

    std::cout << "Ñîñòàâ: ";
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
    std::cout << "\n===! ÄÎÁÀÂÈÒÜ ÎÁÅÐÒÊÓ? !===" << std::endl;
    std::cout.unsetf(std::ios::right);
    std::cout << "1 - Äà, 0 - Íåò: ";
    number_filteredInput<bool>(wrapperSelect);
    if (wrapperSelect) {

        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ÄÎÁÀÂËÅÍÈÅ ÎÁÅÐÒÊÈ !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        std::cout << "Îáåðòêà áóäåò öâåòíîé? (1 - Äà, 0 - Íåò): ";
        number_filteredInput<bool>(colored);
        std::cout << "Îáåðòêà áóäåò c ðèñóíêîì? (1 - Äà, 0 - Íåò): ";
        number_filteredInput<bool>(drawing);

        Wrapper newWrapper(colored, drawing);
        allWrappers.push_back(newWrapper);
        std::cout << "Îáåðòêà óñïåøíî äîáàâëåíà!";
    }
    else {
        return;
    }
}

void Wrapper::deletePr() {
    if (!allWrappers.empty()) {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ÓÄÀËÅÍÈÅ ÎÁÅÐÒÊÈ !===" << std::endl;
        std::cout.unsetf(std::ios::right);

        allWrappers.clear();
    }
    else {
        std::cout.setf(std::ios::right);
        std::cout.width(60);
        std::cout << "\n===! ÌÅÍÞ ÎÁÅÐÒÎÊ ÏÓÑÒÎ !===" << std::endl;
        std::cout.unsetf(std::ios::right);
    }
}

void Wrapper::showPr() {
    if (wrapperSelect) {
        std::cout << "\n=== ÎÁÅÐÒÊÀ ===" << std::endl;
        std::cout << "Öâåòíàÿ: " << (colored ? "Äà" : "Íåò") << std::endl;
        std::cout << "Ñ ðèñóíêîì: " << (drawing ? "Äà" : "Íåò") << std::endl;
    }
}

int Customer::count = 0;

void Customer::addCustomer(std::vector<Customer>& obj) {
    std::string name, city, email;

    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! ÄÎÁÀÂËÅÍÈÅ ÄÀÍÍÛÕ ÊËÈÅÍÒÀ !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    std::cout << "\nÂâåäèòå èìÿ: ";
    letter_filteredInput<std::string>(name, 0, 1);
    std::cout << "Ââåäèòå ãîðîä: ";
    letter_filteredInput<std::string>(city, 0, 1);
    std::cout << "Ââåäèòå email: ";
    letter_filteredInput<std::string>(email, 1, 0, 1);

    obj.push_back(Customer(name, city, email));
}

void Customer::deleteCustomer(std::vector<Customer>& obj) {
    if (!obj.empty()) obj.pop_back();
}

void Customer::showCustomer(std::vector<Customer>& obj) {
    std::cout.setf(std::ios::right);
    std::cout.width(60);
    std::cout << "\n===! ÄÀÍÍÛÅ ÊËÈÅÍÒÀ !===" << std::endl;
    std::cout.unsetf(std::ios::right);

    for (int i = 0; i < obj.size(); i++) {
        std::cout << "Èìÿ: " << obj[i].name << std::endl;
        std::cout << "Ãîðîä: " << obj[i].city << std::endl;
        std::cout << "Email: " << obj[i].email << std::endl;
        std::cout << "ID: " << obj[i].id << std::endl;
    }
}