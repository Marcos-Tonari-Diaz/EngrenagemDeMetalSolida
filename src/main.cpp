#include "controller.h"

int main(int argc, char **argv){
	Controller controller;
	if (argc > 1){
		if (argv[1] == "monitor")
			controller.monitorLoop();
	}
	else
		controller.gameLoop();
	return 0;
}
