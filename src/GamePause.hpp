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
#ifndef _GAME_PAUSE_HPP_
#define _GAME_PAUSE_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado ao menu de pausa do jogo
    namespace Pause {
      //! Exibe a tela de pausa
      void pause();
      
      //! Fecha a tela de pausa e propaga ao controle do jogo
      void resume();
      
      //! Apenas fecha a tela de pausa
      void close();
    }
  }
}

#endif