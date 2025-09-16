#include"input_check.h"
double Stod(const std::string& s) {
	size_t i = 0;
	bool negative = false;

	while (i < s.size() && isspace(s[i])) i++;

	if (i < s.size() && s[0] == '-') {
		negative = true;
		i++;
	}

	double result = 0;
	while (i < s.size() && isdigit(s[i])) {
		result = result * 10 + (s[i] - '0');
		i++;
	}

	if (i < s.size() && s[i] == '.') {
		i++;
		double fraction = 0;
		double divisor = 1;

		while (i < s.size() && isdigit(s[i])) {
			fraction = fraction * 10 + (s[i] - '0');
			divisor *= 10;
			i++;
		}
		result += fraction / divisor;
	}

	return negative ? -result : result;
}

bool check_unsigned_input(const std::string& buf) {
	if (buf.empty() || buf.size() > MAX_DIGITS) { return false; }
	if (buf.size() > 1 && buf[0] == '0') { return false; }
	for (char c : buf) {
		if (!isdigit(c)) { return false; }
	}
	return buf.size() != MAX_UINT32.size() || buf <= MAX_UINT32;
}
bool check_int_input(const std::string& buf) {
	if (buf.empty() || buf.size() > MAX_DIGITS) { return false; }
	if (buf[0] == '-') {
		if (buf.size() > 2 && buf[1] == '0') { return false; }
		for (int i = 1; i < buf.size(); i++) {
			if (!isdigit(buf[i])) { return false; }
		}
		return buf.substr(1).size() < MIN_INT32.size() || (buf.substr(1).size() == MIN_INT32.size() && buf.substr(1) <= MIN_INT32);

	}
	else {
		if (buf.size() > 1 && buf[0] == '0') { return false; }
		for (char c : buf) {
			if (!isdigit(c)) { return false; }
		}
		return buf.size() != MAX_INT32.size() || buf <= MAX_INT32;
	}
}
bool check_double_float_input(const std::string& buf) {
	if (buf.empty() || buf.size() > MAX_DIGITS) { return false; }

	bool has_dot = false;

	if (buf[0] == '-') {
		if (buf.size() == 1) { return false; }
		for (int i = 1; i < buf.size(); i++) {
			if (buf[i] == '.') {
				if (has_dot) { return false; }
				if (i == 1 && i + 1 == buf.size()) { return false; }
				has_dot = true;
			}
			else if (!isdigit(buf[i])) { return false; }
		}
	}
	else {
		for (int i = 0; i < buf.size(); i++) {
			if (buf[i] == '.') {
				if (has_dot) { return false; }
				if (i == 0 && i + 1 == buf.size()) { return false; }
				has_dot = true;
			}
			else if (!isdigit(buf[i])) { return false; }
		}
	}
	return !std::isinf(std::stod(buf)) && !std::isnan(std::stod(buf));
}
bool check_englishLetters_specSymbols_input(const std::string& s) {
	if (s.empty()) return false;
	char c = s[0];
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '@') || (c == '_') || (c == '.');
}
bool check_russian_englishLetters_input(const std::string& s) {
	if (s.empty()) return false;
	char c = s[0];
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z' || c >= 'à' && c <= 'ÿ') || (c >= 'À' && c <= 'ß');
}
bool check_englishLetters_input(const std::string& s) {
	if (s.empty()) return false;
	char c = s[0];
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

//==============DEBUG==============
/*
unsigned a;
int b;
double value;
float d;
std::string str;

std::cout << "<unsigned>: ";
number_filteredInput<unsigned>(a);
std::cout << a << "\n\n";

std::cout << "<int>: ";
number_filteredInput<int>(b);
std::cout << b << "\n\n";

std::cout << "<-int>: ";
number_filteredInput<int>(b, 1);
std::cout << b << "\n\n";

std::cout << "<+int>: ";
number_filteredInput<int>(b, 0, 1);
std::cout << b << "\n\n";

std::cout << "<double>: ";
number_filteredInput<double>(value);
std::cout << value << "\n\n";

std::cout << "<float>: ";
number_filteredInput<float>(d);
std::cout << d << "\n\n\n\n";


std::cout << "<string (english + '-' +'_' + 1-9)>: ";
letter_filteredInput<std::string>(str);
std::cout << str << "\n\n";

std::cout << "<only english>: ";
letter_filteredInput<std::string>(str, 1);
std::cout << str << "\n\n";

std::cout << "<english + russian>: ";
letter_filteredInput<std::string>(str, 0, 1);
std::cout << str << "\n\n";

std::cout << "<*>: ";
letter_filteredInput<std::string>(str, 0, 0, 1);
std::cout << str << "\n\n";
*/