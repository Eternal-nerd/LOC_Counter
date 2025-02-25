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

int main(int argc, char* argv[]) {

	if (argc != 2) {
		std::cout << "ERROR: Expected 1 command line parameter (PATH), got: " << argc-1 << ". \n";
		return -1;
	}

	std::string dir = argv[1];

	fs::path toCheck = fs::current_path() / dir;

	if (!fs::is_directory(toCheck)) {
		std::cout << "ERROR: PATH " << toCheck.relative_path() << " does not exist. \n";
		return -1;
	}
	
	std::cout << "Checking contents of: " << toCheck.relative_path() << " directory. \n";

	int whitespace = 0;
	int total = 0;

	for (auto entry : fs::directory_iterator(toCheck)) {
		if (entry.path().has_extension()) {
			std::string filename = dir + entry.path().filename().string();

			std::cout << "Checking file: " << filename << "\n";

			std::ifstream inFile(filename);
			std::string line;
			while (std::getline(inFile, line)) {
				if (checkWhitespace(line)) {
					whitespace++;
				}
				total++;
			}
			inFile.close();
		}
	}
	
	std::cout << "Total LOC: " << total << "\n";
	std::cout << "Total lines of whitespace: " << whitespace << "\n";
	std::cout << "Total LOC - whitespace: " << total-whitespace << "\n";



	return 0;
}