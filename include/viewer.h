#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <tuple>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <random>
#include "player.h"
#include "camera.h"

/*! \brief Classe para o objeto Viewer.
*	
* Viewer é responsável por renderizar a tela de jogo.
*
*/
class Viewer{
	public:
		SDL_Window* window;
		SDL_Renderer* renderer;

		/*! TileSheet */
		SDL_Texture* bgTiles;
		/*! TileSheet */
		SDL_Texture* doorTiles;
		/*! TileSheet */
		SDL_Texture* testTile;
		/*! TileSheet */
		SDL_Texture* playerSheet;
		/*! TileSheet */
		SDL_Texture* heliportText;

		SDL_Texture* camera_cimaTile;
		SDL_Texture* camera_cima_direitaTile;
		SDL_Texture* camera_cima_esquerdaTile;
		SDL_Texture* camera_baixoTile;
		SDL_Texture* camera_baixo_direitaTile;
		SDL_Texture* camera_baixo_esquerdaTile;
		SDL_Texture* camera_direitaTile;
		SDL_Texture* camera_esquerdaTile;

		/*! Player Animation Sprites Rectangles */
		std::vector<SDL_Rect*> playerSprites;
		/*! Corridor Textures*/
		std::map<std::pair<int, int>, int> corridorRects;
		/*! Wall Textures*/
		std::map<std::pair<int, int>, int> wallRects;

		/*! Tile Source Rectangles */
		SDL_Rect wallRect; 
		/*! Tile Source Rectangles */
		SDL_Rect wallRect2; 
		/*! Tile Source Rectangles */
		SDL_Rect wallRect3; 
		/*! Tile Source Rectangles */
		SDL_Rect wallRect4; 
		/*! Tile Source Rectangles */
		SDL_Rect wallRect5; 
		/*! Tile Source Rectangles */
		SDL_Rect wallRect6; 
		/*! Tile Source Rectangles */
		SDL_Rect corridorRect; 
		/*! Tile Source Rectangles */
		SDL_Rect corridorRect2; 
		/*! Tile Source Rectangles */
		SDL_Rect corridorRect3; 
		/*! Tile Source Rectangles */
		SDL_Rect portaFechadaRect; 
		/*! Tile Source Rectangles */		
		SDL_Rect portaAbertaRect; 
		/*! Tile Source Rectangles */
		SDL_Rect cameraCimaRect; 
		/*! Tile Source Rectangles */
		SDL_Rect cameraCimaDirRect; 
		/*! Tile Source Rectangles */		
		SDL_Rect cameraCimaEsqRect; 
		/*! Tile Source Rectangles */
		SDL_Rect cameraBaixoRect; 
		/*! Tile Source Rectangles */
		SDL_Rect cameraBaixoDirRect; 
		/*! Tile Source Rectangles */
		SDL_Rect cameraBaixoEsqRect; 
		/*! Tile Source Rectangles */
		SDL_Rect cameraEsqRect; 
		/*! Tile Source Rectangles */
		SDL_Rect cameraDirRect; 
		/*! Tile Source Rectangles */
		SDL_Rect emptyRect; 
		/*! Tile Source Rectangles */
		SDL_Rect topU_Rect; 
		/*! Tile Source Rectangles */
		SDL_Rect topUR_Rect; 
		/*! Tile Source Rectangles */
		SDL_Rect topR_Rect; 
		/*! Tile Source Rectangles */
		SDL_Rect topDR_Rect; 
		/*! Tile Source Rectangles */
		SDL_Rect topD_Rect; 
		/*! Tile Source Rectangles */
		SDL_Rect topDL_Rect; 
		/*! Tile Source Rectangles */
		SDL_Rect topL_Rect; 
		/*! Tile Source Rectangles */
		SDL_Rect topUL_Rect; 

		/*! Dicionário de Texturas: (nome)->(textura, retangulo, overlay)*/
		std::map<std::string, std::tuple<SDL_Texture*, SDL_Rect*, int>> textDict;
		SDL_Texture* mainTitle;
		SDL_Texture* exclamationText;

		/*! Referencia para Texture Map */
		std::map<std::pair<int, int>, std::string> textMap;

		// Size of tile sides (tiles are squares)
		// OBS: tileRec.w is global tilesize
		int tileSize = 72;
		/*! Retangulo alvo para texturas do fundo (bg) */
		SDL_Rect tileRect;

		/*! Tamanho da tela */
		const int SCREEN_WIDTH = 15*tileSize;
		/*! Tamanho da tela */
		const int SCREEN_HEIGHT = 10*tileSize;

		/*! Estado do teclado */
		const Uint8* state = SDL_GetKeyboardState(nullptr); // estado do teclado

		//metodos
		/*! \brief Construtor do Viewer
        * Configura e inicializa o renderizador.
		* Monta o dicionário de texturas.
     	* */
		Viewer();
		/*! \brief Destrutor do Viewer
        * Destroi texturas e o Renderizador.
     	* */
		~Viewer();
		/*! Renderiza a cena
		* \param player Jogador a ser renderizado
		*/
		void render(std::map<int ,std::shared_ptr<Player>>& monitorPlayers, int currentMap);
		/*! Renderiza a tela principal
		*/
		void renderMain();
		/*! Renderiza o sinal de deteccao
		*/
		void renderExclamation(Camera& cam);
		/*! Guarda uma referencia para o dicionario do mapa
		*/
		void updateMap(std::map<std::pair<int, int>, std::string>& textMap);
	private:
	  // pseudo random number generator
	  std::mt19937 generator;
	  std::normal_distribution<> corrDistr;
	  std::normal_distribution<> wallDist;

};

#endif
