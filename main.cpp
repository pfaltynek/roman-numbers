#include <iostream>
#include <regex>
#include <string>

bool ConvertToRoman(std::string input, std::string &output) {
	bool result = false;
	int arabic = 0;

	arabic = atoi(input.c_str());

	if (arabic <= 0) {
		std::cout << "Arabic number must be greater than zero" << std::endl;
		return false;
	} else if (arabic > 9999) {
		std::cout << "Arabic number must be less or equal 9999" << std::endl;
		return false;
	}

	

	return result;
}

bool ConvertToArabic(std::string input, std::string &output) {
	bool result = false;
	std::cout << "Roman number in invalid format" << std::endl;
	return result;
}

int main(int argc, char *argv[]) {
	bool is_roman_number = false;
	std::string input = "MCI1", output;
	std::regex roman("^[MDCLXVI]+$");
	std::regex arabic("^(\\d)+$");
	std::smatch sm;

	switch (argc) {
		case 0:
		case 1:
			std::cout << "Missing parameter: number to convert to/from Roman" << std::endl;
			return -1;

		case 2:
			input = argv[1];
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
		} else {
			std::cout << "Arabic number in invalid format" << std::endl;
		}
	}

	return 0;
}