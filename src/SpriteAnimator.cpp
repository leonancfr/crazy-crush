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
#include "SpriteAnimator.hpp"

SpriteAnimator::SpriteAnimator(){
  resourceWidthMultiplier = 0.0;
  resourceHeightMultiplier = 0.0;
  resourcePositionXMultiplier = 0.0;
  resourcePositionYMultiplier = 0.0;
  resourceLoopRatio = 0;
  resourceLoopPlus = 0;
}

SpriteAnimator::~SpriteAnimator(){}

void SpriteAnimator::setResourceSize(float width,float height){
  resourceWidthMultiplier = width;
  resourceHeightMultiplier = height;
}

void SpriteAnimator::setResourcePosition(float posX,float posY){
  resourcePositionXMultiplier = posX;
  resourcePositionYMultiplier = posY;
}

void SpriteAnimator::setResourceLoop(unsigned loop,int plus){
  resourceLoopRatio = loop;
  resourceLoopPlus = plus;
}

irr::core::rect<irr::s32> SpriteAnimator::getResourceRect(irr::u32 time,int upX,int upY,int lowX,int lowY){
  if(resourceLoopRatio == 0){
    if(resourceWidthMultiplier != 0.0)
      lowX += resourceWidthMultiplier*time;
    if(resourceHeightMultiplier != 0.0)
      lowY += resourceHeightMultiplier*time;
    if(resourcePositionXMultiplier != 0.0){
      upX += resourcePositionXMultiplier*time;
      lowX += resourcePositionXMultiplier*time;
    }
    if(resourcePositionYMultiplier != 0.0){
      upY += resourcePositionYMultiplier*time;
      lowY += resourcePositionYMultiplier*time;
    }
  }else{
    if(resourceWidthMultiplier != 0.0)
      lowX += resourceWidthMultiplier*time;
    if(resourceHeightMultiplier != 0.0)
      lowY += resourceHeightMultiplier*time;
    if(resourcePositionXMultiplier != 0.0){
      upX += resourceLoopPlus*(((irr::s32)(time*resourcePositionXMultiplier))%resourceLoopRatio);
      lowX += resourceLoopPlus*(((irr::s32)(time*resourcePositionXMultiplier))%resourceLoopRatio);
    }
    if(resourcePositionYMultiplier != 0.0){
      upY += resourceLoopPlus*(((irr::s32)(time*resourcePositionYMultiplier))%resourceLoopRatio);
      lowY += resourceLoopPlus*(((irr::s32)(time*resourcePositionYMultiplier))%resourceLoopRatio);
    }
  }
  return irr::core::rect<irr::s32>(upX,upY,lowX,lowY);
}