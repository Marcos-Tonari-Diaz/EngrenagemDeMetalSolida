#include "map.h"

Map::Map(std::string mapFile){
	std::ifstream is(mapFile);  
	// saves map lines on a vector of strings
	while(is.peek()!=EOF){
		std::string line;
		std::getline(is, line);	
		mapArray.push_back(line);
	}
	is.close();

	// wall
  	textTable.insert(std::make_pair(0, "wall"));
	// corridor
  	textTable.insert(std::make_pair(1, "corridor"));

	//parses the map, flling the texture map
	for (int i=0; i < mapArray.size(); i++){
		for (int j=0; j < mapArray[i].size(); j++){
			textMap.insert(std::make_pair(std::make_pair(j,i), textTable[mapArray[i][j]-'0']));
		}	
	}
	
}

std::map<std::pair<int, int>, std::string> Map::get_textMap(){ return textMap;}
