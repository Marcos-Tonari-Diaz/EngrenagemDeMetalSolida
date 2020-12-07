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

/*! \brief Classe Mapa
*
*  Mapa é responsável por transformar um arquivo mapa em código em um dicionário (x,y) -> textura
*
*/

class Map{
	private:
		/*! map width */
		int width;
		/*! map height */
		int height;
		/*! size of 1 side of tile (always a square)*/
		int tileSize;
		/*! Mapa (x,y)-> textureFile*/
		std::map<std::pair<int, int>, std::string> textMap;
		/*! indice do mapa */
		int index;

	public:
		/*! \brief loads the map 
		*
		* Carrega o mapa e o transforma num dicionário
		* \param mapFile file (.map)
		*
		* */
		void loadMap(std::string mapFile);
		/*! Retorna o dicionário por referência */
		std::map<std::pair<int, int>, std::string>& get_textMap();
		int getWidth();
		int getHeight();
		void setTileSize(int size);
		int getIndex(){return index;}
		Map(int index){this->index = index;}
};

#endif
