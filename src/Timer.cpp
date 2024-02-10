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
#include "Timer.hpp"
#include "Protected.hpp"
#include <pthread.h>

namespace CrazyCrush {
  namespace Timer {
    irr::u32 protectedTime = 0;
    pthread_mutex_t timerMutex = PTHREAD_MUTEX_INITIALIZER;
    Protected<bool> gameTimerIsPaused(false);
    Protected<irr::u32> gameTimerPausedStart(0);
    Protected<irr::u32> gameTimerPaused(0);
    
    
    Protected<bool> levelTimerIsPaused(false);
    Protected<irr::u32> levelTimerPausedStart(0);
    Protected<irr::u32> levelTimerPaused(0);
  }
}

void setTime(irr::u32 t){
  pthread_mutex_lock(&CrazyCrush::Timer::timerMutex);
  CrazyCrush::Timer::protectedTime = t;
  pthread_mutex_unlock(&CrazyCrush::Timer::timerMutex);
}

irr::u32 getUnprotectedTime(){
  return CrazyCrush::Timer::protectedTime;
}

irr::u32 getTime(){
  irr::u32 t;
  pthread_mutex_lock(&CrazyCrush::Timer::timerMutex);
  t = CrazyCrush::Timer::protectedTime;
  pthread_mutex_unlock(&CrazyCrush::Timer::timerMutex);
  return t;
}


irr::u32 getGameTime(){
  if(CrazyCrush::Timer::gameTimerIsPaused.get()){
    return CrazyCrush::Timer::gameTimerPausedStart.get()-CrazyCrush::Timer::gameTimerPaused.get();
  }else{
    return getTime()-CrazyCrush::Timer::gameTimerPaused.get();
  }
}
/*
void resetGameTimer(){
  CrazyCrush::Timer::gameTimerPaused.set(0);
  CrazyCrush::Timer::gameTimerPausedStart.set(0);
  CrazyCrush::Timer::gameTimerIsPaused.set(false);
}
*/
void pauseGameTimer(){
  if(CrazyCrush::Timer::gameTimerIsPaused.get())
    return;
  CrazyCrush::Timer::gameTimerIsPaused.set(true);
  CrazyCrush::Timer::gameTimerPausedStart.set(getTime());
}

void resumeGameTimer(){
  if(!CrazyCrush::Timer::gameTimerIsPaused.get())
    return;
  CrazyCrush::Timer::gameTimerIsPaused.set(false);
  CrazyCrush::Timer::gameTimerPaused.set(CrazyCrush::Timer::gameTimerPaused.get()+(getTime()-CrazyCrush::Timer::gameTimerPausedStart.get()));
  CrazyCrush::Timer::gameTimerPausedStart.set(0);
}
/*
void increaseGameTimer(unsigned v){
  if(CrazyCrush::Timer::gameTimerPaused.get() <= v){
    CrazyCrush::Timer::gameTimerPaused.set(0);
    return;
  }
  CrazyCrush::Timer::gameTimerPaused.set(CrazyCrush::Timer::gameTimerPaused.get()-v);
}
void decreaseGameTimer(unsigned v){
  CrazyCrush::Timer::gameTimerPaused.set(CrazyCrush::Timer::gameTimerPaused.get()+v);
}
*/

irr::u32 getLevelTime(){
  if(CrazyCrush::Timer::levelTimerIsPaused.get())
    return CrazyCrush::Timer::levelTimerPausedStart.get()-CrazyCrush::Timer::levelTimerPaused.get();
  else
    return getGameTime()-CrazyCrush::Timer::levelTimerPaused.get();
}

void resetLevelTimer(){
  CrazyCrush::Timer::levelTimerPaused.set(getGameTime());
  CrazyCrush::Timer::levelTimerIsPaused.set(false);
}

void pauseLevelTimer(){
  if(CrazyCrush::Timer::levelTimerIsPaused.get())
    return;
  CrazyCrush::Timer::levelTimerIsPaused.set(true);
  CrazyCrush::Timer::levelTimerPausedStart.set(getGameTime());
}

void resumeLevelTimer(){
  if(!CrazyCrush::Timer::levelTimerIsPaused.get())
    return;
  CrazyCrush::Timer::levelTimerIsPaused.set(false);
  CrazyCrush::Timer::levelTimerPaused.set(CrazyCrush::Timer::levelTimerPaused.get()+(getGameTime()-CrazyCrush::Timer::levelTimerPausedStart.get()));
  CrazyCrush::Timer::levelTimerPausedStart.set(0);
}

void increaseLevelTimer(unsigned v){
  if(CrazyCrush::Timer::levelTimerPaused.get() <= v){
    CrazyCrush::Timer::levelTimerPaused.set(0);
    return;
  }
  CrazyCrush::Timer::levelTimerPaused.set(CrazyCrush::Timer::levelTimerPaused.get()-v);
}

void decreaseLevelTimer(unsigned v){
  CrazyCrush::Timer::levelTimerPaused.set(CrazyCrush::Timer::levelTimerPaused.get()+v);
}
