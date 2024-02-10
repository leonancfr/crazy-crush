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
#include "GameDefines.hpp"

#include "Screen.hpp"
#include "TextureCache.hpp"
#include "Timer.hpp"
#include "GamePointsMatrix.hpp"
#include "GameTimeBar.hpp"
#include "GameControl.hpp"
#include "GameMainScreen.hpp"
#include "GamePauseButton.hpp"
#include "GamePostScreen.hpp"
#include "GameLevel.hpp"
#include "GameTimeAttack.hpp"
#include "GameSave.hpp"

namespace CrazyCrush {
namespace Game {

unsigned char totalGemsEnabled = 5;
Percentage::HPercent timeBonusGemProbability;
std::vector<unsigned> stageTopPositionStart;
bool gameIsTimeAttack = false;
const unsigned char maxGemExistent = 7;

void initialize(){
  stageTopPositionStart.resize(Screen::num_columns);
  for(unsigned i=0;i<Screen::num_columns;i++){
    stageTopPositionStart[i] = Screen::stageBackgroundTop;
  }
  
  timeBonusGemProbability = Percentage::formatH(0.001);
  
  Points::initialize();
  TimeBar::initialize();
  Control::initialize();
  MainScreen::initialize();
  Pause::Button::initialize();
  PostScreen::initialize();
  Level::initialize();
  TimeAttack::initialize();
  Save::initialize();
}

}

namespace Screen{

const unsigned stageBackgroundWidth = num_columns*TextureCache::gemWidth;
const unsigned stageBackgroundHeight = num_rows*TextureCache::gemHeight;
const MatrixPosition defaultPosition = {-1,-1};

Protected<MatrixPosition> lastPosition(defaultPosition);
Matrix<Gem*> matrix(num_rows,num_columns);


MatrixPosition convertScreen2Matrix(irr::u16 X,irr::u16 Y){
  MatrixPosition ret;
  if((X<stageBackgroundLeft)||(X>(stageBackgroundLeft+stageBackgroundWidth))){
    ret.i = -1;
    ret.j = -1;
  }else if((Y<stageBackgroundTop)||(Y>(stageBackgroundTop+stageBackgroundHeight))){
    ret.i = -1;
    ret.j = -1;
  }else{
    ret.i = num_rows-1-((Y-stageBackgroundTop)/TextureCache::gemHeight);
    ret.j = (X-stageBackgroundLeft)/TextureCache::gemWidth;
  }
  return ret;
}

irr::core::position2d<irr::s32> convertMatrix2Screen(unsigned i,unsigned j){
  return irr::core::position2d<irr::s32>(
    stageBackgroundLeft+j*TextureCache::gemWidth,
    (stageBackgroundTop+stageBackgroundHeight)-((i+1)*TextureCache::gemHeight)
  );
}   

MatrixPosition getLastBlock(){
  return lastPosition.get();
}

void unselectBlock(){
  frameSelector.setDisplay(false);
  MatrixPosition t = lastPosition.get();
  if((t.i != -1)&&(t.j != -1)){
    matrix.at(t.i,t.j)->resetSpriteAnimation();
    t.i = -1;
    t.j = -1;
    lastPosition.set(t);
  }
}

void unselectBlock(unsigned i,unsigned j){
  MatrixPosition t = lastPosition.get();
  if((t.i==(int)i)&&(t.j==(int)j)){
    frameSelector.setDisplay(false);
    matrix.at(i,j)->resetSpriteAnimation();
    t.i = -1;
    t.j = -1;
    lastPosition.set(t);
  }
}

void selectBlock(unsigned i,unsigned j){
  frameSelector.setDisplay(true);
  frameSelector.setScreenPosition(
    j*TextureCache::gemWidth+stageBackgroundLeft,
    (stageBackgroundTop+stageBackgroundHeight)-(i+1)*TextureCache::gemHeight
  );
  matrix.at(i,j)->startSpriteAnimation(getGameTime());
  MatrixPosition t;
  t.i = i;
  t.j = j;
  lastPosition.set(t);
}


}

}