#ifndef ELEMENT_H
#define ELEMENT_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

 /*! \brief Classe base de Elementos
   *
   *  Classe base de Elementos.
   *  Outros elementos herdam dessa classe.
   *  
   */

class Element{
    protected:
        /*! Retangulo: posicao (x,y) e tamanho (w,h) */
	int x;
	int y;
	int w;
	int h;
	/*! Tamanho do bounding box do Jogador */
	int boxSize;
    public:
        /*! \brief Construtor do Elemento
        * default
     	* */
        Element() = default;
        /*! \brief Construtor do Elemento
        * Overloaded: define posição.
        * \param x coordenada x
        * \param y coordenada y
     	* */
        Element(int x, int y);
        int getX();
        int getY();
        int getW();
        int getH();
	int getBoxSize();
        void setPosition(int x, int y);
	void setTextSize(int w, int h);
	/*! Função virtual para setar atributos de classes derivadas
	 * \param void* vetor de atributos
	 * */
	virtual void setAttributes(std::vector<int>& attributes){return;};
	/*! Função virtual para receber atributos de classes derivadas
	 * \return void* vetor de atributos
	 * */
	virtual void getAttributes(std::vector<int>& attributes){return;};
	SDL_Rect* getRect();
};

#endif
