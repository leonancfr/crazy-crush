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
#ifndef _GAME_PAUSE_BUTTON_HPP_
#define _GAME_PAUSE_BUTTON_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    namespace Pause {
      //! Espaço reservado ao botão de pausa do jogo
      namespace Button {
        //! Inicializa as dependências internas do espaço
        void initialize();
        
        //! Exibe o botão na tela
        void show();
        
        //! Oculta o botão da tela
        void hide();
        
        //! Suspende o evento do botão (ver mais em ScreenHoverList)
        void suspend();
      }
    }
  }
}

#endif