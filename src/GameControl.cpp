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
#include "GameControl.hpp"

#include "ScreenObject.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "Timer.hpp"
#include "GameDefines.hpp"
#include "Screen.hpp"
#include "GamePause.hpp"
#include "CoreProcess.hpp"
#include "Score.hpp"
#include "GameTimeBar.hpp"
#include "GamePauseButton.hpp"
#include "AnimatorObjectList.hpp"
#include "GamePostScreen.hpp"
#include "MorphTimer.hpp"
#include "GameMainScreen.hpp"
#include "GamePointsMatrix.hpp"
#include "AnimationCount.hpp"
#include "Logger.hpp"
#include "AudioManager.hpp"

namespace CrazyCrush {
namespace Game {
namespace Control {

ScreenObject WinOrFailText(TextureCache::sprites);
bool NoMoreMovesNotifier = false;
bool AllGemsFalledNotifier = false;
bool GameFirstFall = false;
bool GameIsPaused = false;
bool GameIsRunning = false;

unsigned const winWidth = 304;
unsigned const winHeight = 66;
unsigned const winResourceX = 8;
unsigned const winResourceY = 420;
unsigned const failWidth = 752-458;
unsigned const failHeight = 492-400;
unsigned const failResourceX = 458;
unsigned const failResourceY = 400;

//! Callback para exibir a tela de quando o jogo termina (seja ganhando o perdendo)
class CallbackShowGameEndDialog : public Callback {
  private:
    unsigned char type;
  public:
    //! Tipos de encerramentos possíveis
    enum { levelWin, levelFail, atackEnd };
    
    //! Instancia a classe e atribui o tipo de encerramento
    CallbackShowGameEndDialog(unsigned char t){
      type = t;
    }
    void aProcess(){
      switch(type){
        case levelWin:
          CrazyCrush::Game::PostScreen::showLevelWin();
          break;
        default:
        case levelFail:
          CrazyCrush::Game::PostScreen::showLevelFail();
          break;
        case atackEnd:
          CrazyCrush::Game::PostScreen::showTimeAtackEnd();
          break;
      };
    };
};

void initialize(){
  WinOrFailText.setDisplay(false);
  z_order.addObject(&WinOrFailText,z_order.index_select+1);
  AnimatorObjectList.addObject(&WinOrFailText);
}

void gameCleanArea(){
  Score::hide();
  Game::TimeBar::hide();
}

void gameStop(){
  CrazyCrush::AudioManager::stop("tetris");
  CrazyCrush::AudioManager::play("no_name");
  GameIsRunning = false;
  Game::Pause::Button::hide();
  pauseLevelTimer();
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      Screen::matrixHover.at(i,j)->setEnabled(false);
    }
  }
  Screen::outHover->setEnabled(false);
  Screen::unselectBlock();
  Screen::frameSelectorPointer.setDisplay(false);
  Screen::hintIcon.setDisplay(false);
}

void levelWin(){
  gameStop();
  WinOrFailText.setResourceSize(winWidth,winHeight)
               .setResourcePosition(winResourceX,winResourceY)
               .setScreenSize(winWidth,winHeight)
               .setScreenPosition(Screen::stageBackgroundLeft+(TextureCache::gemWidth*Screen::num_columns-winWidth)/2,Screen::stageBackgroundTop+(TextureCache::gemHeight*Screen::num_rows-winHeight)/2)
               .setDisplay(true)
               .appendCallback(new CallbackShowGameEndDialog(CallbackShowGameEndDialog::levelWin))
               .appendMorph(new MorphTimer(1000))
               .startAnimator(getTime());
}

void levelFail(){
  gameStop();
  if(Game::gameIsTimeAttack){
    Game::PostScreen::showTimeAtackEnd();
  }else{
    WinOrFailText.setResourceSize(failWidth,failHeight)
                 .setResourcePosition(failResourceX,failResourceY)
                 .setScreenSize(failWidth,failHeight)
                 .setScreenPosition(Screen::stageBackgroundLeft+(TextureCache::gemWidth*Screen::num_columns-failWidth)/2,Screen::stageBackgroundTop+(TextureCache::gemHeight*Screen::num_rows-failHeight)/2)
                 .setDisplay(true)
                 .appendCallback(new CallbackShowGameEndDialog(CallbackShowGameEndDialog::levelFail))
                 .appendMorph(new MorphTimer(1000))
                 .startAnimator(getTime());
  }
}

bool gameIsRunning(){
  return GameIsRunning;
}

void processGameTimer(){
  if(AllGemsFalledNotifier){
    AllGemsFalledNotifier = false;
    resumeLevelTimer();
  }
  if(NoMoreMovesNotifier){
    NoMoreMovesNotifier = false;
    pauseLevelTimer();
  }
}

void setNoMoreMoves(bool v){
  if(GameIsPaused)
    return;
  NoMoreMovesNotifier = v;
}

void setAllGemsFalled(bool v){
  if(!GameIsRunning)
    return;
  if(GameIsPaused)
    return;
  AllGemsFalledNotifier = v;
}

void pauseGame(){
  if(!GameIsRunning)
    return;
  if(GameIsPaused)
    return;
  GameIsPaused = true;
  pauseGameTimer();
  Game::Pause::pause();
}

void resumeGame(bool forced){
  if(forced){
    GameIsPaused = false;
    resumeGameTimer();
  }
}

void gamePlay(){
  GameFirstFall = true;
  pauseGameTimer();
  resetLevelTimer();
  pauseLevelTimer();
  core::lastFullCheck.set(getLevelTime());
  Screen::AnimationCount::set(0);
  core::fillMatrix();
  WinOrFailText.setDisplay(false);
  Score::resetAll();
  GameIsPaused = false;
  GameIsRunning = true;
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      Screen::matrixHover.at(i,j)->setEnabled(true);
      Screen::matrixHover.at(i,j)->suspend();
    }
  }
  Screen::outHover->setEnabled(true);
  Screen::outHover->suspend();
  Screen::stageBackground.setDisplay(true);
  Score::show();
  Game::TimeBar::show();
  Game::Pause::Button::show();
  Game::Pause::Button::suspend();
  resumeGameTimer();
  CrazyCrush::AudioManager::play("tetris",true,"Tetris.ogg");
  CrazyCrush::AudioManager::stop("no_name");
}

void gameGoToMainScreen(){
  if(GameIsRunning&&GameIsPaused){
    
  }
  GameIsRunning = false;
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      Screen::matrix.at(i,j)->setDisplay(false);
      Screen::matrix.at(i,j)->getAnimatorQueue().stopAnimation();
      Screen::matrixHover.at(i,j)->resetStack(false);
    }
  }
  Screen::outHover->resetStack(false);
  Screen::stageBackground.setDisplay(false);
  Screen::hintIcon.setDisplay(false);
  Score::hide();
  Game::TimeBar::hide();
  Game::Pause::Button::hide();
  Game::Points::erase();
  Game::MainScreen::screen.show();
}

/************************************
   LEVEL TIME SCOPE
************************************/

unsigned levelTotalTime = 50000;

void setLevelTotalTime(unsigned v){
  levelTotalTime = v;
}

unsigned getLevelTotalTime(){
  return levelTotalTime;
}


}}}