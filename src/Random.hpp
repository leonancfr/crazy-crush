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
#ifndef _RANDOM_HPP_
#define _RANDOM_HPP_ 1

namespace CrazyCrush {
  //! Espaço reservado à geração de números aleatórios
  /**
  É uma melhor adaptação do uso das funções rand() e srand()
  */
  namespace Random {
    //! Obtém um valor aleatório entre 0 e max
    int get();
    
    //! Valor máximo que a função get() pode retornar
    extern const unsigned max;
  }
}

#endif