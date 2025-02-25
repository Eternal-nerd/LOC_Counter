#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
	std::cout << "hellos worl\n";

	if (argc != 2) {
		std::cout << "ERROR: Expected 1 command line parameter, got: " << argc-1 << ". \n";
		return -1;
	}
	
	std::cout << "Checking contents of " << argv[1] << "/ directory. \n";

	


	return 0;
}