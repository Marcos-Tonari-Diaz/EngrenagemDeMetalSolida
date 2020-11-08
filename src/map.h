#ifndef MAP_H
#define MAP_H

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
		/* map width */
		int width;
		/* map height */
		int height;
		/* size of 1 side of tile (always a square)*/
		int tileSize;
		/* Texture Coordinates (x,y)-> textureFile*/
		std::map<std::pair<int, int>, std::string> textMap;
	public:
		/*! \brief Constructor
		*
		* Loads the bytemap and saves it into mapArray
		* \param map file (.map)
		*
		* */
		Map(std::string mapFile);
		std::map<std::pair<int, int>, std::string> get_textMap();
		int getWidth();
		int getHeight();
};

#endif
