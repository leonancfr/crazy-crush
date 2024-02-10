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
#ifndef _GAME_CONTROL_HPP_
#define _GAME_CONTROL_HPP_ 1

namespace CrazyCrush {
  //! Espaço reservado às ações relacionadas ao jogo
  namespace Game {
    //! Espaço reservado ao gerenciador do jogo
    namespace Control {
      //! Inicializa as dependências internas do espaço
      void initialize();
      
      //! Controla o timer do jogo
      /**
      Utiliza os triggers para controlar o tempo de jogo (pausar quando a matriz é preenchida, por exemplo)
      */
      void processGameTimer();
      
      //! Executa as tarefas relacionadas ao perder uma fase
      /**
      Também é chamada no modo TimeAttack, mas propaga de forma um pouco diferente
      */
      void levelFail();
      
      //! Executa as tarefas relacionadas ao ganhar uma fase
      void levelWin();
      
      //! Útil para saber se o jogo está rodando (pausado ou ainda não iniciado)
      bool gameIsRunning();
      
      //! Função para definir que não há mais nenhum movimento possível
      /**
      \param value: valor a ser definido
      */
      void setNoMoreMoves(bool value);
      
      //! Função para definir que todas as pedras já cairam
      /**
      \param value: valor a ser definido
      */
      void setAllGemsFalled(bool value);
      
      //! Pausa o jogo (apenas o jogo)
      void pauseGame();
      
      //! Continua o jogo
      /**
      \param force: Força o jogo a continuar
      */
      void resumeGame(bool force = false);
      
      //! Executa as instruções necessárias para iniciar o jogo
      void gamePlay();
      
      //! Executa as instruções para parar o jogo e exibir o menu principal
      void gameGoToMainScreen();
      
      //! Define o tempo máximo da fase atual
      /**
      \param time: Tempo em milisegundos
      */
      void     setLevelTotalTime(unsigned time);
      
      //! Obtém o tempo máximo da fase atual
      /**
      \return Tempo total em milisegundos
      */
      unsigned getLevelTotalTime();
    }
  }
}

#endif