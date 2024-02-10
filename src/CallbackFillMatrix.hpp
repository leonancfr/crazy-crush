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
#ifndef _CALLBACK_FILLMATRIX_HPP_
#define _CALLBACK_FILLMATRIX_HPP_ 1

#include "Callback.hpp"
//! Callback usado para preencher toda a matriz de pedras
class CallbackFillMatrix : public Callback {
  public:
    void aProcess();
};

#endif