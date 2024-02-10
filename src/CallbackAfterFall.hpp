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
#ifndef _CALLBACK_AFTER_FALL_HPP_
#define _CALLBACK_AFTER_FALL_HPP_ 1

#include "Callback.hpp"

//! Callback para ser executado por cada peça após ela cair
class CallbackAfterFall : public Callback {
  private:
    unsigned i,j;
  public:
    //! Construtor
    /**
    Passar as coordenadas da pedra na matriz pois o processamento as usará
    \param i: Coordenada i da peça na matriz
    \param j: Coordenada j da peça na matriz
    */
    CallbackAfterFall(unsigned i,unsigned j);
    void aProcess();
};

#endif