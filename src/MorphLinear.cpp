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
#include "MorphLinear.hpp"

MorphLinear::MorphLinear(){
  duration = 1;
  ratioX = 0.0;
  ratioY = 0.0;
  finalPosX = 0;
  finalPosY = 0;
}

MorphLinear& MorphLinear::setDuration(unsigned d){
  duration = d;
  return *this;
}

MorphLinear& MorphLinear::setVelocity(float x,float y){
  ratioX = x;
  ratioY = y;
  return *this;
}

MorphLinear& MorphLinear::setFinalPosition(int X,int Y){
  finalPosX = X;
  finalPosY = Y;
  return *this;
}

MorphLinear& MorphLinear::setFinalPosition(irr::core::position2d<irr::s32> pos){
  finalPosX = pos.X;
  finalPosY = pos.Y;
  return *this;
}

void MorphLinear::internalTrigger(irr::u32 time){
  if((ratioX == 0.0)&&(ratioY == 0.0)){
    ratioX = ((float)(finalPosX-obj->getScreenPositionX()))/duration;
    ratioY = ((float)(finalPosY-obj->getScreenPositionY()))/duration;
  }
}

irr::core::rect<irr::s32> MorphLinear::getScreenRect(irr::u32 time){
  int newPosX = obj->getScreenPositionX()+ratioX*(time-startTime);
  int newPosY = obj->getScreenPositionY()+ratioY*(time-startTime);
  if(ratioX < 0){
    if(newPosX <= finalPosX){
      newPosX = finalPosX;
      if(ratioY < 0){
        if(newPosY <= finalPosY){
          newPosY = finalPosY;
          iComplete = true;
          inRun = false;
        }
      }else{
        if(newPosY >= finalPosY){
          newPosY = finalPosY;
          iComplete = true;
          inRun = true;
        }
      }
    }
  }else{
    if(newPosX >= finalPosX){
      newPosX = finalPosX;
      if(ratioY < 0){
        if(newPosY <= finalPosY){
          newPosY = finalPosY;
          iComplete = true;
          inRun = false;
        }
      }else{
        if(newPosY >= finalPosY){
          newPosY = finalPosY;
          iComplete = true;
          inRun = true;
        }
      }
    }
  }
  if(ratioY < 0){
    if(newPosY <= finalPosY){
      newPosY = finalPosY;
    }
  }else{
    if(newPosY >= finalPosY){
      newPosY = finalPosY;
    }
  }
  
  return irr::core::rect<irr::s32>(
    newPosX,newPosY,
    newPosX+obj->getScreenWidth(),newPosY+obj->getScreenHeight()
  );
}