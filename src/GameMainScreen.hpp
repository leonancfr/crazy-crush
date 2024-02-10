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
#ifndef _GAME_MAIN_SCREEN_HPP_
#define _GAME_MAIN_SCREEN_HPP_ 1

#include "ScreenWindow.hpp"

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado para a tela inicial do jogo
    namespace MainScreen {
      //! Objeto da tela inicial do jogo
      extern ScreenWindow screen;
      
      //! Inicializador das dependências do espaço
      void initialize();
    }
  }
}

#endif