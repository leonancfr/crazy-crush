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
#include "GamePostScreen.hpp"
#include "ScreenWindow.hpp"
#include "ScreenText.hpp"
#include "Screen.hpp"
#include "Score.hpp"
#include "TextureCache.hpp"
#include "ScreenButtonSimple.hpp"
#include "GameControl.hpp"
#include "GameTimeAttack.hpp"
#include "GameSave.hpp"
#include "GameLevel.hpp"
#include "Timer.hpp"
#include "AudioManager.hpp"

#include <sstream>

namespace CrazyCrush {
namespace Game {
namespace PostScreen {

ScreenWindow window;

ScreenText *lblPoints,*lblYourScore,*lblLine1D,*lblLine2D,*lblLine3D,*lblLine4D,*lblLine1E,*lblLine2E,*lblLine3E,*lblLine4E;
ScreenButtonSimple *btnMainMenu,*btnTimeAttack,*btnRetryLevel,*btnNextLevel;
ScreenObject *newScore;

const unsigned width_all = 300;


const int lblYourScore_Y = 5;
const int lblPoints_Y = 20;
const int lblLine1D_Y = 60;
const int lblLine1D_X = 50;
const int lblLine2D_Y = lblLine1D_Y+17;
const int lblLine2D_X = lblLine1D_X;
const int lblLine3D_Y = lblLine2D_Y+17;
const int lblLine3D_X = lblLine1D_X;
const int lblLine4D_Y = lblLine3D_Y+17;
const int lblLine4D_X = lblLine1D_X;
const int btnTimeAttack_Y = lblLine4D_Y+20;
const int btnFail_Y = 77;
const int btnWin_Y = lblLine3D_Y+20;
const int btnMainMenu_Y_timed = btnTimeAttack_Y+34;
const int btnMainMenu_Y_Fail = btnFail_Y+34;
const int btnMainMenu_Y_Win = btnWin_Y+34;
const unsigned height_timeAttack = btnMainMenu_Y_timed+36;
const unsigned height_levelFail = btnMainMenu_Y_Fail+36;
const unsigned height_levelWin = btnMainMenu_Y_Win+36;


//! Callback para ir para o menu principal
class CallbackGameMainMenuButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::PostScreen::close();
      CrazyCrush::Game::Control::gameGoToMainScreen();
    }
};

//! Callback para reiniciar o jogo no modo TimeAttack
class CallbackGameTimeAttackButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::TimeAttack::play();
      CrazyCrush::Game::PostScreen::close();
    }
};

//! Callback para reiniciar o jogo no nível atual
class CallbackGameLevelReTryButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::Level::playLevel(CrazyCrush::Game::Level::getActualLevelNumber());
      CrazyCrush::Game::PostScreen::close();
    }
};

//! Callback para iniciar o jogo no próximo nível, se existir
class CallbackGameLevelNextButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      if(CrazyCrush::Game::Level::hasNextLevel()){
        CrazyCrush::Game::Level::gotoNextLevel();
        CrazyCrush::Game::PostScreen::close();
      }
    }
};

void initialize(){
  window.setType(ScreenWindow::type_2);
  window.setSize(width_all,height_timeAttack);
  window.setPosition((Screen::screenWidth-width_all)/2,(Screen::screenHeight-height_timeAttack)/2);
  
  lblYourScore = new ScreenText(TextureCache::font1);
  lblYourScore->setString("Your Score:");
  lblYourScore->setScreenAlign(ScreenText::center).setScreenPosition(width_all/2,lblYourScore_Y).setColor(255,255,128,0);
  window.inject(lblYourScore,1);
  
  lblPoints = new ScreenText(TextureCache::fontSFComic);
  lblPoints->setScreenAlign(ScreenText::center).setScreenPosition(width_all/2,lblPoints_Y).setColor(255,0,71,105);
  window.inject(lblPoints,1);
  
  lblLine1E = new ScreenText(TextureCache::font1);
  lblLine1E->setString("").setScreenPosition(lblLine1D_X,lblLine1D_Y).setColor(255,0,0,0);
  lblLine2E = new ScreenText(TextureCache::font1);
  lblLine2E->setString("").setScreenPosition(lblLine2D_X,lblLine2D_Y).setColor(255,0,0,0);
  lblLine3E = new ScreenText(TextureCache::font1);
  lblLine3E->setString("").setScreenPosition(lblLine3D_X,lblLine3D_Y).setColor(255,0,0,0);
  lblLine4E = new ScreenText(TextureCache::font1);
  lblLine4E->setString("").setScreenPosition(lblLine4D_X,lblLine4D_Y).setColor(255,0,0,0);
  
  lblLine1D = new ScreenText(TextureCache::font1);
  lblLine1D->setString("").setScreenPosition(width_all-lblLine1D_X,lblLine1D_Y).setColor(255,0,0,0).setScreenAlign(ScreenText::right);
  lblLine2D = new ScreenText(TextureCache::font1);
  lblLine2D->setString("").setScreenPosition(width_all-lblLine2D_X,lblLine2D_Y).setColor(255,0,0,0).setScreenAlign(ScreenText::right);
  lblLine3D = new ScreenText(TextureCache::font1);
  lblLine3D->setString("").setScreenPosition(width_all-lblLine3D_X,lblLine3D_Y).setColor(255,0,0,0).setScreenAlign(ScreenText::right);
  lblLine4D = new ScreenText(TextureCache::font1);
  lblLine4D->setString("").setScreenPosition(width_all-lblLine4D_X,lblLine4D_Y).setColor(255,0,0,0).setScreenAlign(ScreenText::right);
  
  window.inject(lblLine1D,1);
  window.inject(lblLine2D,1);
  window.inject(lblLine3D,1);
  window.inject(lblLine4D,1);
  window.inject(lblLine1E,1);
  window.inject(lblLine2E,1);
  window.inject(lblLine3E,1);
  window.inject(lblLine4E,1);
  
  btnMainMenu = new ScreenButtonSimple();
  btnMainMenu->setLabel("Main Menu")
              .setLabelOffset(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelOffsetHover(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelColor(255,255,255,255)
              .setLabelColorHover(255,255,255,255)
              .setButtonColor(ScreenButtonSimple::gray)
              .setButtonColorHover(ScreenButtonSimple::gray_light)
              .setButtonSize(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setButtonSizeHover(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setOnClick(new CallbackGameMainMenuButtonClick());
  btnMainMenu->getLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);
  window.inject(btnMainMenu,1);
  
  btnTimeAttack = new ScreenButtonSimple();
  btnTimeAttack->setLabel("Try Again")
              .setLabelOffset(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelOffsetHover(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelColor(255,255,255,255)
              .setLabelColorHover(255,255,255,255)
              .setButtonColor(ScreenButtonSimple::green)
              .setButtonColorHover(ScreenButtonSimple::green_light)
              .setButtonSize(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setButtonSizeHover(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setOnClick(new CallbackGameTimeAttackButtonClick());
  btnTimeAttack->getLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);
  window.inject(btnTimeAttack,1);
  
  btnRetryLevel = new ScreenButtonSimple();
  btnRetryLevel->setLabel("Try Again")
              .setLabelOffset(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelOffsetHover(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelColor(255,255,255,255)
              .setLabelColorHover(255,255,255,255)
              .setButtonColor(ScreenButtonSimple::red)
              .setButtonColorHover(ScreenButtonSimple::red_light)
              .setButtonSize(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setButtonSizeHover(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setOnClick(new CallbackGameLevelReTryButtonClick());
  btnRetryLevel->getLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);
  window.inject(btnRetryLevel,1);
  
  btnNextLevel = new ScreenButtonSimple();
  btnNextLevel->setLabel("Next Level")
              .setLabelOffset(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelOffsetHover(0,ScreenButtonSimple::defaultScreenHeight(0)/2)
              .setLabelColor(255,255,255,255)
              .setLabelColorHover(255,255,255,255)
              .setButtonColor(ScreenButtonSimple::green)
              .setButtonColorHover(ScreenButtonSimple::green_light)
              .setButtonSize(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setButtonSizeHover(ScreenButtonSimple::defaultScreenWidth(0),ScreenButtonSimple::defaultScreenHeight(0))
              .setOnClick(new CallbackGameLevelNextButtonClick());
  btnNextLevel->getLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);
  window.inject(btnNextLevel,1);
  
  newScore = new ScreenObject(TextureCache::sprites);
  newScore->setResourcePosition(506,552).setResourceSize(755-506,756-552).setDisplay(false).setScreenSize(50,50);
  window.inject(newScore,1);
}

void showLevelWin(){
  window.setSize(width_all,height_levelWin);
  window.setPosition((Screen::screenWidth-width_all)/2,(Screen::screenHeight-height_levelWin)/2);
  
  unsigned points = Score::getScore()+(Game::Control::getLevelTotalTime()-getLevelTime());
  
  std::stringstream SS;
  std::string S;
  SS << points;
  lblPoints->setString(SS.str().c_str()).setColor(255,0,71,105);
  
  S="";
  SS.str(S);
  //SS << 
  lblLine1E->setString("Points:");
  lblLine2E->setString("Time:");
  lblLine3E->setString("Record:");
  
  SS << Score::getScore();
  lblLine1D->setString(SS.str().c_str());
  
  S = "";
  SS.str(S);
  SS << (Game::Control::getLevelTotalTime()-getLevelTime());
  lblLine2D->setString(SS.str().c_str());
  
  S = "";
  SS.str(S);
  SS << Game::Save::getLevelPoints(CrazyCrush::Game::Level::getActualLevelNumber());
  lblLine3D->setString(SS.str().c_str());
    
  btnNextLevel->setScreenPosition(window.getPositionX()+(width_all-ScreenButtonSimple::defaultScreenWidth(0))/2,window.getPositionY()+btnWin_Y);
  if(Game::Level::hasNextLevel()){
    btnNextLevel->setButtonColor(ScreenButtonSimple::green)
                 .setButtonColorHover(ScreenButtonSimple::green_light);
    btnMainMenu->setButtonColor(ScreenButtonSimple::gray)
                .setButtonColorHover(ScreenButtonSimple::gray_light);
  }else{
    btnNextLevel->setButtonColor(ScreenButtonSimple::gray_light)
                 .setButtonColorHover(ScreenButtonSimple::gray_light);
    btnMainMenu->setButtonColor(ScreenButtonSimple::green)
                .setButtonColorHover(ScreenButtonSimple::green_light);
  }
  btnMainMenu->setScreenPosition(window.getPositionX()+(width_all-ScreenButtonSimple::defaultScreenWidth(0))/2,window.getPositionY()+btnMainMenu_Y_Win);
  
  if(points > Game::Save::getLevelPoints(CrazyCrush::Game::Level::getActualLevelNumber())){
    window.setVisibility(newScore,true);
    newScore->setScreenPosition(lblPoints->getScreenPositionX() + lblPoints->getScreenWidth()/2 -20,window.getPositionY()+lblPoints_Y-25);
    Game::Save::setLevelPoint(CrazyCrush::Game::Level::getActualLevelNumber(),points);
  }else{
    window.setVisibility(newScore,false);
  }
  
  window.setVisibility(lblYourScore,true);
  window.setVisibility(lblLine1E,true);
  window.setVisibility(lblLine1D,true);
  window.setVisibility(lblLine2E,true);
  window.setVisibility(lblLine2D,true);
  window.setVisibility(lblLine3E,true);
  window.setVisibility(lblLine3D,true);
  window.setVisibility(lblLine4E,false);
  window.setVisibility(lblLine4D,false);
  window.setVisibility(lblPoints,true);
  window.setVisibility(btnTimeAttack,false);
  window.setVisibility(btnMainMenu,true);
  window.setVisibility(btnRetryLevel,false);
  window.setVisibility(btnNextLevel,true);
  window.show();
}

void showLevelFail(){
  window.setSize(width_all,height_levelFail);
  window.setPosition((Screen::screenWidth-width_all)/2,(Screen::screenHeight-height_levelFail)/2);
  
  lblPoints->setString("You Failed!").setColor(255,255,0,0);
  
  btnRetryLevel->setScreenPosition(window.getPositionX()+(width_all-ScreenButtonSimple::defaultScreenWidth(0))/2,window.getPositionY()+btnFail_Y);
  btnMainMenu->setScreenPosition(window.getPositionX()+(width_all-ScreenButtonSimple::defaultScreenWidth(0))/2,window.getPositionY()+btnMainMenu_Y_Fail);
  
  window.setVisibility(lblYourScore,false);
  window.setVisibility(lblLine1E,false);
  window.setVisibility(lblLine1D,false);
  window.setVisibility(lblLine2E,false);
  window.setVisibility(lblLine2D,false);
  window.setVisibility(lblLine3E,false);
  window.setVisibility(lblLine3D,false);
  window.setVisibility(lblLine4E,false);
  window.setVisibility(lblLine4D,false);
  window.setVisibility(lblPoints,true);
  window.setVisibility(btnTimeAttack,false);
  window.setVisibility(btnMainMenu,true);
  window.setVisibility(btnRetryLevel,true);
  window.setVisibility(btnNextLevel,false);
  window.setVisibility(newScore,false);
  window.show();
}

void showTimeAtackEnd(){
  window.setSize(width_all,height_timeAttack);
  window.setPosition((Screen::screenWidth-width_all)/2,(Screen::screenHeight-height_timeAttack)/2);
  
  Game::Save::setTimeAttackRecord(Score::getScore());
  
  std::stringstream SS;
  std::string S;
  SS << Score::getScore();
  lblPoints->setString(SS.str().c_str()).setColor(255,0,71,105);
  
  lblLine1E->setString("1:");
  lblLine2E->setString("2:");
  lblLine3E->setString("3:");
  
  S="";
  SS.str(S);
  SS << Game::Save::getTimeAttackAtPosition(1);
  lblLine1D->setString(SS.str().c_str());
  S="";
  SS.str(S);
  SS << Game::Save::getTimeAttackAtPosition(2);
  lblLine2D->setString(SS.str().c_str());
  S="";
  SS.str(S);
  SS << Game::Save::getTimeAttackAtPosition(3);
  lblLine3D->setString(SS.str().c_str());
  
  bool finded = false;
  for(unsigned i=1;i<=Game::Save::maxRankTimeAttack;i++){
    if(Game::Save::getTimeAttackAtPosition(i) == Score::getScore()){
      if(i<=3){
        lblLine4E->setString("4:");
        S="";
        SS.str(S);
        SS << Game::Save::getTimeAttackAtPosition(4);
        lblLine4D->setString(SS.str().c_str());
      }else{
        S="";
        SS.str(S);
        SS << i << ":";
        lblLine4E->setString(SS.str().c_str());
        S="";
        SS.str(S);
        SS << Score::getScore();
        lblLine4D->setString(SS.str().c_str());
      }
      finded = true;
      break;
    }
  }
  
  if(!finded){
    lblLine4E->setString("?:");
    S="";
    SS.str(S);
    SS << Score::getScore();
    lblLine4D->setString(SS.str().c_str());
  }
  
  btnTimeAttack->setScreenPosition(window.getPositionX()+(width_all-ScreenButtonSimple::defaultScreenWidth(0))/2,window.getPositionY()+btnTimeAttack_Y);
  btnMainMenu->setScreenPosition(window.getPositionX()+(width_all-ScreenButtonSimple::defaultScreenWidth(0))/2,window.getPositionY()+btnMainMenu_Y_timed);
  
  if(Score::getScore() == Game::Save::getTimeAttackRecord()){
    window.setVisibility(newScore,true);
    newScore->setScreenPosition(lblPoints->getScreenPositionX() + lblPoints->getScreenWidth()/2 -25,window.getPositionY()+lblPoints_Y-25);
  }else{
    window.setVisibility(newScore,false);
  }
  
  window.setVisibility(lblYourScore,true);
  window.setVisibility(lblLine1E,true);
  window.setVisibility(lblLine1D,true);
  window.setVisibility(lblLine2E,true);
  window.setVisibility(lblLine2D,true);
  window.setVisibility(lblLine3E,true);
  window.setVisibility(lblLine3D,true);
  window.setVisibility(lblLine4E,true);
  window.setVisibility(lblLine4D,true);
  window.setVisibility(lblPoints,true);
  window.setVisibility(btnTimeAttack,true);
  window.setVisibility(btnMainMenu,true);
  window.setVisibility(btnRetryLevel,false);
  window.setVisibility(btnNextLevel,false);
  window.show();
}

void close(){
  window.close();
}

}}}