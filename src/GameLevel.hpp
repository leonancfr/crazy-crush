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
#ifndef _GAME_LEVEL_HPP_
#define _GAME_LEVEL_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado às manipulações básicas de fase
    namespace Level {
      //! Total de níveis que o jogo possui
      extern const unsigned totalLevel;
      
      //! Inicializa as dependências do espaço
      void      initialize();
      
      //! Obtém o número do nível atual
      unsigned  getActualLevelNumber();
      
      //! Prepara e inicia o jogo na fase informada
      /**
      \param level: Nível a ser jogado
      \return Se ocorreu com sucesso
      */
      bool      playLevel(unsigned level);
      
      //! Verifica se o nível atual é o último nível
      bool      hasNextLevel();
      
      //! Instruções rápidas para ir para o próximo nível
      void      gotoNextLevel();
      
      //! Exibe o menu para selecionar o nível
      void      showLevelMenu();
      
      //! Fecha o menu de seleção de nível
      void      closeLevelMenu();
    }
  }
}

#endif