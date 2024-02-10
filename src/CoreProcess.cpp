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
#include "CoreProcess.hpp"
#include "Screen.hpp"
#include "GameDefines.hpp"
#include "MorphLinear.hpp"
#include "Timer.hpp"
#include "AudioManager.hpp"
#include "TextureCache.hpp"
#include "AnimationCount.hpp"
#include "CallbackAfterFall.hpp"
#include "Matrix.hpp"
#include "Random.hpp"
#include "Score.hpp"
#include "MainDraw.hpp"
#include "GamePointsMatrix.hpp"
#include "GameControl.hpp"

namespace CrazyCrush {
namespace core {

Protected<bool> triggerCheckMatrix(false);
Matrix<bool> willDestroy(Screen::num_rows,Screen::num_columns,false);
Protected<bool> isRunning(false);
Protected<unsigned> lastFullCheck(0);

//! Reinicia a dica
void resetHint(){
  lastFullCheck.set(getLevelTime());
  Screen::hintIcon.setDisplay(false).resetSpriteAnimation();
}

bool simpleCheck(unsigned i,unsigned j){
  unsigned I,J;
  bool noLeft = false;
  bool noRight = false;
  unsigned finded = 1;
  for(unsigned x=1;x<=2;x++){
    J = j+x;
    if((!noRight)&&(J < Screen::num_columns)){
      if(!Screen::matrix.at(i,J)->getEnabled()){
        noRight = true;
      }else if(*Screen::matrix.at(i,J) == *Screen::matrix.at(i,j)){
        finded++;
      }else{
        noRight = true;
      }
    }else{
      noRight = true;
    }
    J = j-x;
    if((!noLeft)&&(J < Screen::num_columns)){
      if(!Screen::matrix.at(i,J)->getEnabled()){
        noLeft = true;
      }else if(*Screen::matrix.at(i,J) == *Screen::matrix.at(i,j)){
        finded++;
      }else{
        noLeft = true;
      }
    }else{
      noLeft = true;
    }
  }
  if(finded >= 3)
    return true;
  noLeft = false;
  noRight = false;
  finded = 1;
  for(unsigned x=1;x<=2;x++){
    I = i+x;
    if((!noRight)&&(I < Screen::num_rows)){
      if(!Screen::matrix.at(I,j)->getEnabled()){
        noRight = true;
      }else if(*Screen::matrix.at(I,j) == *Screen::matrix.at(i,j)){
        finded++;
      }else{
        noRight = true;
      }
    }else{
      noRight = true;
    }
    I = i-x;
    if((!noLeft)&&(I < Screen::num_rows)){
      if(!Screen::matrix.at(I,j)->getEnabled()){
        noLeft = true;
      }else if(*Screen::matrix.at(I,j) == *Screen::matrix.at(i,j)){
        finded++;
      }else{
        noLeft = true;
      }
    }else{
      noLeft = true;
    }
  }
  if(finded >= 3)
    return true;
  return false;
}

bool checkFullMatrix(){
  CrazyCrush::core::triggerCheckMatrix.set(false);
  unsigned cVertical = 0;
  unsigned cHorizontal = 0;
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      if((!Screen::matrix.at(i,j)->getEnabled())||
         (!Screen::matrix.at(i,j)->getDisplay()))
        continue;
      cVertical = 1;
      cHorizontal = 1;
      for(unsigned i2 = i+1;(i2<=i+3)&&(i2<Screen::num_rows);i2++){
        if((!Screen::matrix.at(i2,j)->getEnabled())||
           (!Screen::matrix.at(i2,j)->getDisplay()))
          break;
        if(*Screen::matrix.at(i,j) != *Screen::matrix.at(i2,j))
          break;
        cHorizontal++;
      }
      for(unsigned j2 = j+1;(j2<=j+3)&&(j2<Screen::num_columns);j2++){
        if((!Screen::matrix.at(i,j2)->getEnabled())||
           (!Screen::matrix.at(i,j2)->getDisplay()))
          break;
        if(*Screen::matrix.at(i,j) != *Screen::matrix.at(i,j2))
          break;
        cVertical++;
      }
      if((cHorizontal<3)&&(cVertical<3))
        continue;
      willDestroy.at(i,j) = true;
      Screen::unselectBlock(i,j);
      if(cHorizontal>=3){
        for(unsigned i2 = i+1;i2<Screen::num_rows;i2++){
          if((!Screen::matrix.at(i2,j)->getEnabled())||
             (!Screen::matrix.at(i2,j)->getDisplay()))
            break;
          if(*Screen::matrix.at(i,j) != *Screen::matrix.at(i2,j))
            break;
          willDestroy.at(i2,j) = true;
          Screen::unselectBlock(i2,j);
        }
      }
      if(cVertical>=3){
        for(unsigned j2 = j+1;(j2<=j+3)&&(j2<Screen::num_columns);j2++){
          if((!Screen::matrix.at(i,j2)->getEnabled())||
             (!Screen::matrix.at(i,j2)->getDisplay()))
            break;
          if(*Screen::matrix.at(i,j) != *Screen::matrix.at(i,j2))
            break;
          willDestroy.at(i,j2) = true;
          Screen::unselectBlock(i,j2);
        }
      }
    }
  }
  unsigned sum = 0;
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      if(willDestroy.at(i,j) == true){
        sum++;
        willDestroy.at(i,j) = false;
        Screen::matrix.at(i,j)->setDisplay(false);
        Game::Points::decreasePoint(i,j);
      }
    }
  }
  resetHint();
  if(sum != 0){
    AudioManager::play("sfx_point");
    Score::increase(sum*Score::points_per_broke);
    if(!CrazyCrush::Game::gameIsTimeAttack){
      CrazyCrush::Game::Points::checkMatrix();
      if(CrazyCrush::Game::Points::isComplete()){
        CrazyCrush::Game::Control::levelWin();
      }
    }
    return true;
  }
  return false;
}

bool processFall(){
  bool someoneFalled = false;
  bool isTop;
  int topPos;
  irr::core::position2d<irr::s32> pos;
  Gem* sw;
  irr::u32 eTime = getGameTime()==0?1:getGameTime();
  for(unsigned j=0;j<Screen::num_columns;j++){
    topPos = Game::stageTopPositionStart[j]*TextureCache::gemHeight;
    pos = Screen::convertMatrix2Screen(0,j);
    for(unsigned i=0;i<Screen::num_rows;i++){
      if(Screen::matrix.at(i,j)->getDisplay())
        continue;
      if(Screen::matrix.at(i,j)->getFixed()){
        Screen::matrix.at(i,j)->setDisplay(true);
        continue;
      }
      isTop = false;
      for(unsigned i2=i+1;i2<Screen::num_rows;i2++){
        if((!Screen::matrix.at(i2,j)->getDisplay())||
           (Screen::matrix.at(i2,j)->getFixed()))
          continue;
        Screen::unselectBlock(i2,j);
        someoneFalled = true;
        isTop = true;
        sw = Screen::matrix.at(i,j);
        Screen::matrix.at(i,j) = Screen::matrix.at(i2,j);
        Screen::matrix.at(i2,j) = sw;
        Screen::matrix.at(i,j)->setEnabled(false);
        MorphLinear *t = new MorphLinear();
        t->setFinalPosition(Screen::convertMatrix2Screen(i,j));
        t->setVelocity(0.0,Screen::fall_velocity);
        Screen::matrix.at(i,j)->appendMorph(t).startAnimator(eTime).appendCallback(new CallbackAfterFall(i,j));
        Screen::AnimationCount::increase();
        break;
      }
      if(!isTop){
        someoneFalled = true;
        topPos -= TextureCache::gemHeight;
        Screen::matrix.at(i,j)->setScreenPosition(pos.X,topPos);
        MorphLinear *t = new MorphLinear();
        t->setFinalPosition(Screen::convertMatrix2Screen(i,j));
        t->setVelocity(0.0,Screen::fall_velocity);
        Screen::matrix.at(i,j)->setEnabled(false);
        Screen::matrix.at(i,j)->randGem()
          .appendMorph(t).startAnimator(eTime).setDisplay(true).appendCallback(new CallbackAfterFall(i,j));
        Screen::AnimationCount::increase();
      }
    }
  }
  return someoneFalled;
}

void resumeGame(){
  if(isRunning.get())
    return;
  isRunning.set(true);
  AudioManager::resume();
  Game::Control::resumeGame(false);
}

void pauseGame(){
  if(!isRunning.get())
    return;
  isRunning.set(false);
  AudioManager::suspend();
  Game::Control::pauseGame();
  draw();
}

//! Posiciona a dica na tela
/**
\param i: Coordenada i da matriz
\param j: Coordenada j da matriz
\param v: Se o movimento é vertical
*/
bool setHintPosition(unsigned i,unsigned j,bool v){
  if(v){
    Screen::hintIcon.setTexture(TextureCache::seta_v).setScreenPosition(Screen::stageBackgroundLeft+j*TextureCache::gemWidth,(Screen::stageBackgroundTop+Screen::num_rows*TextureCache::gemHeight)-((i+1)*TextureCache::gemHeight)+(TextureCache::gemHeight/2));
  }else{
    Screen::hintIcon.setTexture(TextureCache::seta_h).setScreenPosition(Screen::stageBackgroundLeft+j*TextureCache::gemWidth+(TextureCache::gemWidth/2),(Screen::stageBackgroundTop+Screen::num_rows*TextureCache::gemHeight)-((i+1)*TextureCache::gemHeight));
  }
  return true;
}

bool checkIfHasMoveLeft(){
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      if(Screen::matrix.at(i,j)->getFixed())
        continue;
      if(j+1 < Screen::num_columns){
        if(*Screen::matrix.at(i,j+1) == *Screen::matrix.at(i,j)){
          if(j+2 < Screen::num_columns){
            if((i+1 < Screen::num_rows)&&(*Screen::matrix.at(i+1,j+2) == *Screen::matrix.at(i,j)))
              return setHintPosition(i+1,j+2,true);
            if((i>0)&&(*Screen::matrix.at(i-1,j+2) == *Screen::matrix.at(i,j)))
              return setHintPosition(i,j+2,true);
            if((j+3 < Screen::num_columns)&&(*Screen::matrix.at(i,j+3) == *Screen::matrix.at(i,j)))
              return setHintPosition(i,j+2,false);
          }
          if(j>0){
            if(((i+1) < Screen::num_rows)&&(*Screen::matrix.at(i+1,j-1) == *Screen::matrix.at(i,j)))
              return setHintPosition(i+1,j-1,true);
            if((i>0)&&(*Screen::matrix.at(i-1,j-1) == *Screen::matrix.at(i,j)))
              return setHintPosition(i,j-1,true);
            if((j>1)&&(*Screen::matrix.at(i,j-2) == *Screen::matrix.at(i,j)))
              return setHintPosition(i,j-2,false);
          }
        }
        if((j+2 < Screen::num_columns)&&(*Screen::matrix.at(i,j+2) == *Screen::matrix.at(i,j))){
          if((i+1 < Screen::num_rows)&&(*Screen::matrix.at(i+1,j+1) == *Screen::matrix.at(i,j)))
            return setHintPosition(i+1,j+1,true);
          if((i>0)&&(*Screen::matrix.at(i-1,j+1) == *Screen::matrix.at(i,j)))
            return setHintPosition(i,j+1,true);
        }
      }
      if(i+1 < Screen::num_rows){
        if(*Screen::matrix.at(i+1,j) == *Screen::matrix.at(i,j)){
          if(i+2 < Screen::num_rows){
            if((j+1 < Screen::num_rows)&&(*Screen::matrix.at(i+2,j+1) == *Screen::matrix.at(i,j)))
              return setHintPosition(i+2,j,false);
            if((j>0)&&(*Screen::matrix.at(i+2,j-1) == *Screen::matrix.at(i,j)))
              return setHintPosition(i+2,j-1,false);
            if((i+3 < Screen::num_rows)&&(*Screen::matrix.at(i+3,j) == *Screen::matrix.at(i,j)))
             return setHintPosition(i+3,j,true);
          }
          if(i>0){
            if((j+1 < Screen::num_rows)&&(*Screen::matrix.at(i-1,j+1) == *Screen::matrix.at(i,j)))
              return setHintPosition(i-1,j,false);
            if((j>0)&&(*Screen::matrix.at(i-1,j-1) == *Screen::matrix.at(i,j)))
              return setHintPosition(i-1,j-1,false);
            if((i>1)&&(*Screen::matrix.at(i-2,j) == *Screen::matrix.at(i,j)))
             return setHintPosition(i-1,j,true);
          }
        }
        if((i+2 < Screen::num_rows)&&(*Screen::matrix.at(i+2,j) == *Screen::matrix.at(i,j))){
          if((j+1 < Screen::num_columns)&&(*Screen::matrix.at(i+1,j+1) == *Screen::matrix.at(i,j)))
            return setHintPosition(i+1,j,false);;
          if((j>0)&&(*Screen::matrix.at(i+1,j-1) == *Screen::matrix.at(i,j)))
            return setHintPosition(i+1,j-1,false);;
        }
      }
    }
  }
  resetHint();
  return false;
}

void fillMatrix(){
  pauseLevelTimer();
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      if(!Screen::matrix.at(i,j)->getFixed())
        Screen::matrix.at(i,j)->setDisplay(false);
    }
  }
  processFall();
}

}} // Close CrazyCrush::core