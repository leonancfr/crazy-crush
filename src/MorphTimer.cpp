/* Universidade Federal do Rio de Janeiro
 * Escola Polit�cnica
 * Departamento de Eletr�nica e Computa��o
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programa��o
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan Fran�a    (leonancfr@poli.ufrj.br)
 *          Gustavo Silva    (diguser@gmail.com)
 *          Michael Douglas  (michaeldouglas@poli.ufrj.br)
 */
#include "MorphTimer.hpp"

MorphTimer::MorphTimer(irr::u32 t){
  duration = t;
}

MorphTimer& MorphTimer::setDuration(irr::u32 t){
  duration = t;
  return *this;
}

irr::core::rect<irr::s32> MorphTimer::getScreenRect(irr::u32 time){
  if(time-startTime > duration){
    iComplete = true;
    inRun = false;
  }
  
  return irr::core::rect<irr::s32>(
    obj->getScreenPositionX(),obj->getScreenPositionY(),
    obj->getScreenPositionX()+obj->getScreenWidth(),obj->getScreenPositionY()+obj->getScreenHeight()
  );
}

void MorphTimer::internalTrigger(irr::u32 time){
  if(time-startTime > duration){
    iComplete = true;
    inRun = false;
  }
}