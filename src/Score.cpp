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
#include "Score.hpp"
#include "Irrlicht/irrTypes.h"
#include "ScreenText.hpp"
#include "Timer.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "Protected.hpp"
#include "GameDefines.hpp"
#include "Screen.hpp"
#include "AnimatorObjectList.hpp"
#include <pthread.h>
#include <sstream>

namespace CrazyCrush {
namespace Score {

const unsigned delay_time_for_combo = 1500;             // millisecond
const unsigned base_interval_between_decrease = 1000;   // millisecond
const unsigned interval_between_decrease = 166;         // millisecond

Protected<unsigned char> multiplier(0);
Protected<unsigned char> decreasingRatio(0);
Protected<unsigned> score(0);
Protected<irr::u32> lastTime(0);
Protected<unsigned> lastRandom(0);
Protected<bool> isDecreasing(false);
ScreenText scoreDisplay(NULL);
ScreenObject scoreBackground(NULL);
ScreenObject scoreBar(NULL);
ScreenObject scoreBarSpliter(NULL);
ScreenObject scoreObjMarker(NULL);
std::stringstream tSS;
std::string tS;

const unsigned barWidth = 150;
const unsigned barHeight = 3;
const unsigned barStartX = 7;
const unsigned barStartYGreen = 37;
const unsigned barStartYOrange = 42;
const unsigned barStartYYellow = 47;
const unsigned barStartYCyan = 52;
const unsigned barStartYMagenta = 57;
const unsigned barStartYBlue = 62;

void initialize(){
  score.set(0);
  multiplier.set(0);
  isDecreasing.set(false);
  lastTime.set(getGameTime());
  scoreDisplay.setFont(TextureCache::font1);
  scoreDisplay.setScreenPosition(164,Screen::stageBackgroundTop+2);
  scoreDisplay.setString("0");
  scoreDisplay.setDisplay(false);
  scoreDisplay.setColor(255,255,255,255);
  scoreDisplay.setScreenAlign(ScreenText::right);
  
  scoreBackground.setTexture(TextureCache::sprites).setResourceSize(164,30).setScreenSize(164,30).setScreenPosition(5,Screen::stageBackgroundTop).setDisplay(false);
  scoreBarSpliter.setTexture(TextureCache::sprites).setResourceSize(barWidth,barHeight).setResourcePosition(barStartX,32).setScreenSize(barWidth,barHeight).setScreenPosition(12,Screen::stageBackgroundTop+25).setDisplay(false);
  scoreBar.setTexture(TextureCache::sprites).setResourceSize(barWidth,barHeight).setResourcePosition(barStartX,barStartYYellow).setScreenSize(0,barHeight).setScreenPosition(12,Screen::stageBackgroundTop+25).setDisplay(false);
  scoreObjMarker.setResourceSize(84,84).setScreenSize(14,14).setScreenPosition(10,Screen::stageBackgroundTop+5).setTexture(TextureCache::gem0).setSpriteAnimator(&TextureCache::DefaultAnimator).startSpriteAnimation(1).setDisplay(false);
  
  CrazyCrush::AnimatorObjectList.addObject(&scoreObjMarker);
  z_order.addObject(&scoreBackground,ZOrder<bool>::index_score_bg);
  z_order.addObject(&scoreBarSpliter,ZOrder<bool>::index_score_bar_divider);
  z_order.addObject(&scoreBar,ZOrder<bool>::index_score_bar);
  z_order.addObject(&scoreObjMarker,ZOrder<bool>::index_score_bar);
  z_order.addObject(&scoreDisplay,ZOrder<bool>::index_score_bar);
}

void updateMultiplierBar(){
  unsigned mul = multiplier.get();
  if(mul > 50){
    scoreBar.setResourcePosition(barStartX,barStartYBlue);
    scoreObjMarker.setDisplay(true).setTexture(TextureCache::gem6);
    mul -= 50;
  }else if(mul > 40){
    scoreBar.setResourcePosition(barStartX,barStartYMagenta);
    scoreObjMarker.setDisplay(true).setTexture(TextureCache::gem3);
    mul -= 40;
  }else if(mul > 30){
    scoreBar.setResourcePosition(barStartX,barStartYCyan);
    scoreObjMarker.setDisplay(true).setTexture(TextureCache::gem4);
    mul -= 30;
  }else if(mul > 20){
    scoreBar.setResourcePosition(barStartX,barStartYGreen);
    scoreObjMarker.setDisplay(true).setTexture(TextureCache::gem2);
    mul -= 20;
  }else if(mul > 10){
    scoreBar.setResourcePosition(barStartX,barStartYOrange);
    scoreObjMarker.setDisplay(true).setTexture(TextureCache::gem5);
    mul -= 10;
  }else{
    scoreBar.setResourcePosition(barStartX,barStartYYellow);
    scoreObjMarker.setDisplay(false);
  }
  if(mul > 10)
    mul = 10;
  scoreBar.setScreenSize(barWidth*mul/10,barHeight).setResourceSize(barWidth*mul/10,barHeight);
}

void trigger(){
  if(((!isDecreasing.get())&&(getGameTime() <= lastTime.get()+delay_time_for_combo))||
     ((isDecreasing.get())&&(getGameTime() <= lastTime.get()+delay_time_for_combo-base_interval_between_decrease-(interval_between_decrease*decreasingRatio.get()))))
    return;
  lastTime.set(getGameTime());
  if((isDecreasing.get())&&((interval_between_decrease*decreasingRatio.get()) >= delay_time_for_combo+base_interval_between_decrease)){
    isDecreasing.set(false);
    multiplier.set(0);
  }else{
    isDecreasing.set(true);
    decreasingRatio.set(decreasingRatio.get()+1);
    unsigned ml = multiplier.get();
    multiplier.set(ml==0?0:ml-1);
  }
  updateMultiplierBar();
}

void increase(unsigned r,unsigned val){
  isDecreasing.set(false);
  decreasingRatio.set(0);
  if(lastRandom.get() != r){
    if(getGameTime() < lastTime.get()+delay_time_for_combo)
      multiplier.set(multiplier.get()>=100?100:multiplier.get()+1);
    lastRandom.set(r);
  }
  lastTime.set(getGameTime());
  score.set(score.get()+val*multiplier.get());
  tSS.str(tS);
  tSS << score.get();
  tS = tSS.str();
  scoreDisplay.setString(tS);
}

void increase(unsigned val){
  isDecreasing.set(false);
  decreasingRatio.set(0);
  if(getGameTime()<lastTime.get()+delay_time_for_combo){
    multiplier.set(multiplier.get()>=100?100:multiplier.get()+1);
    updateMultiplierBar();
  }
  lastTime.set(getGameTime());
  score.set(score.get()+val*multiplier.get());
  tSS.str(tS);
  tSS << score.get();
  tS = tSS.str();
  scoreDisplay.setString(tS);
}

void resetMultiplier(){
  multiplier.set(0);
  updateMultiplierBar();
}

void show(){
  scoreBar.setDisplay(true);
  scoreBarSpliter.setDisplay(true);
  scoreBackground.setDisplay(true);
  scoreDisplay.setDisplay(true);
  //scoreObjMarker
}

void hide(){
  scoreBar.setDisplay(false);
  scoreBarSpliter.setDisplay(false);
  scoreBackground.setDisplay(false);
  scoreDisplay.setDisplay(false);
  scoreObjMarker.setDisplay(false);
}

void resetAll(){
  multiplier.set(0);
  updateMultiplierBar();
  score.set(0);
  lastTime.set(getGameTime());
  isDecreasing.set(false);
  decreasingRatio.set(0);
  scoreDisplay.setString("0");
  tS = "0";
}

unsigned getScore(){
  return score.get();
}

}}
