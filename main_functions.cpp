#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include "lab1-2.h"
#include "threads_options.h"

enum Lab1Menu { LAB1_ADD_ORDER, LAB1_DELETE_ORDER, LAB1_SHOW_ALL_ORDERS, LAB1_SEARCH_BY_ID, LAB1_SORT_BY_FLOWERS, LAB1_BACK, LAB1_EXIT };
enum Lab2Menu { LAB2_ADD_ORDER_TO_FILE, LAB2_DELETE_ORDER, LAB2_SHOW_ALL_ORDERS, LAB2_SEARCH_BY_ID, LAB2_SORT_BY_FLOWERS, LAB2_DELETE_BY_ID_IN_FILE, LAB2_VIEW_FILE_DATA, LAB2_BACK, LAB2_EXIT };

static void showLab1Menu() {
    const std::string lab1_Menu[]{ "Добавить заказ", "Удалить заказ", "Показать все заказы", "Поиск заказа по id", "Сортировка по количеству цветов", "Назад", "Выйти" };
    const int lab1_Count = sizeof(lab1_Menu) / sizeof(lab1_Menu[0]);

    static std::vector<Bouquet> bqt;
    static std::vector<Wrapper> wrppr;
    static std::vector<Customer> cstmr;

    bool inLab1Menu = true;
    while (inLab1Menu) {
        int lab1_choice = main_showMenu("Лабораторная работа 1", lab1_Menu, lab1_Count);

        switch (lab1_choice) {
        case LAB1_ADD_ORDER: {
            showCursor();

            int bouquetSize;

            if (cstmr.empty()) {
                Customer::addCustomer(cstmr);
            }

            std::cout << "\nСколько букетов вам нужно? ";
            while (true) {
                std::cin >> bouquetSize;
                if (!std::cin.bad() && bouquetSize > 0) {
                    break;
                }
                std::cin.clear();
                std::cerr << "Неправильный ввод данных\n";
                std::cin.ignore(10, '\n');
            }
            for (int i = 0; i < bouquetSize; i++) {
                Bouquet bouquet;
                Wrapper wrapper;

                bouquet.addPr();
                wrapper.addPr();

                bqt.push_back(bouquet);
                wrppr.push_back(wrapper);
            }

            hideCursor();

            std::cout << "\nЗаказ добавляется";
            loadingImitation();

            break;
        }
        case LAB1_DELETE_ORDER: {
            if (cstmr.empty()) {
                std::cout << "Нет созданных заказов!\n";
                system("pause");
                break;
            }
            else {
                showCursor();

                while (bqt.size()) {
                    bqt.pop_back();
                    wrppr.pop_back();
                }

                hideCursor();
            }

            std::cout << "\nЗаказ удаляется";
            loadingImitation();

            break;
        }
        case LAB1_SHOW_ALL_ORDERS: {
            std::cout << "\nЗагружаем заказы";
            loadingImitation();
            
            if (cstmr.empty()) {
                std::cout << "\nНет созданных заказов!\n";
                system("pause");
                break;
            }

            showCursor();

            for (int i = 0; i < bqt.size(); i++) {
                bqt[i].showPr();
                if (i < wrppr.size()) {
                    wrppr[i].showPr();
                }
            }
            Customer::showCustomer(cstmr);

            hideCursor();
            system("pause");
            break;
        }
        case LAB1_SEARCH_BY_ID: {
            if (bqt.empty()) {
                std::cout << "\nНет созданных заказов!\n";
                system("pause");
                break;
            }

            showCursor();
            int idSearch;

            do {
                std::cout << "\nПоиск по id букета (введи 0 чтобы выйти): ";
                while (true) {
                    std::cin >> idSearch;
                    if (std::cin.good() && !std::cin.eof()) {
                        break;
                    }
                    std::cin.clear();
                    std::cerr << "Неправильный ввод данных\n";
                    std::cin.ignore(10, '\n');
                }
                for (int i = 0; i < bqt.size(); i++) {
                    if (idSearch == bqt[i].GetBouquetId()) {
                        bqt[i].showPr();
                        wrppr[i].showPr();
                    }
                }
            } while (idSearch != 0);

            hideCursor();
            break;
        }
        case LAB1_SORT_BY_FLOWERS: {
            if (bqt.empty()) {
                std::cout << "\nНет созданных заказов на букеты!\n";
                system("pause");
                break;
            }
            if (bqt.size() < 2) {
                std::cout << "\nНедостаточно заказов на букеты!\n";
                system("pause");
                break;
            }

            std::cout << "\nСортирую";
            loadingImitation();

            std::vector<Bouquet> copy_bqt = bqt;

            bubbleSort(copy_bqt);

            for (int i = 0; i < bqt.size(); i++) {
                copy_bqt[i].showPr();
            }

            system("pause");

            break;
        }
        case LAB1_BACK: {
            std::cout << "Возвращаемся в предыдущее меню";
            loadingImitation();

            inLab1Menu = false;
            break;
        }
        case LAB1_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}

static void showLab2Menu() {
    const std::string lab2_Menu[]{ "Добавить заказ и записать в файл", "Удалить заказ", "Показать все заказы", "Поиск заказа по id", "Сортировка по количеству цветов", "Удаление по id в файле", "Просмотр данных в файле", "Назад", "Выйти"};
    const int lab2_Count = sizeof(lab2_Menu) / sizeof(lab2_Menu[0]);

    static std::vector<Bouquet> bqt;
    static std::vector<Wrapper> wrppr;
    static std::vector<Customer> cstmr;

    bool inLab2Menu = true;
    while (inLab2Menu) {
        int lab1_choice = main_showMenu("Лабораторная работа 2", lab2_Menu, lab2_Count);

        switch (lab1_choice) {
        case LAB2_ADD_ORDER_TO_FILE: {
            showCursor();

            int bouquetSize;

            if (cstmr.empty()) {
                Customer::addCustomer(cstmr);
            }

            std::cout << "\nСколько букетов вам нужно? ";
            while (true) {
                std::cin >> bouquetSize;
                if (!std::cin.bad() && bouquetSize > 0) {
                    break;
                }
                std::cin.clear();
                std::cerr << "Неправильный ввод данных\n";
                std::cin.ignore(10, '\n');
            }
            for (int i = 0; i < bouquetSize; i++) {
                Bouquet bouquet;
                Wrapper wrapper;

                bouquet.addPr();
                wrapper.addPr();

                bqt.push_back(bouquet);
                wrppr.push_back(wrapper);
            }

            hideCursor();

            std::cout << "\nЗаказ добавляется";
            loadingImitation();
            std::cout << "\nЗагрузка данных в файл";
            loadingImitation();

            break;
        }
        case LAB2_DELETE_ORDER: {
            if (cstmr.empty()) {
                std::cout << "Нет созданных заказов!\n";
                system("pause");
                break;
            }
            else {
                showCursor();

                while (bqt.size()) {
                    bqt.pop_back();
                    wrppr.pop_back();
                }

                hideCursor();
            }

            std::cout << "\nЗаказ удаляется";
            loadingImitation();

            break;
        }
        case LAB2_SHOW_ALL_ORDERS: {
            std::cout << "\nЗагружаем заказы";
            loadingImitation();

            if (cstmr.empty()) {
                std::cout << "\nНет созданных заказов!\n";
                system("pause");
                break;
            }

            showCursor();

            for (int i = 0; i < bqt.size(); i++) {
                bqt[i].showPr();
                if (i < wrppr.size()) {
                    wrppr[i].showPr();
                }
            }
            Customer::showCustomer(cstmr);

            hideCursor();
            system("pause");
            break;
        }
        case LAB2_SEARCH_BY_ID: {
            if (bqt.empty()) {
                std::cout << "\nНет созданных заказов!\n";
                system("pause");
                break;
            }

            showCursor();
            int idSearch;

            do {
                std::cout << "\nПоиск по id букета (введи 0 чтобы выйти): ";
                while (true) {
                    std::cin >> idSearch;
                    if (std::cin.good() && !std::cin.eof()) {
                        break;
                    }
                    std::cin.clear();
                    std::cerr << "Неправильный ввод данных\n";
                    std::cin.ignore(10, '\n');
                }
                for (int i = 0; i < bqt.size(); i++) {
                    if (idSearch == bqt[i].GetBouquetId()) {
                        bqt[i].showPr();
                        wrppr[i].showPr();
                    }
                }
            } while (idSearch != 0);

            hideCursor();
            break;
        }
        case LAB2_SORT_BY_FLOWERS: {
            if (bqt.empty()) {
                std::cout << "\nНет созданных заказов на букеты!\n";
                system("pause");
                break;
            }
            if (bqt.size() < 2) {
                std::cout << "\nНедостаточно заказов на букеты!\n";
                system("pause");
                break;
            }

            std::cout << "\nСортирую";
            loadingImitation();

            std::vector<Bouquet> copy_bqt = bqt;

            bubbleSort(copy_bqt);

            for (int i = 0; i < bqt.size(); i++) {
                copy_bqt[i].showPr();
            }

            system("pause");

            break;
        }
        case LAB2_DELETE_BY_ID_IN_FILE: {
            int deleteIndex;
            Bouquet bouquetFromFileWork;

            std::cout << "\nЗагрузка данных из файла";
            loadingImitation();

            std::cout << "\n\n";

            if (fileEmptyChecker()) {
                std::cout << "Файл пуст\n";
                system("pause");
                break;
            }

            bouquetFromFileWork.showFileInfo();

            showCursor();

            do {
                std::cout << "Введите id букета, котрый хотите удалить из файла (введи 0 чтобы выйти): ";
                while (true) {
                    std::cin >> deleteIndex;
                    if (std::cin.good() && !std::cin.eof()) {
                        break;
                    }
                    std::cin.clear();
                    std::cerr << "Неправильный ввод данных\n";
                    std::cin.ignore(10, '\n');
                }
                std::cout << std::endl;
                bouquetFromFileWork.removeByIndex(deleteIndex);
                if(deleteIndex != 0) {
                    bouquetFromFileWork.showFileInfo();
                }
            } while (deleteIndex != 0);

            hideCursor();

            break;
        }
        case LAB2_VIEW_FILE_DATA: {
            Bouquet bouquetFromFileWork;

            std::cout << "Загрузка данных из файла";
            loadingImitation();
            std::cout << "\n\n";

            if (fileEmptyChecker()) {
                std::cout << "\n\nФайл пуст\n";
                system("pause");
                break;
            }
            else {
                bouquetFromFileWork.showFileInfo();
            }

            system("pause");

            break;
        }
        case LAB2_BACK: {
            std::cout << "Возвращаемся в предыдущее меню";
            loadingImitation();

            inLab2Menu = false;
            break;
        }
        case LAB2_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}