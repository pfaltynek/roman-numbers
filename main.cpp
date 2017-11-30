#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#define TEST 1

class NumberConvertInfo {
  public:
	std::string roman;
	int arabic;
	int max_roman_count;

	NumberConvertInfo(std::string r, int a, int max) {
		max_roman_count = max;
		roman = r;
		arabic = a;
	}
};

std::vector<NumberConvertInfo> table;

bool ConvertToRoman(std::string input, std::string &output) {
	bool result = true;
	int arabic = 0;
	int cnt = 0;
	std::vector<NumberConvertInfo>::iterator it;

	arabic = stoi(input);

	if (arabic <= 0) {
		std::cout << "Arabic number must be greater than zero" << std::endl;
		return false;
	} else if (arabic > 9999) {
		std::cout << "Arabic number must be less or equal 9999" << std::endl;
		return false;
	}

	output.clear();
	it = table.begin();
	while ((arabic > 0) && (result)) {
		if (arabic >= it->arabic) {
			cnt++;
			output.append(it->roman);
			arabic -= it->arabic;
			if (cnt > it->max_roman_count) {
				result = false;
				std::cout << "Unknown problem (counter)" << std::endl;
			}
		} else {
			cnt = 0;
			it++;
			if (it == table.end()) {
				result = false;
				std::cout << "Unknown problem (table end)" << std::endl;
			}
		}
	}

	return result;
}

bool ConvertToArabic(std::string input, std::string &output) {
	bool result = true;
	int arabic = 0;
	int cnt = 0;
	unsigned int idx = 0;
	std::vector<NumberConvertInfo>::iterator it;
	std::string tmp;
	it = table.begin();

	while ((idx < input.size()) && (result)) {
		tmp = input.substr(idx, it->roman.size());
		if (tmp.compare(it->roman) == 0) {
			arabic += it->arabic;
			idx += it->roman.size();
			cnt++;
			if (cnt > it->max_roman_count) {
				result = false;
				std::cout << "Unknown problem (counter)" << std::endl;
			}
		} else {
			it++;
			cnt = 0;
			if (it == table.end()) {
				result = false;
				std::cout << "Unknown problem (table end)" << std::endl;
			}
		}
	}

	output = std::to_string(arabic);

	return result;
}

void PrepareConvertTable() {
	table.clear();
	table.push_back(NumberConvertInfo("M", 1000, 9));
	table.push_back(NumberConvertInfo("CM", 900, 1));
	table.push_back(NumberConvertInfo("D", 500, 1));
	table.push_back(NumberConvertInfo("CD", 400, 1));
	table.push_back(NumberConvertInfo("C", 100, 4));
	table.push_back(NumberConvertInfo("XC", 90, 1));
	table.push_back(NumberConvertInfo("L", 50, 1));
	table.push_back(NumberConvertInfo("XL", 40, 1));
	table.push_back(NumberConvertInfo("X", 10, 4));
	table.push_back(NumberConvertInfo("IX", 9, 1));
	table.push_back(NumberConvertInfo("V", 5, 1));
	table.push_back(NumberConvertInfo("IV", 4, 1));
	table.push_back(NumberConvertInfo("I", 1, 4));
}

void RunSelfTest() {
	std::vector<std::string> test_area(10000);
	std::string in, out;
	bool test_ok = true;

	std::cout << "Starting selftest ... please wait" << std::endl;

	test_area[0] = "";
	for (int i = 1; i <= 9999; i++) {
		in = std::to_string(i);
		if (ConvertToRoman(in, out)) {
			test_area[i] = out;
		} else {
			std::cout << "Failed to convert " << i << "to roman" << std::endl;
			test_ok = false;
			break;
		}
	}

	if (test_ok) {
		for (int i = 1; i <= 9999; i++) {
			in = test_area[i];
			if (ConvertToArabic(in, out)) {
				if (out.compare(std::to_string(i)) != 0) {
					test_ok = false;
				}
			} else {
				test_ok = false;
			}
			if (!test_ok) {
				std::cout << "Failed to convert " << i << "from roman (" << in << ")" << std::endl;
				break;
			}
		}
	}

	std::cout << "Self test finished." << std::endl;

	if (test_ok) {
		std::ofstream data_out;

		data_out.open("data.txt", std::ofstream::out);

		if (data_out.fail()) {
			std::cout << "Test data export failed." << std::endl;
			return;
		}

		for (int i = 1; i <= 9999; i++) {
			data_out << std::to_string(i) << "," << test_area[i] << std::endl;
		}
		data_out.close();
	}
}

int main(int argc, char *argv[]) {
	bool is_roman_number = false;
	std::string input = "MCI1", output;
	std::regex roman("^[MDCLXVI]+$");
	std::regex arabic("^(\\d)+$");
	std::smatch sm;

	PrepareConvertTable();

	switch (argc) {
		case 0:
		case 1:
			std::cout << "Missing parameter: number to convert to/from Roman" << std::endl;
			return -1;

		case 2:
			input = argv[1];
#if TEST
			if (!input.compare("--test")) {
				RunSelfTest();
				return 0;
			}
#endif
			if (regex_match(input, sm, arabic)) {
				is_roman_number = false;
			} else if (regex_match(input, sm, roman)) {
				is_roman_number = true;
			} else {
				std::cout << "Unknown number type." << std::endl;
				return -1;
			}
			break;

		default:
			std::cout << "Too many parameters, only one number can be converted" << std::endl;
			return -1;
			break;
	}

	if (is_roman_number) {
		if (ConvertToArabic(input, output)) {
			std::cout << input << " -> " << output << std::endl;
		} else {
			std::cout << "Roman number in invalid format" << std::endl;
		}
	} else {
		if (ConvertToRoman(input, output)) {
			std::cout << input << " -> " << output << std::endl;
		}
	}

	return 0;
}