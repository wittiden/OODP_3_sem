#pragma once
#include<iostream>
#include<thread>
#include<chrono>

#include<atomic>

std::atomic<bool> atm;

void loadingImitation() {
	for (int i = 0; i < 3; i++) {
		std::this_thread::sleep_for(std::chrono::milliseconds(700));
		std::cout << ".";
	}
}

//void activity_monitor() {
//	while (true) {
//		std::this_thread::sleep_for(std::chrono::seconds(30));
//
//		if () {
//
//		}
//		system("cls");
//		std::cout << "Вы долго не проявляли активность\n";
//		std::cout << "Выходим из программы";
//		loadingImitation();
//		exit(0);
//	}
//}