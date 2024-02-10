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
#ifndef _ANIMATION_COUNT_HPP_
#define _ANIMATION_COUNT_HPP_ 1

//! Namespace principal do jogo
namespace CrazyCrush {
  //! Espaço reservado às ações que envolvem a tela
  namespace Screen {
    //! Espaço responsável por contar quantas pedras estão em movimento
    namespace AnimationCount {
      //! Retorna a quantidade de pedras em movimento
      unsigned get();
      
      //! Define uma quantidade de pedras em movimento
      /**
      Útil para zerar o a contagem
      */
      void set(unsigned);
      
      //! Incrementa a contagem em uma unidade
      /**
      \return O novo valor do contador
      */
      unsigned increase();
      
      //! Incrementa a contagem em N unidades
      /**
      \param n: Quantidade a ser incrementada
      \return O novo valor do contador
      */
      unsigned increase(unsigned n);
      
      //! Decrementa a contagem em uma unidade
      /**
      \return O novo valor do contador
      */
      unsigned decrease();
      
      //! Decrementa a contagem em N unidades
      /**
      \param n: Quantidade a ser decrementada
      \return O novo valor do contador
      */
      unsigned decrease(unsigned n);
    }
  }
}

#endif