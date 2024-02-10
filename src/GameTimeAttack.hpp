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
#ifndef _GAME_TIME_ATTACK_HPP_
#define _GAME_TIME_ATTACK_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado ao controlador do modo de jogo TimeAttack
    namespace TimeAttack {
      //! Inicializa as dependências internas do espaço
      void initialize();
      
      //! Inicia o jogo no modo TimeAttack
      /**
      \return Se ocorreu com sucesso
      */
      bool play();
    }
  }
}

#endif