#include<iostream>
#include<Windows.h>
#include<string>
#include<vector>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include "input_check.h"
#include "lab1-2.h"
#include "lab3.h"
#include "threads_options.h"
#include "main_functions.cpp"

enum main_menu_names { LAB_1, LAB_2, LAB_3, LAB_4, MAIN_EXIT };
enum secondary_menu_names { SHOW_LAB_INFO, LAB_IMPLEMENTATION, BACK_TO_MAIN_MENU, SECONDARY_EXIT };

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	hideCursor();

	clearFile();

	//std::thread activity_control(activity_monitor);
	//activity_control.detach();

	const std::string main_Menu[]{ "1 - Использование потоков ввода/вывода данных", "2 - Использование потоков файлового ввода/вывода данных", "3 - Контейнеры VECTOR, ARRAY, LIST","4 - Контейнеры map, set, multimap, multiset, unordered_map, unordered_set, unordered_multimap, unordered_multiset", "Выход" };
	const int main_Menu_Count = sizeof(main_Menu) / sizeof(main_Menu[0]);

	bool inMainMenu = true;
	while (inMainMenu) {
		int main_Menu_choice = main_showMenu("LAB WORK NUMBER", main_Menu, main_Menu_Count, false);

		switch (main_Menu_choice) {
		case LAB_1 : {
			const std::string secondary_Menu[]{ "Получить информацию о задании","Выполнить задание","Назад","Выход" };
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
					showLab1Menu();

					break;
				}
				case BACK_TO_MAIN_MENU : {
					std::cout << "Возвращаемся в предыдущее меню";
					loadingImitation();

					inSecondaryMenu = false;
					break;
				}
				case SECONDARY_EXIT : {
					std::cout << "Выходим из программы";
					loadingImitation();

					return 0;
				}
				default:
					break;
				}
			}
			break;
		}
		case LAB_2 : {
			const std::string secondary_Menu[]{ "Получить информацию о задании", "Выполнить задание", "Назад", "Выход" };
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
					showLab2Menu();
					break;
				}
				case BACK_TO_MAIN_MENU: {
					std::cout << "Возвращаемся в предыдущее меню";
					loadingImitation();

					inSecondaryMenu = false;
					break;
				}
				case SECONDARY_EXIT: {
					std::cout << "Выходим из программы";
					loadingImitation();

					return 0;
				}
				default:
					break;
				}
			}
			break;
		}
		case LAB_3: {
			const std::string secondary_Menu[]{ "Получить информацию о задании", "Выполнить задание", "Назад", "Выход" };
			const int secondary_Menu_Count = sizeof(secondary_Menu) / sizeof(secondary_Menu[0]);

			bool inSecondaryMenu = true;
			while (inSecondaryMenu) {
				int secondary_Menu_choice = main_showMenu("3 - Контейнеры VECTOR, ARRAY, LIST", secondary_Menu, secondary_Menu_Count, false);

				switch (secondary_Menu_choice) {
				case SHOW_LAB_INFO: {
					std::cout << "Учет студентов ВУЗа\n\nВ каждом индивидуальном задании необходимо создать контейнеры list, vector, array, которые будут хранить объекты классов по предметной области, указанной в таблице(класс должен содержать функционал по предметной области(добавление, удаление, редактирование, поиск, фильтр данных)). Для контейнера реализовать добавление, удаление, редактирование, вывод содержимого контейнера на экран и в файл, поиск и сортировку элементов.Необходимо создать удобное пользовательское меню для тестирования всех реализованных функций.\n";
					system("pause");
					break;
				}
				case LAB_IMPLEMENTATION: {
					showLab3Menu();
					break;
				}
				case BACK_TO_MAIN_MENU: {
					std::cout << "Возвращаемся в предыдущее меню";
					loadingImitation();

					inSecondaryMenu = false;
					break;
				}
				case SECONDARY_EXIT: {
					std::cout << "Выходим из программы";
					loadingImitation();

					return 0;
				}
				default:
					break;
				}
			}
			break;
		}
		case LAB_4: {
			const std::string secondary_Menu[]{ "Получить информацию о задании", "Выполнить задание", "Назад", "Выход" };
			const int secondary_Menu_Count = sizeof(secondary_Menu) / sizeof(secondary_Menu[0]);

			bool inSecondaryMenu = true;
			while (inSecondaryMenu) {
				int secondary_Menu_choice = main_showMenu("4 - Контейнеры map, set, multimap, multiset, unordered_map, unordered_set, unordered_multimap.....", secondary_Menu, secondary_Menu_Count, false);

				switch (secondary_Menu_choice) {
				case SHOW_LAB_INFO: {
					std::cout << "Учет студентов ВУЗа\n\nВо всех вариантах индивидуальных заданий необходимо реализовать работу с контейнерами map, set, multimap, multiset, unordered_map, unordered_set, unordered_multimap, unordered_multiset.Уметь обосновать использование каждого типа контейнера. В каждом индивидуальном задании необходимо создать контейнеры, которые будут хранить объекты классов по предметной области, указанной в таблице ниже(класс должен содержать функционал по предметной области (добавление, удаление, редактирование, поиск, фильтр данных)).Для контейнера реализовать добавление, удаление, редактирование, вывод содержимого контейнера на экран и в файл, поиск и сортировку элементов. Необходимо создать удобное\n";
					system("pause");
					break;
				}
				case LAB_IMPLEMENTATION: {
					showLab4Menu();
					break;
				}
				case BACK_TO_MAIN_MENU: {
					std::cout << "Возвращаемся в предыдущее меню";
					loadingImitation();

					inSecondaryMenu = false;
					break;
				}
				case SECONDARY_EXIT: {
					std::cout << "Выходим из программы";
					loadingImitation();

					return 0;
				}
				default:
					break;
				}
			}
			break;
		}
		case MAIN_EXIT : {
			std::cout << "Выходим из программы";
			loadingImitation();

			return 0;
		}
		default:
			break;
		}
	}

	return 0;
}