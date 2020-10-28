#include <memory>
#include "viewer.h"
#include "map.h"

class Controller {
	private:
		std::shared_ptr<Viewer> viewer;
		std::shared_ptr<Map> map;
	public:
		Controller();
		void gameLoop();
};
