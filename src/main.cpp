#include "controller.h"
#include <string>

int main(int argc, char **argv){
	int create_window=0;
	std::string arg1;
	if (argc > 1) {
		arg1 = argv[1];
		if (arg1 == "monitor") create_window=1;
	}
	else create_window=0;
	Controller controller(create_window);
	if (argc > 1){
		if (arg1 == "monitor") controller.monitorLoop();
	}
	else
		controller.gameLoop();
	return 0;
}
