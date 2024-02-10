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
#ifndef _GAME_POINTS_MATRIX_HPP_
#define _GAME_POINTS_MATRIX_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado à matriz de pontuação do jogo
    /**
    Essa matriz é independente da matriz do jogo
    */
    namespace Points {
      //! Inicializa as dependências internas do espaço
      void initialize();
      
      //! Verifica a matriz para saber se a fase está concluída
      void checkMatrix();
      
      //! Decrementa, em um ponto, uma posição da matriz
      /**
      \param i: Índice i da matriz
      \param j: Índice j da matriz
      */
      void decreasePoint(unsigned i,unsigned j);
      
      //! Define um valor para um ponto na matriz
      /**
      \param i: Índice i da matriz
      \param j: Índice j da matriz
      \param value: Valor a atribuir
      */
      void setPoint(unsigned i,unsigned j,unsigned char value);
      
      //! Obtém a pontuação nos índices desejado
      /**
      \param i: Índice i da matriz
      \param j: Índice j da matriz
      \return O valor nos índices
      */
      unsigned char getPoint(unsigned i,unsigned j);
      
      //! Se a matriz está completamente zerada
      bool isComplete();
      
      //! Zera a matriz
      void erase();
    }
  }
}

#endif