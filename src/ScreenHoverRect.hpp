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
#ifndef _SCREEN_HOVER_RECT_HPP_
#define _SCREEN_HOVER_RECT_HPP_ 1

#include "ScreenHover.hpp"

//! Extensão da ScreenHover cuja região delimitada é um retângulo
class ScreenHoverRect : public ScreenHover {
  private:
    int x,y;
    unsigned w,h;
  public:
    //! Instancia a classe na posição informada e com o tamanho informado
    /**
    \param x: Coordenada X da tela onde ficará o canto superior esquerdo do retângulo na tela
    \param y: Coordenada Y da tela onde ficará o canto superior esquerdo do retângulo na tela
    \param width: Largura do retângulo
    \param height: Altura do retângulo
    */
    ScreenHoverRect(int x,int y,unsigned width,unsigned height);
    
    //! Define as coordenadas do canto superior esquerdo do retângulo na tela
    void setPosition(int x,int y);
    
    //! Define o tamanho do retângulo
    void setSize(unsigned width,unsigned height);
    
    //! Obtém a coordenada X do canto superior esquerdo do retâgulo
    int getPositionX();
    
    //! Obtém a coordenada Y do canto superior esquerdo do retâgulo
    int getPositionY();
    
    //! Obtém a largura do retângulo
    unsigned getWidth();
    
    //! Obtém a altura do retângulo
    unsigned getHeight();
    
    bool isHover(int,int);
};

#endif