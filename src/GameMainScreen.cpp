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
#include "GameMainScreen.hpp"

#include "ScreenButtonDefault.hpp"
#include "CallbackGameExitButtonClick.hpp"
#include "GameControl.hpp"
#include "GameLevelFile.hpp"
#include "GameLevel.hpp"
#include "GameTimeAttack.hpp"
#include "Logger.hpp"
#include "GameTimeAttackRank.hpp"
#include "GameHowToPlay.hpp"
#include "AudioManager.hpp"
#include <sstream>

namespace CrazyCrush {
namespace Game {
namespace MainScreen {

//! Callback para exibir o menu de seleção de nível
class CallbackGamePlayLevelButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::MainScreen::screen.close();
      CrazyCrush::Game::Level::showLevelMenu();
    }
};

//! Callback para iniciar o jogo no modo TimeAttack
class CallbackGamePlayTimeAttackButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      if(CrazyCrush::Game::TimeAttack::play() == true){
        CrazyCrush::Game::MainScreen::screen.close();
      }
    }
};

//! Callback para abrir o menu de "Como jogar"
class CallbackGameHowToPlayButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::HowToPlay::show();
    }
};


//! Callback para abrir o menu de Rank do modo TimeAttack
class CallbackGameRankButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::TimeAttack::Rank::show();
    }
};

ScreenWindow screen;
ScreenButtonDefault *btnPlayLevel,*btnExit,*btnPlayTimeAttack,*btnHowToPlay,*btnRank;

void initialize(){
  btnExit = new ScreenButtonDefault();
  btnPlayLevel = new ScreenButtonDefault();
  btnPlayTimeAttack = new ScreenButtonDefault();
  btnHowToPlay = new ScreenButtonDefault();
  btnRank = new ScreenButtonDefault();
  
  btnExit->setLabel("Exit");
  btnExit->setScreenPosition(200,193);
  btnExit->setOnClick(new CallbackGameExitButtonClick());
  
  btnPlayLevel->setLabel("Play Level");
  btnPlayLevel->setScreenPosition(67,61);
  btnPlayLevel->setOnClick(new CallbackGamePlayLevelButtonClick());
  
  btnPlayTimeAttack->setLabel("Time Attack");
  btnPlayTimeAttack->setScreenPosition(331,61);
  btnPlayTimeAttack->setOnClick(new CallbackGamePlayTimeAttackButtonClick());
  
  btnHowToPlay->setLabel("How to Play");
  btnHowToPlay->setScreenPosition(67,131);
  btnHowToPlay->setOnClick(new CallbackGameHowToPlayButtonClick());
  
  btnRank->setLabel("View Rank");
  btnRank->setScreenPosition(331,131);
  btnRank->setOnClick(new CallbackGameRankButtonClick());
  
  screen.setSize(0,220);
  screen.setPosition(22,130);
  screen.inject(btnExit,1);
  screen.inject(btnPlayLevel,1);
  screen.inject(btnPlayTimeAttack,1);
  screen.inject(btnHowToPlay,1);
  screen.inject(btnRank,1);
  //screen.setPosition(22,95);
}

}}}