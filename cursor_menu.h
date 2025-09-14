#pragma once
#include <string>

const int MENU_INDENT = 2;

void setCursorPos(int y, int x = MENU_INDENT);
int main_showMenu(const std::string& title, const std::string opts[], int count, bool rememberPosition = false);