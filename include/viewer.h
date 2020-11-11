#ifndef VIEWER_H
#define VIEWER_H

#include <memory>
#include <iostream>
#include <map>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

		/*! Tile Source Rectangles */
		SDL_Rect wallRect; 
		/*! Tile Source Rectangles */
		SDL_Rect corridorRect; 
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

		/*! Dicionário de Texturas*/
		std::map<std::string, std::pair<SDL_Texture*, SDL_Rect*>> textDict;
		SDL_Texture* mainTitle;
		SDL_Texture* exclamationText;


		/*! Referencia para Texture Map */
		std::map<std::pair<int, int>, std::string> textMap;

		// Size of tile sides (tiles are squares)
		// OBS: tileRec.w is global tilesize
		/*! Retangulo alvo para texturas do fundo (bg) */
		SDL_Rect tileRect;
		int tileSize = 72;

		/*! Tamanho da tela */
		const int SCREEN_WIDTH = 10*tileSize;
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
		void render(Player& player);
		/*! Renderiza a tela principal
		*/
		void renderMain();
		/*! Renderiza o sinal de deteccao
		*/
		void renderExclamation(Camera& cam);
		/*! Guarda uma referencia para o dicionario do mapa
		*/
		void updateMap(std::map<std::pair<int, int>, std::string>& textMap);
};

#endif
