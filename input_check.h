#pragma once
#include <iostream>
#include <string>
#include <conio.h>

constexpr const int ENTER = 13;
constexpr const int BACKSPACE = 8;
constexpr const int MAX_DIGITS = 11;
const std::string MAX_INT32 = "2147483647";
const std::string MIN_INT32 = "2147483648";
const std::string MAX_UINT32 = "4294967295";

double Stod(const std::string& s);

bool check_unsigned_input(const std::string& s);
bool check_int_input(const std::string& s);
bool check_double_float_input(const std::string& s);

bool check_englishLetters_specSymbols_input(const std::string& s);
bool check_russian_englishLetters_input(const std::string& s);
bool check_englishLetters_input(const std::string& s);

template<typename T>
bool number_filteredInput(T& result) {
    std::string buf;

    while (true) {
        int c = _getch();

        if (c == 0 || c == 0xE0) {
            _getch();
            continue;
        }
        if (c == BACKSPACE && !buf.empty()) {
            buf.pop_back();
            std::cout << "\b \b";
            continue;
        }
        if (c == ENTER && !buf.empty()) {
            try {
                if constexpr (std::is_same_v<T, bool>) {
                    if (buf.size() == 1 && (buf[0] == '0' || buf[0] == '1')) {
                        result = (buf[0] == '1');
                        std::cout << std::endl;
                        return true;
                    }
                }
                else if constexpr (std::is_same_v<T, unsigned>) {
                    if (check_unsigned_input(buf)) {
                        result = std::stoul(buf);
                        std::cout << std::endl;
                        return true;
                    }
                }
                else if constexpr (std::is_same_v<T, int>) {
                    if (check_int_input(buf)) {
                        result = std::stoi(buf);
                        std::cout << std::endl;
                        return true;
                    }
                }
                else if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float>) {
                    if (check_double_float_input(buf)) {
                        result = Stod(buf);
                        std::cout << std::endl;
                        return true;
                    }
                }
            }
            catch (...) {
                return false;
            }
        }

        if constexpr (std::is_same_v<T, bool>) {
            if ((c == '0' || c == '1') && buf.empty()) {
                buf += static_cast<char>(c);
                std::cout << static_cast<char>(c);
            }
        }
        else if constexpr (std::is_same_v<T, unsigned>) {
            if (isdigit(c) && buf.size() < MAX_DIGITS) {
                std::string new_buf = buf + char(c);
                if (check_unsigned_input(new_buf)) {
                    buf += char(c);
                    std::cout << char(c);
                }
            }
        }
        else if constexpr (std::is_same_v<T, int>) {
            if ((isdigit(c) || (c == '-' && buf.empty())) && buf.size() < MAX_DIGITS) {
                std::string new_buf = (c == '-') ? "-" : buf + char(c);
                if (check_int_input(new_buf)) {
                    buf += char(c);
                    std::cout << char(c);
                }
            }
        }
        else if constexpr (std::is_same_v<T, double> || std::is_same_v<T, float>) {
            if ((isdigit(c) || c == '.' || (c == '-' && buf.empty())) && buf.size() < MAX_DIGITS) {
                std::string new_buf = buf + char(c);
                if (check_double_float_input(new_buf)) {
                    buf += char(c);
                    std::cout << char(c);
                }
            }
        }
    }
}
template <typename T>
void letter_filteredInput(std::string& buf, bool check_english = false, bool check_russian_english = false, bool mask_input = false) {
	buf.clear();

	while (true) {
		int c = _getch();

		if (c == 0 || c == 0xE0) {
			_getch();
			continue;
		}
		if (c == BACKSPACE && !buf.empty()) {
			buf.pop_back();
			std::cout << "\b \b";
			continue;
		}
		if (c == ENTER && !buf.empty()) {
			std::cout << std::endl;
			return;
		}

		if constexpr (std::is_same_v<T, std::string>) {
			bool isValid = false;

			if (check_english) {
				isValid = check_englishLetters_input(std::string(1, char(c)));
			}
			else if (check_russian_english) {
				isValid = check_russian_englishLetters_input(std::string(1, char(c)));
			}
			else {
				isValid = check_englishLetters_specSymbols_input(std::string(1, char(c)));
			}

			if (isValid && buf.size() < MAX_DIGITS) {
				buf += char(c);
				if (mask_input) {
					std::cout << '*';
				}
				else {
					std::cout << char(c);
				}
			}
		}
	}
}