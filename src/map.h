#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*! \brief Map Class
*
*  Map is responsible for mapping a code map to a texture map (to use as backgroud)
*  It's representation is also used in collision detection
*
*/

class Map{
	private:
		uint16_t mapWidth;
		uint16_t mapLength;
		/* size of 1 side of tile (always a square)*/
		uint16_t tileSize;
		/* Loaded Code Map*/
		std::vector<std::string> mapArray;
		/* Code to Texture (c)-> texture*/
		std::map<int, std::string> textTable;
		/* Texture Coordinates (x,y)-> textureFile*/
		std::map<std::pair<int, int>, std::string> textMap;
	public:
		/*! \brief Constructor
		*
		* Loads the bytemap and saves it into mapArray
		* \param bytemap file (.map)
		*
		* */
		Map(std::string mapFile);
		std::map<std::pair<int, int>, std::string> get_textMap();
};
