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
#ifndef _CALLBACK_PROCESS_MATRIX_HPP_
#define _CALLBACK_PROCESS_MATRIX_HPP_ 1

#include "Callback.hpp"

//! Callback executado após o movimento das pedras executado pelo usuário
class CallbackProcessMatrix : public Callback {
  private:
    unsigned i1,j1,i2,j2;
  public:
    ~CallbackProcessMatrix();
    //! Define as coordenadas de uma das pedras envolvidas no movimento
    /**
    \param i: Coordenada i
    \param j: Coordenada j
    */
    CallbackProcessMatrix& setMatrixPositionObj1(unsigned i,unsigned j);
    
    //! Define as coordenadas da outra pedra envolvida no movimento
    /**
    \param i: Coordenada i
    \param j: Coordenada j
    */
    CallbackProcessMatrix& setMatrixPositionObj2(unsigned i,unsigned j);
    void aProcess();
};

#endif