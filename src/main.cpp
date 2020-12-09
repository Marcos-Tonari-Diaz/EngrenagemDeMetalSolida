#include "controller.h"
#include <string>

int main(int argc, char **argv){
	Controller controller;
	if (argc > 1){
		std::string arg1 = argv[1];
		if (arg1 == "monitor")
			controller.monitorLoop();
	}
	else
		controller.gameLoop();
	return 0;
}
