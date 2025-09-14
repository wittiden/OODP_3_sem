#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include"input_check.h"

static int globalProductCount = 0;

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

	void addPr() override {
		flowers.clear();

		std::cout.setf(std::ios::right);
		std::cout.width(50);
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
	}
	void deletePr() override {
		if (!flowers.empty()) {
			std::cout.setf(std::ios::right);
			std::cout.width(60);
			std::cout << "\n===! УДАЛЕНИЕ БУКЕТА !===" << std::endl;
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
	void showPr() override {
		std::cout << "\n========================\n";
		std::cout << "\n=== БУКЕТ #" << bouquetId << " ===" << std::endl;
		std::cout << "Цветов: " << flowersAmount << std::endl;
		std::cout << "Стоимость: " << cost << " руб." << std::endl;

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
};
int Bouquet::bouquetCount = 0;

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

	void addPr() override {
		std::cout.setf(std::ios::right);
		std::cout.width(60);
		std::cout << "\n===! ДОБАВИТЬ ОБЕРТКУ? !===" << std::endl;
		std::cout.unsetf(std::ios::right);
		std::cout << "1 - Да, 0 - Нет: ";
		number_filteredInput<bool>(wrapperSelect);
		if (wrapperSelect) {

			std::cout.setf(std::ios::right);
			std::cout.width(60);
			std::cout << "\n===! ДОБАВЛЕНИЕ ОБЕРТКИ !===" << std::endl;
			std::cout.unsetf(std::ios::right);

			std::cout << "Обертка будет цветной? (1 - Да, 0 - Нет): ";
			number_filteredInput<bool>(colored);
			std::cout << "Обертка будет c рисунком? (1 - Да, 0 - Нет): ";
			number_filteredInput<bool>(drawing);

			Wrapper newWrapper(colored, drawing);
			allWrappers.push_back(newWrapper);
			std::cout << "Обертка успешно добавлена!";
		}
		else {
			return;
		}

	}
	void deletePr() override {
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
	void showPr() {
		if (wrapperSelect) {
			std::cout << "\n=== ОБЕРТКА ===" << std::endl;
			std::cout << "Цветная: " << (colored ? "Да" : "Нет") << std::endl;
			std::cout << "С рисунком: " << (drawing ? "Да" : "Нет") << std::endl;
		}
	}
};
int Wrapper::wrapperCount = 0;

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

	static void addCustomer(std::vector<Customer>& obj) {
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
		letter_filteredInput<std::string>(email, 1, 0, 1);

		obj.push_back(Customer(name, city, email));
	}
	static void deleteCustomer(std::vector<Customer>& obj) {
		if (!obj.empty()) obj.pop_back();
	}
	static void showCustomer(std::vector<Customer>& obj) {
		std::cout.setf(std::ios::right);
		std::cout.width(60);
		std::cout << "\n===! ДАННЫЕ КЛИЕНТА !===" << std::endl;
		std::cout.unsetf(std::ios::right);

		for (int i = 0; i < obj.size(); i++) {
			std::cout << "Имя: " << obj[i].name << std::endl;
			std::cout << "Город: " << obj[i].city << std::endl;
			std::cout << "Email: " << obj[i].email << std::endl;
			std::cout << "ID: " << obj[i].id << std::endl;
		}
	}
};
int Customer::count = 0;

enum main_menu_names { LAB_1, LAB_2, MAIN_EXIT };
enum secondary_menu_names { SHOW_LAB_INFO, LAB_IMPLEMENTATION, BACK_TO_MAIN_MENU, SECONDARY_EXIT };

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hideCursor();

	const std::string main_Menu[]{ "1 - Использование потоков ввода/вывода данных", "2 - .......", "Выход" };
	const int main_Menu_Count = sizeof(main_Menu) / sizeof(main_Menu[0]);

	bool inMainMenu = true;
	while (inMainMenu) {
		int main_Menu_choice = main_showMenu("LAB WORK NUMBER", main_Menu, main_Menu_Count, false);

		switch (main_Menu_choice) {
		case LAB_1 : {
			const std::string secondary_Menu[]{ "Получить информацию о задании","Создать заказ на букет","Назад","Выход" };
			const int secondary_Menu_Count = sizeof(secondary_Menu) / sizeof(secondary_Menu[0]);

			bool inSecondaryMenu = true;
			while (inSecondaryMenu) {
				int secondary_Menu_choice = main_showMenu("1 - Использование потоков ввода/вывода данных", secondary_Menu, secondary_Menu_Count, false);

				switch (secondary_Menu_choice) {
				case SHOW_LAB_INFO : {
					std::cout << "В каждом индивидуальном задании необходимо реализовать функции просмотра, добавления, удаления, редактирования, сортировки, поиска данных по необходимым параметрам. Использовать минимум 5 флагов форматирования. Сформировать табличный вывод всех данных. Использовать функции setf() и unsetf() для установки и сбрасывания флагов. Использовать функции eof(), fail(), good(), bad(), clear() для провеки состояния потока.\n\n 1. Разработать набор классов (минимум 5 классов, связи между классами: агрегация, композиция, наследование) по предметной области «Цветочный магазин». Функционал программы должен позволить собрать заказ.\n";
					system("pause");
					break;
				}
				case LAB_IMPLEMENTATION : {
					showCursor();

					int bouquetsize;
					int idSearch;
					std::vector<Customer> cstmr;
					std::vector<Wrapper> wrppr;
					std::vector<Bouquet> bqt;

					Customer::addCustomer(cstmr);

					std::cout << "\nСколько букетов вам нужно? ";
					while (true) {
						std::cin >> bouquetsize;
						if (!std::cin.bad() && bouquetsize > 0) {
							break;
						}
						std::cin.clear();
						std::cout << "Неправильный ввод данных\n";
						std::cin.ignore(10, '\n');
					}

					for (int i = 0; i < bouquetsize; i++) {
						Bouquet bouquet;
						Wrapper wrapper;

						bouquet.addPr();
						wrapper.addPr();

						bqt.push_back(bouquet);
						wrppr.push_back(wrapper);
					}

					for (int i = 0; i < bqt.size(); i++) {
						bqt[i].showPr();
						if (i < wrppr.size()) {
							wrppr[i].showPr();
						}
					}
					Customer::showCustomer(cstmr);

					do {
						std::cout << "\nПоиск по id букета (введи 0 чтобы выйти): ";
						while (true) {
							std::cin >> idSearch;
							if (std::cin.good() && !std::cin.eof()) {
								break;
							}
							std::cin.clear();
							std::cout << "Неправильный ввод данных\n";
							std::cin.ignore(10, '\n');
						}
						for (int i = 0; i < bqt.size(); i++) {
							if (idSearch == bqt[i].GetBouquetId()) {
								bqt[i].showPr();
							}
						}
					} while (idSearch != 0);

					hideCursor();
					system("pause");
					break;
				}
				case BACK_TO_MAIN_MENU : {
					inSecondaryMenu = false;
					break;
				}
				case SECONDARY_EXIT : {
					return 0;
				}
				default:
					break;
				}
			}
			break;
		}
		case LAB_2 : {
			break;
		}
		case MAIN_EXIT : {
			return 0;
		}
		default:
			break;
		}
	}

	return 0;
}