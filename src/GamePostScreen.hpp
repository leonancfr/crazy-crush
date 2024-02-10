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
#ifndef _GAME_POST_SCREEN_HPP_
#define _GAME_POST_SCREEN_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado à tela exibida ao fim de cada jogo
    namespace PostScreen {
      //! Inicializa as dependências internas do espaço
      void initialize();
      
      //! Exibe a tela de quando se ganha um nível
      void showLevelWin();
      
      //! Exibe a tela de quando se falha no nível
      void showLevelFail();
      
      //! Exibe a tela de quando o tempo acaba no modo TimaAttak
      void showTimeAtackEnd();
      
      //! Fecha a janela
      void close();
    }
  }
}

#endif