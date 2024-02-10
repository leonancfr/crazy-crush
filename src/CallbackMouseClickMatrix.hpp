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
#ifndef _CALLBACK_MOUSE_CLICK_MATRIX_
#define _CALLBACK_MOUSE_CLICK_MATRIX_ 1

#include "Callback.hpp"

//! Callback para processar o click na tela sobre um elemento da matriz
class CallbackMouseClickMatrix : public Callback {
  private:
    int i,j;
  public:
    //! Construtuor
    /**
    Associa-se a respectiva coordenada da matriz
    \param i: Coordenada i
    \param j: Coordenada j
    */
    CallbackMouseClickMatrix(int i,int j);
    void aProcess();
};

#endif