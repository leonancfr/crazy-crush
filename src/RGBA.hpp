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
#ifndef _RGBA_HPP_
#define _RGBA_HPP_

#include "Irrlicht/SColor.h"
#include "Irrlicht/irrTypes.h"

//! Classe para manipular de forma fácil e rápida os 4 ponteiros necessários na hora de exibir um sprite na tela
class RGBA {
  private:
    irr::video::SColor* color;
  public:
    RGBA();
    ~RGBA();
    //! Obtém o ponteiro
    irr::video::SColor* getColor();
    //! Instancia o ponteiro interno, caso não esteja instanciado
    RGBA& initColor();
    
    //! Define o ponteiro interno como o ponteiro passado como argumento
    RGBA& setColor(irr::video::SColor*);
    
    //! Define o canal alpha de cada SColor interno
    RGBA& setAlpha(irr::u8);
    
    //! Define o canal vermelho de cada SColor interno
    RGBA& setRed(irr::u8);
    
    //! Define o canal verde de cada SColor interno
    RGBA& setGreen(irr::u8);
    
    //! Define o canal azul de cada SColor interno
    RGBA& setBlue(irr::u8);
    
    //! Define os canais azul, verde e vermelho de cada SColor interno
    RGBA& setRGB(irr::u8 R,irr::u8 G,irr::u8 B);
    
    //! Clona as cores do outro objeto no objeto atual
    RGBA& operator=(RGBA&);
};

#endif