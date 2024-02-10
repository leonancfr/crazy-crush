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
#include "GameLevel.hpp"
#include "ScreenWindow.hpp"
#include "GameLevelFile.hpp"
#include "GameControl.hpp"
#include "GameDefines.hpp"
#include "ScreenButtonExtended.hpp"
#include "ScreenButtonDefault.hpp"
#include "ScreenButtonSimple.hpp"
#include "ScreenButtonSprite.hpp"
#include "GameSave.hpp"
#include "Logger.hpp"
#include "TextureCache.hpp"
#include "AudioManager.hpp"
#include <sstream>

namespace CrazyCrush {
namespace Game {
namespace Level {

const unsigned totalLevel = 6;
const unsigned totalPages = (totalLevel/4)+(totalLevel%4!=0?1:0);

unsigned actualPage = 0;
unsigned levelNum = 0;
ScreenWindow screenLevelSelect;
void printButtonsPage();

//! Callback para voltar ao menu principal
class CallbackGameMainMenuButtonClick : public Callback {
  public:
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::Level::closeLevelMenu();
      CrazyCrush::Game::Control::gameGoToMainScreen();
    }
};

//! Callback para iniciar um nível
class CallbackGamePlayLevelButtonClick : public Callback {
  private:
    unsigned lvl;
  public:
    //! Instancia o objeto e define qual nível irá jogar
    CallbackGamePlayLevelButtonClick(unsigned l){
      lvl = l;
    }
    void aProcess(){
      CrazyCrush::AudioManager::play("sfx_wing",false,"sfx_wing.ogg");
      CrazyCrush::Game::Level::playLevel(lvl);
    }
};


//! Callback para mudar de página
class CallbackGoToPageButtonClick : public Callback {
  private:
    unsigned page;
  public:
    //! Instancia o objeto e define qual página irá exibir
    CallbackGoToPageButtonClick(unsigned p){
      page = p;
    }
    void aProcess(){
      if(page >= totalPages)
        return;
      CrazyCrush::AudioManager::play("sfx_wing");
      actualPage = page;
      printButtonsPage();
    }
};

ScreenButtonExtended *btnLvl1,*btnLvl2,*btnLvl3,*btnLvl4;
ScreenButtonDefault *btnBack;
ScreenButtonSimple *btnLeft,*btnRight;
ScreenText *lblPage;

void printButtonsPage(){
  ScreenButtonExtended *btn;
  std::string S;
  std::stringstream SS;
  unsigned offset = actualPage*4;
  for(unsigned i=1;i<=4;i++){
    switch(i){
      default:
      case 1:
        btn = btnLvl1;
        break;
      case 2:
        btn = btnLvl2;
        break;
      case 3:
        btn = btnLvl3;
        break;
      case 4:
        btn = btnLvl4;
        break;
    };
    if(offset+i > totalLevel){
      screenLevelSelect.setVisibility(btn,false);
      continue;
    }else{
      screenLevelSelect.setVisibility(btn,true);
    }
    S="";
    SS.str(S);
    SS << "Level " << offset+i;
    btn->setLabel(SS.str());
    btn->setOnClick(new CallbackGamePlayLevelButtonClick(offset+i));
    S="";
    SS.str(S);
    if(Game::Save::getLevelPoints(offset+i) == 0){
      SS << "No record";
    }else{
      SS << "Record: "<<Game::Save::getLevelPoints(offset+i);
    }
    btn->setSubLabel(SS.str());
  }
  
  if(actualPage == 0){
    screenLevelSelect.setVisibility(btnLeft,false);
  }else{
    screenLevelSelect.setVisibility(btnLeft,true);
    btnLeft->setOnClick(new CallbackGoToPageButtonClick(actualPage-1));
  }
  if(actualPage == totalPages-1){
    screenLevelSelect.setVisibility(btnRight,false);
  }else{
    screenLevelSelect.setVisibility(btnRight,true);
    btnRight->setOnClick(new CallbackGoToPageButtonClick(actualPage+1));
  }
  
  S="";
  SS.str(S);
  SS << "Page " << actualPage+1 << " of " << totalPages;
  lblPage->setString(SS.str().c_str());
}

void initialize(){
  lblPage = new ScreenText(TextureCache::font1);
  btnBack = new ScreenButtonDefault;
  btnLvl1 = new ScreenButtonExtended;
  btnLvl2 = new ScreenButtonExtended;
  btnLvl3 = new ScreenButtonExtended;
  btnLvl4 = new ScreenButtonExtended;
  btnLeft = new ScreenButtonSimple();
  btnRight = new ScreenButtonSimple();
  
  for(unsigned i=1;i<=totalLevel;i++){
    if(Game::Save::getLevelPoints(i) == 0){
      actualPage = i/4;
      break;
    }
  }
  
  lblPage->setDisplay(false).setString("").setScreenAlign(ScreenText::center).setScreenPosition(298,240).setColor(255,255,255,255);
  btnLeft->setIconResourceSize(16,16).setIconSize(16,16)
          .setIconResourceSizeHover(16,16).setIconSizeHover(16,16)
          .setIconResourceOffset(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_left_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_left_white))
          .setIconResourceOffsetHover(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_left_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_left_white))
          .setIconOffset(4,4).setIconOffsetHover(4,4)
          .setButtonColor(ScreenButtonSimple::blue).setButtonColorHover(ScreenButtonSimple::blue_light)
          .setButtonSize(24,24).setButtonSizeHover(24,24).setScreenPosition(170,240);
  
  btnRight->setIconResourceSize(16,16).setIconSize(16,16)
           .setIconResourceSizeHover(16,16).setIconSizeHover(16,16)
           .setIconResourceOffset(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_right_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_left_white))
           .setIconResourceOffsetHover(ScreenButtonSprite::getOffsetX(ScreenButtonSprite::button_right_white),ScreenButtonSprite::getOffsetY(ScreenButtonSprite::button_left_white))
           .setIconOffset(4,4).setIconOffsetHover(4,4)
           .setButtonColor(ScreenButtonSimple::blue).setButtonColorHover(ScreenButtonSimple::blue_light)
           .setButtonSize(24,24).setButtonSizeHover(24,24).setScreenPosition(402,240);
  
  btnBack->setLabel("Back");
  btnBack->setScreenPosition(200,263);
  btnBack->setOnClick(new CallbackGameMainMenuButtonClick());

  btnLvl1->setScreenPosition(67,80);
  btnLvl1->setScreenSize(0,70);
  btnLvl1->setSubLabelOffset(btnLvl1->getScreenWidth()/2,34 + 15);
  btnLvl1->getSubLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);

  btnLvl2->setScreenPosition(331,80);
  btnLvl2->setScreenSize(0,70);
  btnLvl2->setSubLabelOffset(btnLvl2->getScreenWidth()/2,34 + 15);
  btnLvl2->getSubLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);

  btnLvl3->setScreenPosition(67,160);
  btnLvl3->setScreenSize(0,70);
  btnLvl3->setSubLabelOffset(btnLvl3->getScreenWidth()/2,34 + 15);
  btnLvl3->getSubLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);

  btnLvl4->setScreenPosition(331,160);
  btnLvl4->setScreenSize(0,70);
  btnLvl4->setSubLabelOffset(btnLvl4->getScreenWidth()/2,34 + 15);
  btnLvl4->getSubLabelObject().setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);
  
  screenLevelSelect.inject(btnBack,1);
  screenLevelSelect.inject(btnLvl1,1);
  screenLevelSelect.inject(btnLvl2,1);
  screenLevelSelect.inject(btnLvl3,1);
  screenLevelSelect.inject(btnLvl4,1);
  screenLevelSelect.inject(lblPage,1);
  screenLevelSelect.inject(btnLeft,1);
  screenLevelSelect.inject(btnRight,1);
  //screenLevelSelect.inject(btnLvl5,1);
  //screenLevelSelect.inject(btnLvl6,1);
  screenLevelSelect.setSize(0,290);
  screenLevelSelect.setPosition(22,95);
  printButtonsPage();
}

unsigned getActualLevelNumber(){
  return levelNum;
}

bool playLevel(unsigned l){
  if(Game::Control::gameIsRunning())
    return false;
  Game::gameIsTimeAttack = false;
  levelNum = l;
  std::stringstream SS;
  SS << "level" << levelNum << ".bin";
  if(!CrazyCrush::Game::LevelFile::openLevel(SS.str())){
    std::stringstream SSS;
    SSS << "Unable to init level: " << SS.str();
    LOG_ERROR(SSS.str().c_str());
    return false;
  }
  CrazyCrush::Game::Control::gamePlay();
  CrazyCrush::Game::Level::closeLevelMenu();
  return true;
}

void showLevelMenu(){
  screenLevelSelect.show();
  printButtonsPage();
}

void closeLevelMenu(){
  screenLevelSelect.close();
}

bool hasNextLevel(){
  if(levelNum>=totalLevel)
    return false;
  return true;
}

void gotoNextLevel(){
  if(hasNextLevel())
    playLevel(levelNum+1);
}

}}}