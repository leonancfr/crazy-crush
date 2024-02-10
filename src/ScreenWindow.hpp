/* Universidade Federal do Rio de Janeiro
 * Escola Politécnica
 * Departamento de Eletrônica e Computação
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programação
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan França    (leonancfr@poli.ufrj.br)
 *          Gustavo Silva    (diguser@gmail.com)
 *          Michael Douglas  (michaeldouglas@poli.ufrj.br)
 */
#ifndef _SCREEN_WINDOW_HPP_
#define _SCREEN_WINDOW_HPP_ 1

#include "ScreenObject.hpp"
#include "AnimatorObject.hpp"
#include "Events.hpp"
#include <vector>

//! Classe para criar uma janela dentro do jogo
/**
O tamanho mínimo da janela depende do tipo da mesma. Caso seja definido um valor menor que o mínimo, o valor mínimo será assumido.

Todos os elementos internos da janela possuem posição e índices (no ZOrder) relativos aos valores da janela.
Estes ajustes só ocorrem no momento em que a mesmo é exibida
*/
class ScreenWindow : public Events {
  private:
    struct AAB {
      AnimatorObject* obj;
      int relativeIndex,lastIndex;
      bool visible;
    };
    ScreenObject top_left,top_middle,top_right;
    ScreenObject middle_left,middle_middle,middle_right;
    ScreenObject bottom_left,bottom_middle,bottom_right,darkBg;
    unsigned width,height;
    int posX,posY;
    bool isOpen;
    unsigned char screenType;
    std::vector<AAB> objList;
    void propagateType();
    void propagatePosition();
  public:
    //! Tipos de janelas existentes
    enum { type_1,type_2 };
    ScreenWindow();
    ~ScreenWindow();
    
    //! Define o tipo de janela
    ScreenWindow& setType(unsigned char type);
    
    //! Define o tamanho da janela
    /**
    \param width: Largura da janela
    \param height: Altura da janela
    */
    ScreenWindow& setSize(unsigned width,unsigned height);
    
    //! Define a posição do topo esquerdo da janela na tela
    ScreenWindow& setPosition(int x,int y);
    
    //! Exibe a janela e seus conteúdos
    ScreenWindow& show();
    
    //! Fecha a janela e seus conteúdos
    ScreenWindow& close();
    
    //! Anexa um AnimatorObject (Botão, Sprite ou Texto) à janela com um índice relativo
    /**
    \param object: AnimatorObject a associar
    \param zIndex: Índice relativo que o objeto irá assumir em relação ao índice da janela 
    */
    ScreenWindow& inject(AnimatorObject* object,int zIndex);
    
    //! Define a visibilidade de um elemento
    /**
    Procura pelo objeto na lista interna e atribui sua visibilidade
    \param object: AnimatorObject a alterar a visibilidade
    \param value: Visibilidade do objeto
    */
    ScreenWindow& setVisibility(AnimatorObject* object,bool value);
    
    //! Obtém a coordenada X do topo esquerdo da janela
    int getPositionX();
    
    //! Obtém a coordenada Y do topo esquerdo da janela
    int getPositionY();
    
    //! Obtém a largura da janela
    unsigned getWidth();
    
    //! Obtém a altura da janela
    unsigned getHeight();
    
    //! Obtém o tipo da janela
    unsigned char getType();
};

#endif