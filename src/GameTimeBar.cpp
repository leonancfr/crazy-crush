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
#include "GameTimeBar.hpp"

#include "ScreenObject.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "GameDefines.hpp"
#include "Screen.hpp"
#include "AnimatorObjectList.hpp"
#include "Timer.hpp"
#include "GameControl.hpp"
#include "CoreProcess.hpp"

//! Classe gambiarra para adicionar à Thread de processamento no Tempo
class UpdateTimeBar : public AnimatorObject {
  public:
    unsigned char getType(){
      return 255;
    }
    void processTime(irr::u32 t){
      CrazyCrush::Game::TimeBar::updateLength();
    }
    UpdateTimeBar(){};
    ~UpdateTimeBar(){};
    void aSetDisplay(bool a){};
    void aSetScreenSize(unsigned a,unsigned b){};
    void aSetScreenPosition(int a,int b){};
    void aSetImageColor(irr::video::SColor* a){};
    irr::video::SColor* getColor(){return NULL;};
    unsigned    getScreenWidth(){return 0;}
    unsigned    getScreenHeight(){return 0;};
    int         getScreenPositionX(){return 0;};
    int         getScreenPositionY(){return 0;};
    bool        getDisplay(){return true;};
};

namespace CrazyCrush {
namespace Game {
namespace TimeBar {

ScreenObject bar(TextureCache::sprites);
ScreenObject barBackground(TextureCache::sprites);
UpdateTimeBar updateTimeBar;

const unsigned timeToShowHint = 7000;
const unsigned barWidth = 452;
const unsigned barHeight = 10;
const unsigned barBackgroundWidth = 456;
const unsigned barBackgroundHeight = 14;
const unsigned barResourceX = 4;
const unsigned barResourceY = 384;
const unsigned barBackgroundResourceX = 2;
const unsigned barBackgroundResourceY = 398;
const unsigned barOffsetLeft = Screen::stageBackgroundLeft-2;
const unsigned barOffsetTop = Screen::stageBackgroundTop+TextureCache::gemHeight*Screen::num_rows+2;

void initialize(){
  bar.setResourceSize(barWidth,barHeight)
     .setResourcePosition(barResourceX,barResourceY)
     .setScreenSize(barWidth,barHeight)
     .setScreenPosition(barOffsetLeft+(barBackgroundWidth-barWidth)/2,barOffsetTop+(barBackgroundHeight-barHeight)/2)
     .setDisplay(false);
  barBackground.setResourceSize(barBackgroundWidth,barBackgroundHeight)
               .setResourcePosition(barBackgroundResourceX,barBackgroundResourceY)
               .setScreenSize(barBackgroundWidth,barBackgroundHeight)
               .setScreenPosition(barOffsetLeft,barOffsetTop)
               .setDisplay(false);
  z_order.addObject(&barBackground,z_order.index_gems);
  z_order.addObject(&bar,z_order.index_gems);
  AnimatorObjectList.addObject(&updateTimeBar);
}

void show(){
  bar.setDisplay(true);
  barBackground.setDisplay(true);
}

void hide(){
  bar.setDisplay(false);
  barBackground.setDisplay(false);
}

void updateLength(){
  if(!Game::Control::gameIsRunning())
    return;
  if(bar.getDisplay()){
    if(getLevelTime() >= Game::Control::getLevelTotalTime()){
      Game::Control::levelFail();
      bar.setResourceSize(0,barHeight).setScreenSize(0,barHeight);
      return;
    }
    if((getLevelTime()>timeToShowHint+core::lastFullCheck.get())&&(!Screen::hintIcon.getDisplay())){
      Screen::hintIcon.setDisplay(true).startSpriteAnimation(getGameTime());
    }
    unsigned size = ((Game::Control::getLevelTotalTime()-getLevelTime())*barWidth)/Game::Control::getLevelTotalTime();
    bar.setResourceSize(size,barHeight).setScreenSize(size,barHeight);
  }
}


}}}