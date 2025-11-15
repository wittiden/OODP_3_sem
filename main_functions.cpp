#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#include "cursor_menu.h"
#include "cursor_visibility.h"
#include "threads_options.h"
#include "lab1-2.h"

enum Lab1Menu { LAB1_ADD_ORDER, LAB1_DELETE_ORDER, LAB1_SHOW_ALL_ORDERS, LAB1_SEARCH_BY_ID, LAB1_DELETE_BY_ID, LAB1_SORT_BY_FLOWERS, LAB1_BACK, LAB1_EXIT };
enum Lab2Menu { LAB2_ADD_ORDER_TO_FILE, LAB2_DELETE_ORDER, LAB2_SHOW_ALL_ORDERS, LAB2_SEARCH_BY_ID, LAB2_DELETE_BY_ID, LAB2_SORT_BY_FLOWERS, LAB2_DELETE_BY_ID_IN_FILE, LAB2_VIEW_FILE_DATA, LAB2_BACK, LAB2_EXIT };
enum Lab3Menu { LAB3_VECTOR, LAB3_LIST, LAB3_ARRAY, LAB3_BACK, LAB3_EXIT };


static void showLab1Menu() {
    const std::string lab1_Menu[]{ "Добавить заказ", "Удалить заказ", "Показать все заказы", "Поиск заказа по id", "Удалить заказ по id", "Сортировка по количеству цветов", "Назад", "Выйти"};
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
        case LAB1_DELETE_BY_ID: {
            if (bqt.empty()) {
                std::cout << "\nНет созданных заказов!\n";
                system("pause");
                break;
            }

            showCursor();
            int idSearchForDelete;

            do {
                std::cout << "\nПоиск по id букета для удаления (введи 0 чтобы выйти): ";
                while (true) {
                    std::cin >> idSearchForDelete;
                    if (std::cin.good() && !std::cin.eof()) {
                        break;
                    }
                    std::cin.clear();
                    std::cerr << "Неправильный ввод данных\n";
                    std::cin.ignore(10, '\n');
                }
                for (int i = 0; i < bqt.size(); i++) {
                    if (idSearchForDelete == bqt[i].GetBouquetId()) {
                        bqt[i].deletePr(bqt, idSearchForDelete);
                    }
                }
            } while (idSearchForDelete != 0);
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
    const std::string lab2_Menu[]{ "Добавить заказ и записать в файл", "Удалить заказ", "Показать все заказы", "Поиск заказа по id", "Удалить заказ по id", "Сортировка по количеству цветов", "Удаление по id в файле", "Просмотр данных в файле", "Назад", "Выйти"};
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
        case LAB2_DELETE_BY_ID: {
            if (bqt.empty()) {
                std::cout << "\nНет созданных заказов!\n";
                system("pause");
                break;
            }

            showCursor();
            int idSearchForDelete;

            do {
                std::cout << "\nПоиск по id букета для удаления (введи 0 чтобы выйти): ";
                while (true) {
                    std::cin >> idSearchForDelete;
                    if (std::cin.good() && !std::cin.eof()) {
                        break;
                    }
                    std::cin.clear();
                    std::cerr << "Неправильный ввод данных\n";
                    std::cin.ignore(10, '\n');
                }
                for (int i = 0; i < bqt.size(); i++) {
                    if (idSearchForDelete == bqt[i].GetBouquetId()) {
                        bqt[i].deletePr(bqt, idSearchForDelete);
                    }
                }
            } while (idSearchForDelete != 0);
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


////////////////////////////3_LAB//////////////////////////////////////////////

void showLab3Secondary_VECTOR_Menu();
void showLab3Secondary_ARRAY_Menu();
void showLab3Secondary_LIST_Menu();

static void showLab3Menu() {
    const std::string lab3_Menu[]{ "vector", "list", "array", "Назад", "Выйти"};
    const int lab3_Count = sizeof(lab3_Menu) / sizeof(lab3_Menu[0]);

    bool inLab3Menu = true;
    while (inLab3Menu) {
        int lab1_choice = main_showMenu("Лабораторная работа 3", lab3_Menu, lab3_Count);

        switch (lab1_choice) {
        case LAB3_VECTOR: {
            showLab3Secondary_VECTOR_Menu();
        break;
        }
        case LAB3_LIST: {
            showLab3Secondary_LIST_Menu();
        break;
        }
        case LAB3_ARRAY: {
            showLab3Secondary_ARRAY_Menu();
        break;
        }
        case LAB3_BACK: {
            inLab3Menu = false;
            break;
        }
        case LAB3_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
enum LAB3_CONTAINER { LAB3_ADD_INFO, LAB3_DELETE_INFO, LAB3_CHANGE_INFO, LAB3_FIND_INFO, LAB3_SORT_INFO, LAB3_FILTER_INFO, LAB3_CONTAINER_BACK, LAB3_CONTAINER_EXIT };

static void showLab3Secondary_VECTOR_Menu() {
    const std::string lab3Secondary_VECTOR_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab3Secondary_VECTOR_Count = sizeof(lab3Secondary_VECTOR_Menu) / sizeof(lab3Secondary_VECTOR_Menu[0]);

    bsuir st;

    bool inLab3Secondary_VECTOR_Menu = true;
    while (inLab3Secondary_VECTOR_Menu) {
        int lab3_choice = main_showMenu("Лабораторная работа 3 (VECTOR)", lab3Secondary_VECTOR_Menu, lab3Secondary_VECTOR_Count);

        switch (lab3_choice) {
        case LAB3_ADD_INFO: {
        
            st.AddInf("vector");
            break;
        }
        case LAB3_DELETE_INFO: { 
            
            st.DeleteInf("vector");
            break;
        }
        case LAB3_CHANGE_INFO: {
           
            st.ChangeInf("vector");
            break;
        }
        case LAB3_FIND_INFO: {
            st.SearchInf("vector");
            break;
        }
        case LAB3_SORT_INFO: {

            st.SortInf("vetor");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("vector");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab3Secondary_VECTOR_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab3Secondary_ARRAY_Menu() {
    const std::string lab3Secondary_ARRAY_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab3Secondary_ARRAY_Count = sizeof(lab3Secondary_ARRAY_Menu) / sizeof(lab3Secondary_ARRAY_Menu[0]);

    bsuir st;

    bool inLab3Secondary_ARRAY_Menu = true;
    while (inLab3Secondary_ARRAY_Menu) {
        int lab3_choice = main_showMenu("Лабораторная работа 3 (ARRAY)", lab3Secondary_ARRAY_Menu, lab3Secondary_ARRAY_Count);

        switch (lab3_choice) {
        case LAB3_ADD_INFO: {

            st.AddInf("array");
            break;
        }
        case LAB3_DELETE_INFO: {

            std::cout << "В контейнере array нельзя удалять значения!\n";
            system("pause");
            break;
        }
        case LAB3_CHANGE_INFO: {

            st.ChangeInf("array");
            break;
        }
        case LAB3_FIND_INFO: {
            st.SearchInf("array");
            break;
        }
        case LAB3_SORT_INFO: {

            st.SortInf("array");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("array");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab3Secondary_ARRAY_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab3Secondary_LIST_Menu() {
    const std::string lab3Secondary_LIST_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab3Secondary_LIST_Count = sizeof(lab3Secondary_LIST_Menu) / sizeof(lab3Secondary_LIST_Menu[0]);

    bsuir st;

    bool inLab3Secondary_LIST_Menu = true;
    while (inLab3Secondary_LIST_Menu) {
        int lab3_choice = main_showMenu("Лабораторная работа 3 (LIST)", lab3Secondary_LIST_Menu, lab3Secondary_LIST_Count);

        switch (lab3_choice) {
        case LAB3_ADD_INFO: {

            st.AddInf("list");
            break;
        }
        case LAB3_DELETE_INFO: {

            st.DeleteInf("list");
            break;
        }
        case LAB3_CHANGE_INFO: {

            st.ChangeInf("list");
            break;
        }
        case LAB3_FIND_INFO: {
            st.SearchInf("list");
            break;
        }
        case LAB3_SORT_INFO: {

            st.SortInf("list");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("list");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab3Secondary_LIST_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}

////////////////////////////4_LAB//////////////////////////////////////////////

enum Lab4Menu { LAB4_SET, LAB4_MULTISET, LAB4_MAP, LAB4_MULTIMAP, LAB4_UNORDERED_MAP, LAB4_BACK, LAB4_EXIT };
void showLab4Secondary_SET_Menu();
void showLab4Secondary_MULTISET_Menu();
void showLab4Secondary_MAP_Menu();
void showLab4Secondary_MULTIMAP_Menu();
void showLab4Secondary_UNORDERED_MAP_Menu();

static void showLab4Menu() {
    const std::string lab4_Menu[]{ "set", "multiset", "map", "multimap", "unordered_map", "Назад", "Выйти"};
    const int lab4_Count = sizeof(lab4_Menu) / sizeof(lab4_Menu[0]);

    bool inLab4Menu = true;
    while (inLab4Menu) {
        int lab1_choice = main_showMenu("Лабораторная работа 4", lab4_Menu, lab4_Count);

        switch (lab1_choice) {
        case LAB4_SET: {
            showLab4Secondary_SET_Menu();
            break;
        }
        case LAB4_MULTISET: {
            showLab4Secondary_MULTISET_Menu();
            break;
        }
        case LAB4_MAP: {
            showLab4Secondary_MAP_Menu();
            break;
        }
        case LAB4_MULTIMAP: {
            showLab4Secondary_MULTIMAP_Menu();
            break;
        }
        case LAB4_UNORDERED_MAP: {
            showLab4Secondary_UNORDERED_MAP_Menu();
            break;
        }
        case LAB4_BACK: {
            inLab4Menu = false;
            break;
        }
        case LAB4_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}

static void showLab4Secondary_SET_Menu() {
    const std::string lab4Secondary_SET_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab4Secondary_SET_Count = sizeof(lab4Secondary_SET_Menu) / sizeof(lab4Secondary_SET_Menu[0]);

    bsuir st;

    bool inLab4Secondary_SET_Menu = true;
    while (inLab4Secondary_SET_Menu) {
        int lab4_choice = main_showMenu("Лабораторная работа 4 (SET)", lab4Secondary_SET_Menu, lab4Secondary_SET_Count);

        switch (lab4_choice) {
        case LAB3_ADD_INFO: {

            st.AddInf("set");
            break;
        }
        case LAB3_DELETE_INFO: {

            st.DeleteInf("set");
            break;
        }
        case LAB3_CHANGE_INFO: {

            std::cout << "В контейнере set нельзя менять значения!\n";
            system("pause");
            break;
        }
        case LAB3_FIND_INFO: {

            st.SearchInf("set");
            break;
        }
        case LAB3_SORT_INFO: {

            st.ShowInf("set");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("set");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab4Secondary_SET_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab4Secondary_MULTISET_Menu() {
    const std::string lab4Secondary_MULTISET_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab4Secondary_MULTISET_Count = sizeof(lab4Secondary_MULTISET_Menu) / sizeof(lab4Secondary_MULTISET_Menu[0]);

    bsuir st;

    bool inLab4Secondary_MULTISET_Menu = true;
    while (inLab4Secondary_MULTISET_Menu) {
        int lab4_choice = main_showMenu("Лабораторная работа 4 (MULTISET)", lab4Secondary_MULTISET_Menu, lab4Secondary_MULTISET_Count);

        switch (lab4_choice) {
        case LAB3_ADD_INFO: {

            st.AddInf("multiset");
            break;
        }
        case LAB3_DELETE_INFO: {

            st.DeleteInf("multiset");
            break;
        }
        case LAB3_CHANGE_INFO: {

            std::cout << "В контейнере multiset нельзя менять значения!\n";
            system("pause");
            break;
        }
        case LAB3_FIND_INFO: {

            st.SearchInf("multiset");
            break;
        }
        case LAB3_SORT_INFO: {

            st.ShowInf("multiset");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("multiset");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab4Secondary_MULTISET_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab4Secondary_MAP_Menu() {
    const std::string lab4Secondary_MAP_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab4Secondary_MAP_Count = sizeof(lab4Secondary_MAP_Menu) / sizeof(lab4Secondary_MAP_Menu[0]);

    bsuir st;

    bool inLab4Secondary_MAP_Menu = true;
    while (inLab4Secondary_MAP_Menu) {
        int lab4_choice = main_showMenu("Лабораторная работа 4 (map)", lab4Secondary_MAP_Menu, lab4Secondary_MAP_Count);

        switch (lab4_choice) {
        case LAB3_ADD_INFO: {

            st.AddInf("map");
            break;
        }
        case LAB3_DELETE_INFO: {

            st.DeleteInf("map");
            break;
        }
        case LAB3_CHANGE_INFO: {

            st.ChangeInf("map");
            break;
        }
        case LAB3_FIND_INFO: {

            st.SearchInf("map");
            break;
        }
        case LAB3_SORT_INFO: {

            st.ShowInf("map");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("map");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab4Secondary_MAP_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab4Secondary_MULTIMAP_Menu() {
    const std::string lab4Secondary_MULTIMAP_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab4Secondary_MULTIMAP_Count = sizeof(lab4Secondary_MULTIMAP_Menu) / sizeof(lab4Secondary_MULTIMAP_Menu[0]);

    bsuir st;

    bool inLab4Secondary_MULTIMAP_Menu = true;
    while (inLab4Secondary_MULTIMAP_Menu) {
        int lab4_choice = main_showMenu("Лабораторная работа 4 (multimap)", lab4Secondary_MULTIMAP_Menu, lab4Secondary_MULTIMAP_Count);

        switch (lab4_choice) {
        case LAB3_ADD_INFO: {

            st.AddInf("multimap");
            break;
        }
        case LAB3_DELETE_INFO: {

            st.DeleteInf("multimap");
            break;
        }
        case LAB3_CHANGE_INFO: {

            st.ChangeInf("multimap");
            break;
        }
        case LAB3_FIND_INFO: {

            st.SearchInf("multimap");
            break;
        }
        case LAB3_SORT_INFO: {

            st.ShowInf("multimap");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("multimap");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab4Secondary_MULTIMAP_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab4Secondary_UNORDERED_MAP_Menu() {
    const std::string lab4Secondary_UNORDEDRED_MAP_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Назад", "Выйти" };
    const int lab4Secondary_UNORDERED_MAP_Count = sizeof(lab4Secondary_UNORDEDRED_MAP_Menu) / sizeof(lab4Secondary_UNORDEDRED_MAP_Menu[0]);

    bsuir st;

    bool inLab4Secondary_UNORDEDRED_MAP_Menu = true;
    while (inLab4Secondary_UNORDEDRED_MAP_Menu) {
        int lab4_choice = main_showMenu("Лабораторная работа 4 (unordered_map)", lab4Secondary_UNORDEDRED_MAP_Menu, lab4Secondary_UNORDERED_MAP_Count);

        switch (lab4_choice) {
        case LAB3_ADD_INFO: {

            st.AddInf("unordered_map");
            break;
        }
        case LAB3_DELETE_INFO: {

            st.DeleteInf("unordered_map");
            break;
        }
        case LAB3_CHANGE_INFO: {

            st.ChangeInf("unordered_map");
            break;
        }
        case LAB3_FIND_INFO: {

            st.SearchInf("unordered_map");
            break;
        }
        case LAB3_SORT_INFO: {

            st.ShowInf("unordered_map");
            system("pause");
            break;
        }
        case LAB3_FILTER_INFO: {
            st.FilterInf("unordered_map");
            break;
        }
        case LAB3_CONTAINER_BACK: {
            inLab4Secondary_UNORDEDRED_MAP_Menu = false;
            break;
        }
        case LAB3_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}


////////////////////////////5_LAB//////////////////////////////////////////////

enum Lab5Menu { LAB5_QUEUE, LAB5_STACK, LAB5_PRIORITY_QUEUE, LAB5_BACK, LAB5_EXIT };
enum LAB5_CASE_MENU { LAB5_ADD_INFO, LAB5_DELETE_INFO, LAB5_CHANGE_INFO, LAB5_FIND_INFO, LAB5_SORT_INFO, LAB5_FILTER_INFO, LAB5_ADD_TO_FILE, LAB5_SHOW_FROM_FILE, LAB5_CONTAINER_BACK, LAB5_CONTAINER_EXIT };

void showLab5Secondary_QUEUE_Menu();
void showLab5Secondary_STACK_Menu();
void showLab5Secondary_PRIORITY_QUEUE_Menu();

static void showLab5Menu() {
    const std::string lab5_Menu[]{ "queue", "stack", "priority_queue", "Назад", "Выйти" };
    const int lab5_Count = sizeof(lab5_Menu) / sizeof(lab5_Menu[0]);

    bool inLab5Menu = true;
    while (inLab5Menu) {
        int lab1_choice = main_showMenu("5 - Контейнеры queue, stack, priority_queue", lab5_Menu, lab5_Count);

        switch (lab1_choice) {
        case LAB5_QUEUE: {
            showLab5Secondary_QUEUE_Menu();
            break;
        }
        case LAB5_STACK: {
            showLab5Secondary_STACK_Menu();
            break;
        }
        case LAB5_PRIORITY_QUEUE: {
            showLab5Secondary_PRIORITY_QUEUE_Menu();
            break;
        }
        case LAB5_BACK: {
            inLab5Menu = false;
            break;
        }
        case LAB5_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}

static void showLab5Secondary_QUEUE_Menu() {
    const std::string lab5Secondary_QUEUE_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Добавить в файл", "Вывести из файла", "Назад", "Выйти" };
    const int lab5Secondary_QUEUE_Count = sizeof(lab5Secondary_QUEUE_Menu) / sizeof(lab5Secondary_QUEUE_Menu[0]);

    bsuir st;

    bool inLab5Secondary_QUEUE_Menu = true;
    while (inLab5Secondary_QUEUE_Menu) {
        int lab5_choice = main_showMenu("Лабораторная работа 5 (queue)", lab5Secondary_QUEUE_Menu, lab5Secondary_QUEUE_Count);

        switch (lab5_choice) {
        case LAB5_ADD_INFO: {

            st.AddInf("queue");
            break;
        }
        case LAB5_DELETE_INFO: {

            st.DeleteInf("queue");
            break;
        }
        case LAB5_CHANGE_INFO: {

            st.ChangeInf("queue");
            break;
        }
        case LAB5_FIND_INFO: {

            st.SearchInf("queue");
            break;
        }
        case LAB5_SORT_INFO: {

            st.ShowInf("queue");
            break;
        }
        case LAB5_FILTER_INFO: {
            st.FilterInf("queue");
            break;
        }
        case LAB5_ADD_TO_FILE: {
            
            break;
        }
        case LAB5_SHOW_FROM_FILE: {
            
            break;
        }
        case LAB5_CONTAINER_BACK: {
            inLab5Secondary_QUEUE_Menu = false;
            break;
        }
        case LAB5_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab5Secondary_STACK_Menu() {
    const std::string lab5Secondary_STACK_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Добавить в файл", "Вывести из файла", "Назад", "Выйти" };
    const int lab5Secondary_STACK_Count = sizeof(lab5Secondary_STACK_Menu) / sizeof(lab5Secondary_STACK_Menu[0]);

    bsuir st;

    bool inLab5Secondary_STACK_Menu = true;
    while (inLab5Secondary_STACK_Menu) {
        int lab5_choice = main_showMenu("Лабораторная работа 5 (stack)", lab5Secondary_STACK_Menu, lab5Secondary_STACK_Count);

        switch (lab5_choice) {
        case LAB5_ADD_INFO: {

            st.AddInf("stack");
            break;
        }
        case LAB5_DELETE_INFO: {

            st.DeleteInf("stack");
            break;
        }
        case LAB5_CHANGE_INFO: {

            st.ChangeInf("stack");
            break;
        }
        case LAB5_FIND_INFO: {

            st.SearchInf("stack");
            break;
        }
        case LAB5_SORT_INFO: {

            st.ShowInf("stack");
            break;
        }
        case LAB5_FILTER_INFO: {
            st.FilterInf("stack");
            break;
        }
        case LAB5_ADD_TO_FILE: {

            break;
        }
        case LAB5_SHOW_FROM_FILE: {

            break;
        }
        case LAB5_CONTAINER_BACK: {
            inLab5Secondary_STACK_Menu = false;
            break;
        }
        case LAB5_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}
static void showLab5Secondary_PRIORITY_QUEUE_Menu() {
    const std::string lab5Secondary_PRIORITY_QUEUE_Menu[]{ "Добавить", "Удалить", "Редактировать", "Поиск", "Сортировка", "Фильтрация", "Добавить в файл", "Вывести из файла", "Назад", "Выйти" };
    const int lab5Secondary_PRIORITY_QUEUE_Count = sizeof(lab5Secondary_PRIORITY_QUEUE_Menu) / sizeof(lab5Secondary_PRIORITY_QUEUE_Menu[0]);

    bsuir st;

    bool inLab5Secondary_PRIORITY_QUEUE_Menu = true;
    while (inLab5Secondary_PRIORITY_QUEUE_Menu) {
        int lab5_choice = main_showMenu("Лабораторная работа 5 (priority_queue)", lab5Secondary_PRIORITY_QUEUE_Menu, lab5Secondary_PRIORITY_QUEUE_Count);

        switch (lab5_choice) {
        case LAB5_ADD_INFO: {

            st.AddInf("priority_queue");
            break;
        }
        case LAB5_DELETE_INFO: {

            st.DeleteInf("priority_queue");
            break;
        }
        case LAB5_CHANGE_INFO: {

            st.ChangeInf("priority_queue");
            break;
        }
        case LAB5_FIND_INFO: {

            st.SearchInf("priority_queue");
            break;
        }
        case LAB5_SORT_INFO: {

            st.ShowInf("priority_queue");
            break;
        }
        case LAB5_FILTER_INFO: {
            st.FilterInf("priority_queue");
            break;
        }
        case LAB5_ADD_TO_FILE: {

            break;
        }
        case LAB5_SHOW_FROM_FILE: {

            break;
        }
        case LAB5_CONTAINER_BACK: {
            inLab5Secondary_PRIORITY_QUEUE_Menu = false;
            break;
        }
        case LAB5_CONTAINER_EXIT: {
            std::cout << "Выходим из программы";
            loadingImitation();
            exit(0);
        }
        default:
            break;
        }
    }
}