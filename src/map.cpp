#include "map.h"

Map::Map(std::string mapFile){
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
  	textTable.insert(std::make_pair(0, "wall"));
	// corridor
  	textTable.insert(std::make_pair(1, "corridor"));
	// porta 
  	textTable.insert(std::make_pair(2, "porta"));

	//parses the map, flling the texture map
	for (int i=0; i < height; i++){
		for (int j=0; j < width; j++){
			// map has SDL style coordinates (x,y)
			textMap.insert(std::make_pair(std::make_pair(j,i), textTable[mapArray[i][j]-'0']));
			// creates a new porta
			if (textTable[mapArray[i][j]-'0']=="porta")
				portaVec.push_back(std::shared_ptr<Porta> (new Porta(j*tileSize,i*tileSize)));
		}
	}
}

std::map<std::pair<int, int>, std::string> Map::get_textMap(){ return textMap;}
int Map::getWidth(){return width;}
int Map::getHeight(){return height;}
void Map::setTileSize(int size){tileSize = size;}
void setPortaVec(std::vector<std::shared_ptr<Porta>> portaVec){this.portaVec = portaVec;}
void setCameraVec(std::vector<std::shared_ptr<Camera>> cameraVec){this.cameraVec = cameraVec;}
