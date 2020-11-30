#include "map.h"

void Map::loadMap(std::string mapFile){
	/* Loaded Code Map*/
	std::vector<std::string> mapArray;
	/* Code to Texture (c)-> texture*/
	std::map<int, std::string> textTable;

	// read mapFile
	std::ifstream is(mapFile);  
	// saves map lines on a vector of strings
	while(is.peek()!=EOF){
		std::string line;
		std::getline(is, line);	
		mapArray.push_back(line);
	}
	is.close();

	width = mapArray[0].size();
	height = mapArray.size();

	// wall
  	textTable.insert(std::make_pair('0', "wall"));
	// corridor
  	textTable.insert(std::make_pair('1', "corridor"));
	// porta fechada 
  	textTable.insert(std::make_pair('2', "porta_fechada"));
  	// porta aberta
  	textTable.insert(std::make_pair('3', "porta_aberta"));
  	// camera cima
  	textTable.insert(std::make_pair('4', "camera_cima"));
  	// camera baixo
  	textTable.insert(std::make_pair('5', "camera_baixo"));
  	// camera direita
  	textTable.insert(std::make_pair('6', "camera_direita"));
  	// camera esquerda
  	textTable.insert(std::make_pair('7', "camera_esquerda"));
	// end tile ('E')
	textTable.insert(std::make_pair('E', "end"));
  	// camera cima direita
  	textTable.insert(std::make_pair('8', "camera_cima_direita"));
  	// camera cima esquerda
  	textTable.insert(std::make_pair('9', "camera_cima_esquerda"));
  	// camera baixo direita
  	textTable.insert(std::make_pair('A', "camera_baixo_direita"));
  	// camera baixo esquerda
  	textTable.insert(std::make_pair('B', "camera_baixo_esquerda"));
	//parses the map, flling the texture map
	for (int i=0; i < height; i++){
		for (int j=0; j < width; j++){
			// map has SDL style coordinates (x,y)
			textMap.insert(std::make_pair(std::make_pair(j,i), textTable[mapArray[i][j]]));
		}
	}
}

std::map<std::pair<int, int>, std::string>& Map::get_textMap(){ return textMap;}
int Map::getWidth(){return width;}
int Map::getHeight(){return height;}
void Map::setTileSize(int size){tileSize = size;}
