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
#ifndef _PERCENTAGE_HPP_
#define _PERCENTAGE_HPP_ 1

namespace CrazyCrush {
  //! Espaço reservado para as operações de porcentagem
  /**
  Permite precisão maior que um simples cálculo usando float
  */
  namespace Percentage {
    //! Estrutura de porcentagem simples
    typedef struct {
      unsigned range,value;
    } Percent;
    
    //! Estrutura de porcentagem avançada
    /**
    Permite precisão maior
    */
    typedef struct {
      Percent p1,p2,p3,p4;
    } HPercent;
    
    //! Retorna true com uma chance definida pela porcentagem
    /**
    \param percent: Chance de retornar true
    */
    bool get(Percent& percent);
    
    //! Retorna true com uma chance definida pela porcentagem
    /**
    \param percent: Chance de retornar true
    */
    bool get(HPercent& percent);
    
    //! Converte um valor (entre 0 e 1) para uma estrutura Percent equivalente
    /**
    \param value: Porcentagem desejada (entre 0 e 1)
    \return Estrutura com a porcentagem desejada
    */
    Percent format(float value);
    
    //! Converte um valor (entre 0 e 1) para uma estrutura HPercent equivalente
    /**
    \param value: Porcentagem desejada (entre 0 e 1)
    \return Estrutura com a porcentagem desejada
    */
    HPercent formatH(float value);
    //! Converte um valor (entre 0 e 1) para uma estrutura HPercent equivalente com valor mínimo de erro
    /**
    A chance de retornar true (pela função get()) é de value+error
    \param value: Porcentagem desejada (entre 0 e 1)
    \param error: Margem de erro desejada
    \return Estrutura com a porcentagem desejada
    */
    HPercent formatH(float value,float error);
  }
}

#endif