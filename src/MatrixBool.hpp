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
#ifndef _MATRIX_BOOL_HPP_
#define _MATRIX_BOOL_HPP_ 1

#include "Matrix.hpp"
#include <pthread.h>

//! Uma espécie de extensão da Matrix para o tipo boleano
class MatrixBool {
  private:
    Matrix<bool> principal;
    pthread_mutex_t access;
  public:
    //! Instancia a classe com 0 linhas e 0 colunas
    MatrixBool();
    
    //! Instancia a classe com linhas e colunas definidas
    /**
    \param lines: Número de linhas da matriz
    \param columns: Número de colunas da matriz
    */
    MatrixBool(unsigned lines,unsigned columns);
    
    //! Preenche toda a matriz com um valor
    /**
    \param value: Valor a preencher a matriz
    \return A própria matriz
    */
    MatrixBool& fill(bool value);
    
    //! Redimensiona a matriz
    /**
    \param lines: Número de linhas da matriz
    \param columns: Número de colunas da matriz
    \return A própria matriz
    */
    MatrixBool& resize(unsigned lines,unsigned columns);
    
    //! Define o valor de uma posição da matriz
    /**
    \param i: Índice da linha a acessar
    \param j: Índice da coluna a acessar
    \param value: Valor a ser definido
    \return A própria matriz
    */
    MatrixBool& set(unsigned i,unsigned j,bool value);
    
    //! Obtém o valor de uma posição na matriz
    /**
    \param i: Índice da linha a acessar
    \param j: Índice da coluna a acessar
    \return O valor na posição informada
    */
    bool get(unsigned,unsigned);
    
    #ifdef DEBUG
    void debug();
    #endif
};

#endif