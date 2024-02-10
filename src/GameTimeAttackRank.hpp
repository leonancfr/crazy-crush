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
#ifndef _GAME_TIME_ATTACK_RANK_HPP_
#define _GAME_TIME_ATTACK_RANK_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    namespace TimeAttack {
      //! Espaço reservado ao menu de Rank do modo TimeAttack
      namespace Rank {
        //! Inicializa as dependências internas do espaço
        void initialize();
        
        //! Exibe o menu de rank
        void show();
        
        //! Fecha o menu de rank
        void close();
      }
    }
  }
}

#endif