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
#ifndef _SPRITE_ANIMATOR_HPP_
#define _SPRITE_ANIMATOR_HPP_ 1

#include "Irrlicht/irrTypes.h"
#include "Irrlicht/rect.h"

//! Simples animador de Sprite
/**
Apenas modifica as posições e/ou tamanhos da textura de um sprite
*/
class SpriteAnimator {
  private:
    float resourceWidthMultiplier;
    float resourceHeightMultiplier;
    float resourcePositionXMultiplier;
    float resourcePositionYMultiplier;
    unsigned resourceLoopRatio;
    int resourceLoopPlus;
  public:
    SpriteAnimator();
    ~SpriteAnimator();
    
    //! Define o fator de multiplicação do tamanho da textura
    /**
    \param width: Fator de multiplicação da largura
    \param height: Fator de multiplicação da altura
    */
    void setResourceSize(float width,float height);
    
    //! Define o fator de multiplicação da posição da textura
    void setResourcePosition(float x,float y);
    
    //! Define valores de loop da animação
    /**
    \param loop: Total de frames da animação
    \param size: Tamanho de cada frame
    */
    void setResourceLoop(unsigned loop,int size);
    
    //! Obtém o retângulo (posição e tamanho) que o sprite ocupará da textura
    /**
    \param time: Tempo atual usado para processar a posição
    \param x_up: Coordenada X do topo esquerdo
    \param y_up: Coordenada Y do topo esquerdo
    \param x_down: Coordenada X do bottom direito
    \param y_down: Coordenada Y do bottom direito
    */
    irr::core::rect<irr::s32> getResourceRect(irr::u32 time,int x_up,int y_up,int x_down,int y_down);
};

#endif