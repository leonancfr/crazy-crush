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
#ifndef _CALLBACK_MATRIX_OUT_HPP_
#define _CALLBACK_MATRIX_OUT_HPP_ 1

#include "Callback.hpp"

//! Callback usado durante o jogo para quando o mouse sai da área da matriz
class CallbackMatrixOutHover : public Callback {
  public:
    void aProcess();
};

//! Callback usado durante o jogo para quando o mouse clica fora da área da matriz
class CallbackMatrixOutClick : public Callback {
  public:
    void aProcess();
};

#endif