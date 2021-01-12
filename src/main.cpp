#include "controller.h"
#include <string>

int main(int argc, char **argv){
	Controller controller;
	std::string arg1;
	std::string arg2;
	if (argc > 2) {
		arg1 = argv[1];
		arg2 = argv[2];
		if (arg1 == "monitor") controller.monitorLoop(arg2);
	}
	else controller.gameLoop();
	return 0;
}
