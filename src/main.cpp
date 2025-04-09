#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

// returns true if entire string is whitespace
bool checkWhitespace(const std::string& s) {
	for (auto c : s) {
		if (!std::isspace(c)) {
			return false;
		}
	}
	return true;
}

void checkEntry(const std::filesystem::directory_entry& entry, int* total, int* whitespace) {
	if (entry.path().has_extension()) {
		std::string filename = entry.path().generic_string();

		std::cout << "Checking file: " << filename << "\n";

		std::ifstream inFile(filename);
		std::string line;
		while (std::getline(inFile, line)) {
			if (checkWhitespace(line)) {
				*whitespace += 1;
			}
			*total += 1;
		}
		inFile.close();
	}
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout << "error, not enough arguments\n";
		return -1;
	}

	std::string dir = argv[1];

	bool recursive = false;
	std::string recursiveString = "";

	if (argc > 2) {
		std::string flag = argv[2];
		if (flag == "-r") {
			recursive = true;
			recursiveString = " RECURSIVELY";
		}
	}

	fs::path toCheck = fs::current_path() / dir;

	if (!fs::is_directory(toCheck)) {
		std::cout << "ERROR: PATH " << toCheck.relative_path() << " does not exist. \n";
		return -1;
	}
	
	std::cout << "Checking contents of: " << toCheck.relative_path() << " directory" << recursiveString << ". \n";

	int whitespace = 0;
	int total = 0;

	if (recursive) {
		for (auto entry : fs::recursive_directory_iterator(toCheck)) {
			checkEntry(entry, &total, &whitespace);
		}
	}
	else {
		for (auto entry : fs::directory_iterator(toCheck)) {
			checkEntry(entry, &total, &whitespace);
		}
	}
	
	std::cout << "Total LOC: " << total << "\n";
	std::cout << "Total lines of whitespace: " << whitespace << "\n";
	std::cout << "Total LOC - whitespace: " << total-whitespace << "\n";

	return 0;
}