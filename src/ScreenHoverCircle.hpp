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
#ifndef _SCREEN_HOVER_CIRCLE_HPP_
#define _SCREEN_HOVER_CIRCLE_HPP_ 1

#include "ScreenHover.hpp"

//! Extensão da ScreenHover cuja região delimitada é uma circunferência
class ScreenHoverCircle : public ScreenHover {
  private:
    int x,y,xmin,ymin,xmax,ymax;
    unsigned r;
  public:
    //! Instancia a classe na posição informada e com o raio informado
    /**
    \param x: Coordenada X da tela onde ficará o centro do círculo
    \param y: Coordenada Y da tela onde ficará o centro do círculo
    \param radius: Raio da circunferência
    */
    ScreenHoverCircle(int x,int y,unsigned radius);
    
    //! Define a posição do centro da circuferência
    void setPosition(int x,int y);
    
    //! Define o raio da circunferência
    void setRadius(unsigned radius);
    
    //! Obtém a coordenada X do centro da circunferência
    int getPositionX();
    
    //! Obtém a coordenada Y do centro da circunferência
    int getPositionY();
    
    //! Obtém o raio da circunferência
    unsigned getRadius();
    
    bool isHover(int,int);
};

#endif