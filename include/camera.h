#ifndef CAMERA_H
#define CAMERA_H

#include "element.h"
#include "json.hpp"

using nlohmann::json;


/*! \brief Classe do objeto camera.
*	Classe camera herda da classe Element.
*
*  Essa classe serve como objeto detector do jogador no mapa.
*/
class Camera : public Element {
	private:
		int direcao; /*!< direção (Direção do campo de visão) */
		int alcance; /*!< alcance (Alcance do campo de visão) */
		int detectado; /*!< detectado (Flag de detecção do player pela camera) */
		int avistado; /*!< avistado (Flag de avistamento do player pela camera) */
		int x_vis; /*!< x_visão (Coordenada x do inicio do cone de visão) */
		int y_vis; /*!< y_visão (Coordenada y do inicio do cone de visão) */
	public:
		 /*! \brief Construtor.
		 *         Inicializa um objeto "Camera".
		 *
		 * \param direcao Direção do campo de visão.
		 * \param alcance Alcance do campo de visão.
		 * \param x Coordenada x da camera.
		 * \param y Coordenada y da camera
		 */
		Camera(int direcao, int alcance, int x, int y, int onMap);
		/*! \brief Macro para json.
		*
		*/
		NLOHMANN_DEFINE_TYPE_INTRUSIVE(Camera, avistado, detectado);
		 /*! \brief Retorna o valor da direção.
		 *
		 */
		int get_direcao();
		 /*! \brief Retorna o valor do alcance.
		 */
		int get_alcance();
		 /*! \brief Retorna o valor da detecção.
		 *
		 *  O valor de detecção indica se o player voi avistado pela camera, e se esse avistamento foi válido.
		 */
		int get_detectado();
		 /*! \brief Retorna o valor de avistamento.
		 *
		 *  O valor de avistamento indica se o player está no campo de visão da camera.
		 */
		int get_avistado();
		 /*! \brief Retorna o valor do x de visão.
		 *
		 *  Esse valor se refera à posição que o cone de visão ira começar.
		 */
		int get_x_vis();
		 /*! \brief Retorna o valor do x de visão.
		 *
		 *  Esse valor se refera à posição que o cone de visão ira começar.
		 */
		int get_y_vis();
		 /*! \brief Seta o valor de avistamento.
		 */
		void set_avistado(int avistado);
		 /*! \brief Seta o x de visão.
		 */
		void set_x_vis(int x_vis);
		 /*! \brief Seta o y de visão.
		 */
		void set_y_vis(int y_vis);
		/*! \brief Seta o valor de detecção.
	 	*/
		void set_detectado(int detectado);
};

#endif
