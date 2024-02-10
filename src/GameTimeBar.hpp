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
#ifndef _GAME_TIME_BAR_HPP_
#define _GAME_TIME_BAR_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado ao controlador e a barra de tempo do jogo
    namespace TimeBar {
      //! Inicializa as dependências internas do espaço
      void initialize();
      
      //! Atualiza a largura da barra em relação ao tempo
      void updateLength();
      
      //! Exibe a barra de progresso na tela
      void show();
      
      //! Oculta a barra de progresso na tela
      void hide();
    }
  }
}

#endif