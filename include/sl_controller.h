#ifndef SL_H
#define SL_H

#include "element.h"
#include "json.hpp"

using nlohmann::json;

/*! \brief Classe para salvar e carregar estados.
*	Essa classe utiliza o polimorfismo gerado pela classe Element.
*
*  A calsse possuí duas funções, salvar e carregar.
*/
class SLcontroller{
	private:
		json file; /*!< File (Arquivo com os dados dos objetos salvos) */
	public:
		/*! \brief Inicializador do objeto "Save-Load Controller".
		 *		
		 *
		 *  O inicializador do objeto é padrão.
		 */
		SLcontroller() = default;
		/*! \brief Função que salva os objetos guardados.
		 *	
		 * \param address Path do arquivo em que se deseja salvar.
		 */
		void save(std::string address);
		/*! \brief Função que carrega os objetos guardados.
		 *
		 */
		void load(Element& s, std::string tag, std::string address);
		/*! \brief Função que adiciona um objeto a ser salvo.
		 *
		 * \param address Path do arquivo que se deseja ler.
		 * \param s Objeto a ser guardado.
		 * \param tag Identificador do objeto a ser guardado.
		 */
		void add(Element& s, std::string tag);
		/*! \brief Função que retorna o json de dados salvos.
		 *
		 */
		json get_file();
		/*! \brief Função que apaga a lista de objetos guardados.
		 *
		 */
		void clear();
};

#endif
