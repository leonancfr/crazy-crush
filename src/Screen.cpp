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
#include "Screen.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "CoreProcess.hpp"
#include "Timer.hpp"
#include "ScreenHoverRect.hpp"
#include "CallbackMouseClickMatrix.hpp"
#include "CallbackMouseHoverMatrix.hpp"
#include "CallbackMatrixOut.hpp"
#include "AnimatorObjectList.hpp"
#include "GameDefines.hpp"

namespace CrazyCrush {
namespace Screen {

const unsigned stageBackgroundWidth = num_columns*TextureCache::gemWidth;
const unsigned stageBackgroundHeight = num_rows*TextureCache::gemHeight;

Matrix<ScreenHover*> matrixHover(num_rows,num_columns);
ScreenHover* outHover;
ScreenObject frameSelectorPointer(NULL);
ScreenObject frameSelector(NULL);
ScreenObject stageBackground(NULL);
ScreenObject gameBackground(NULL);
ScreenObject noMoreMovesObj(NULL);
ScreenObject hintIcon(NULL);

bool initializeScreen(){
  Gem* tmpObj;
  z_order.addObject(&stageBackground,ZOrder<char>::index_stage);
  z_order.addObject(&frameSelectorPointer,ZOrder<char>::index_selectPointer);
  z_order.addObject(&frameSelector,ZOrder<char>::index_select);
  z_order.addObject(&noMoreMovesObj,ZOrder<char>::index_select);
  z_order.addObject(&gameBackground,ZOrder<char>::index_background);
  z_order.addObject(&hintIcon,ZOrder<char>::index_select);
  
  gameBackground.setTexture(TextureCache::gameBackground);
  gameBackground.setResourcePosition(0,0);
  gameBackground.setResourceSize(640,480);
  gameBackground.setScreenSize(screenWidth,screenHeight);
  gameBackground.setDisplay(true);
  
  stageBackground.setTexture(TextureCache::stageBackground);
  stageBackground.setResourcePosition(0,0);
  stageBackground.setResourceSize(452,452);
  stageBackground.setScreenSize(452,452);
  stageBackground.setScreenPosition(stageBackgroundLeft-1,stageBackgroundTop-1);
  stageBackground.setDisplay(false);
  
  frameSelectorPointer.setTexture(TextureCache::selector);
  frameSelectorPointer.setResourceSize(30,30);
  frameSelectorPointer.setResourcePosition(30,0);
  frameSelectorPointer.setScreenSize(30,30);
  frameSelectorPointer.setDisplay(false);
  
  frameSelector.setTexture(TextureCache::selector);
  frameSelector.setResourcePosition(0,0);
  frameSelector.setResourceSize(30,30);
  frameSelector.setScreenSize(30,30);
  frameSelector.setDisplay(false);
  
  noMoreMovesObj.setTexture(TextureCache::sprites);
  noMoreMovesObj.setResourcePosition(170,0);
  noMoreMovesObj.setResourceSize(295,51);
  noMoreMovesObj.setScreenSize(295,51);
  noMoreMovesObj.setScreenPosition(stageBackgroundLeft+77,stageBackgroundTop+200);
  noMoreMovesObj.setDisplay(false);
  CrazyCrush::AnimatorObjectList.addObject(&noMoreMovesObj);
  
  hintIcon.setTexture(TextureCache::seta_v).setResourcePosition(0,0).setResourceSize(84,84).setScreenSize(TextureCache::gemWidth,TextureCache::gemHeight).setDisplay(false);
  hintIcon.setSpriteAnimator(&(TextureCache::DefaultAnimator));
  CrazyCrush::AnimatorObjectList.addObject(&hintIcon);
  
  
  ScreenHover* tHover = NULL;
  for(unsigned i=0;i<num_rows;i++){
    for(unsigned j=0;j<num_columns;j++){
      tmpObj = new Gem();
      if(tmpObj == NULL)
        return false;
      z_order.addObject(tmpObj,ZOrder<char>::index_gems);
      matrix.at(i,j) = tmpObj;
      tmpObj->setScreenPosition(stageBackgroundLeft+j*TextureCache::gemWidth,(stageBackgroundTop+stageBackgroundHeight)-((i+1)*TextureCache::gemHeight));
      tHover = new ScreenHoverRect(
        stageBackgroundLeft+j*TextureCache::gemWidth,
        (stageBackgroundTop+stageBackgroundHeight)-((i+1)*TextureCache::gemHeight),
        TextureCache::gemWidth,
        TextureCache::gemHeight
      );
      tHover->setClickEvent(new CallbackMouseClickMatrix(i,j)).setHoverEvent(new CallbackMouseHoverMatrix(i,j)).setEnabled(false);
      matrixHover.at(i,j) = tHover;
    }
  }
  outHover = new ScreenHoverRect(0,0,640,480);
  outHover->setClickEvent(new CallbackMatrixOutClick()).setHoverEvent(new CallbackMatrixOutHover()).setEnabled(false);
  return true;
}

void updateScreenPosition(ScreenObject& obj,unsigned i,unsigned j){
  obj.setScreenPosition(stageBackgroundLeft+j*TextureCache::gemWidth,(stageBackgroundTop+stageBackgroundHeight)-((i+1)*TextureCache::gemHeight));
}



}} // Close CrazyCrush::Screen