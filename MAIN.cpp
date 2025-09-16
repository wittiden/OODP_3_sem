#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include "input_check.h"
#include "lab1.h"

enum main_menu_names { LAB_1, LAB_2, MAIN_EXIT };
enum secondary_menu_names { SHOW_LAB_INFO, LAB_IMPLEMENTATION, BACK_TO_MAIN_MENU, SECONDARY_EXIT };

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hideCursor();

	const std::string main_Menu[]{ "1 - Использование потоков ввода/вывода данных", "2 - Использование потоков файлового ввода/вывода данных", "Выход" };
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
			const std::string secondary_Menu[]{ "Получить информацию о задании","Запустить программу по работе с файлами","Назад","Выход" };
			const int secondary_Menu_Count = sizeof(secondary_Menu) / sizeof(secondary_Menu[0]);

			bool inSecondaryMenu = true;
			while (inSecondaryMenu) {
				int secondary_Menu_choice = main_showMenu("2 - Использование потоков файлового ввода/вывода данных", secondary_Menu, secondary_Menu_Count, false);

				switch (secondary_Menu_choice) {
				case SHOW_LAB_INFO: {
					std::cout << "На основе разработанной иерархии классов, реализованной в лабораторной работе «Использование потоков ввода/вывода данных», реализовать программу работы с данными, используя потоки файлового ввода-вывода. Реализовать функций добавления данных в файл, удаления данных из файла, редактирования данных в файле, просмотра данных из файла, поиска данных по необходимым параметрам в файле.\n\nИспользовать функции open(), is_open(), bad(), good(), close(), eof(), fail(), перегрузить операторы вывода в поток << и считывания из потока >>, seekg(), seekp(), tellg()\n";
					system("pause");
					break;
				}
				case LAB_IMPLEMENTATION: {
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
								wrppr[i].showPr();
							}
						}
					} while (idSearch != 0);

					std::cout << "\n\n===! ВЫВОД ИНФОРМАЦИИ ИЗ ФАЙЛА !===\n\n";
					std::cout << "Пользователи: \n";
					Customer::showCustomerFileInfo();

					std::cout << "Букеты: \n";
					Bouquet bouquetForShowfileInfo;
					bouquetForShowfileInfo.showFileInfo();

					hideCursor();
					system("pause");
					break;
				}
				case BACK_TO_MAIN_MENU: {
					inSecondaryMenu = false;
					break;
				}
				case SECONDARY_EXIT: {
					return 0;
				}
				default:
					break;
				}
			}
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