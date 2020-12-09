#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "viewer.h"
#include "map.h"
#include "element.h"
#include "player.h"
#include "collisionController.h"
#include "camera_controller.h"
#include "camera.h"
#include "porta.h"
#include "porta_controller.h"
#include "eventos.h"
#include "sl_controller.h"
#include "transfer_controller.h"

 /*! \brief Classe para o controller
   *
   *  Controller Principal.
   *  Responsável pelo loop principal do jogo.
   *  Guarda ponteiros para todos os objetos.
   *  
   */

class Controller {
	private:
		std::shared_ptr<Viewer> viewer;
		std::shared_ptr<Eventos> event;
		std::shared_ptr<Map> map;
		std::shared_ptr<Player> player;
		std::shared_ptr<collisionController> collisioncontroller;

		std::shared_ptr<Camera_controller> cameracontroller;
		std::shared_ptr<Porta_controller> portacontroller;
		std::shared_ptr<SLcontroller> slcontroller;
		std::shared_ptr<TRcontroller> trcontroller;

		/*! Guarda todas as cameras */
		std::vector<std::shared_ptr<Camera>> cameraVec;
		/*! Guarda todas as portas */
		std::vector<std::shared_ptr<Porta>> portaVec;

		/*! Estado do teclado */
  		const Uint8* state = NULL;
		/*! Estado do teclado */
		bool rodando = true;
		/*! Usado para o controle de eventos */
  		SDL_Event evento; 

		// porta timer
		int portaEventCounter = 0;
		int portaGo = 0;

		/*! Tamanho do lado do Tile */
		int tileSize;
		/*! Tamanho do bounding box do Jogador */
		int boxSize;
	public:
	    /*! \brief Construtor do Controller
     	*
     	* Aloca memória para os objetos principais.
     	* Configura objetos.
		* 
     	* \return Nada (este é um construtor!)
     	* */
		Controller();
	    /*! \brief Loop principal
     	*
		* Loop principal do jogo.
		* Roda os controllers secundáros.
		*
     	* */
		void gameLoop();
		void monitorLoop();
		/*! \brief Tela Principal
     	*
		* Renderiza a tela principal até que o jogador aperte espaço.
		*
     	* */
		void titleScreen();
};
