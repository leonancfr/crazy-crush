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
#ifndef _MORPH_LINEAR_HPP_
#define _MORPH_LINEAR_HPP_ 1

#include "ObjectMorph.hpp"

//! Classe para movimentar um objeto na tela de forma linear
/**
Observação: Velocidade precede duração
*/
class MorphLinear : public ObjectMorph {
  private:
    int finalPosX, finalPosY;
    float ratioX,ratioY;
    unsigned duration;
    
    //! Função interna de processamento da velocidade
    void internalTrigger(irr::u32);
  public:
    MorphLinear();
    
    //! Define a duração da transição
    /**
    \param duration: Duração em milisegundos
    \return O objeto
    */
    MorphLinear& setDuration(unsigned duration);
    
    //! Define a velocidade do movimento do objeto
    /**
    Evite valor negativo
    \param x: Velocidade no eixo X
    \param y: Velocidade no eixo Y
    \return O objeto
    */
    MorphLinear& setVelocity(float x,float y);
    
    //! Define a posição final da transição do objeto
    /**
    \param x: Coordenada X na tela
    \param y: Coordenada Y na tela
    \return O objeto
    */
    MorphLinear& setFinalPosition(int x,int y);
    
    //! Define a posição final da transição do objeto
    /**
    \param position: Objeto que possui as corrdenadas X e Y
    \return O objeto
    */
    MorphLinear& setFinalPosition(irr::core::position2d<irr::s32> position);
    
    irr::core::rect<irr::s32> getScreenRect(irr::u32);
};

#endif