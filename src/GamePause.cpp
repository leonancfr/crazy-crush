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
#include "GamePause.hpp"
#include "ScreenWindow.hpp"
#include "Callback.hpp"
#include "GameDefines.hpp"
#include "ScreenButtonDefault.hpp"
#include "GameControl.hpp"
#include "MainDraw.hpp"
#include "CallbackGameExitButtonClick.hpp"
#include "AudioManager.hpp"

namespace CrazyCrush {
namespace Game {
namespace Pause {

//! Callback executado quando a janela de pausa é exibida
/**
Basicamente remove as pedras da tela
*/
class CallbackGamePauseOnShow : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::setVolume("tetris",.5);
      for(unsigned i=0;i<Screen::num_rows;i++){
        for(unsigned j=0;j<Screen::num_columns;j++){
          Screen::matrix.at(i,j)->setDisplay(false);
        }
      }
    }
};

//! Callback executado quando a janela de pausa é fechada
/**
Basicamente exibe as pedras na tela
*/
class CallbackGamePauseOnClose : public Callback {
  public:
    void aProcess(){
      if(CrazyCrush::shutdownGame.get())
        return;
      CrazyCrush::AudioManager::setVolume("tetris",1.0);
      for(unsigned i=0;i<Screen::num_rows;i++){
        for(unsigned j=0;j<Screen::num_columns;j++){
          Screen::matrix.at(i,j)->setDisplay(true);
        }
      }
    }
};


//! Callback para continuar o jogo
class CallbackGamePauseButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::Pause::resume();
    }
};


//! Callback para sair do nível e exibir o menu principal
class CallbackGameMainMenuButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_hit",false,"sfx_hit.ogg");
      CrazyCrush::Game::Pause::close();
      CrazyCrush::AudioManager::stop("tetris");
      CrazyCrush::AudioManager::play("no_name");
      CrazyCrush::Game::Control::gameGoToMainScreen();
    }
};

ScreenWindow pauseScreen;
ScreenButtonDefault *btnContinue,*btnExit,*btnMainMenu;
bool initialized = false;

void initialize(){
  if(initialized)
    return;
  btnContinue = new ScreenButtonDefault();
  btnMainMenu = new ScreenButtonDefault();
  btnExit = new ScreenButtonDefault();
  btnContinue->setLabel("Continue");
  btnContinue->setOnClick(new CallbackGamePauseButtonClick());
  btnContinue->aSetScreenPosition(67,81);
  
  btnMainMenu->setLabel("Main Menu");
  btnMainMenu->setOnClick(new CallbackGameMainMenuButtonClick());
  btnMainMenu->aSetScreenPosition(331,81);
  
  btnExit->setLabel("Exit Game");
  btnExit->setOnClick(new CallbackGameExitButtonClick());
  btnExit->aSetScreenPosition(200,147);
  pauseScreen.setOnShow(new CallbackGamePauseOnShow());
  pauseScreen.setOnClose(new CallbackGamePauseOnClose());
  pauseScreen.inject(btnContinue,1);
  pauseScreen.inject(btnExit,1);
  pauseScreen.inject(btnMainMenu,1);
  initialized = true;
}

void pause(){
  initialize();
  pauseScreen.show();
}

void resume(){
  initialize();
  pauseScreen.close();
  Game::Control::resumeGame(true);
}

void close(){
  initialize();
  pauseScreen.close();
}

}}}