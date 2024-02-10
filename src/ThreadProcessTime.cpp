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
#include "ThreadProcessTime.hpp"

#include <unistd.h>
#include "Timer.hpp"
#include "GameDefines.hpp"
#include "GameControl.hpp"
#include "CoreProcess.hpp"
#include "AnimatorObjectList.hpp"
#include "AudioManager.hpp"
#include "Score.hpp"
#include "Logger.hpp"
#include "CallbackDestroy.hpp"
#include "ScreenHover.hpp"

namespace CrazyCrush {
namespace Thread {

pthread_mutex_t ProcessTimeMutex;
pthread_t ProcessTimeThread;
bool ProcessTimeControl;
irr::u32 lastTime = 0;

void* ProcessTime(void*);

bool startProcessTime(){
  pthread_mutex_lock(&ProcessTimeMutex);
  ProcessTimeControl = true;
  pthread_mutex_unlock(&ProcessTimeMutex);
  LOG_INFO("Starting ThreadProcessTime");
  if(pthread_create(&ProcessTimeThread,NULL,ProcessTime,NULL) != 0)
    return false;
  return true;
}

void stopProcessTime(){
  pthread_mutex_lock(&ProcessTimeMutex);
  LOG_INFO("Stopping ThreadProcessTime");
  ProcessTimeControl = false;
  pthread_mutex_unlock(&ProcessTimeMutex);
  pthread_join(ProcessTimeThread,NULL);
}

//! Thread de processamento no tempo
void* ProcessTime(void*){
  AudioManager::play("no_name",true);
  AnimatorObject* obj;
  pthread_mutex_lock(&ProcessTimeMutex);
  while(ProcessTimeControl){
  pthread_mutex_unlock(&ProcessTimeMutex);
    if(lastTime == getTime()){
      usleep(10000);
      continue;
    }
    lastTime = getTime();
    CrazyCrush::Score::trigger();
    CrazyCrush::Game::Control::processGameTimer();
    //std::cout << "ThreadProcessTimeRunning" <<std::endl;
    for(unsigned i=0;i<Screen::num_rows;i++){
      for(unsigned j=0;j<Screen::num_columns;j++){
        Screen::matrix.at(i,j)->processTime(getGameTime());
      }
    }
    CrazyCrush::AnimatorObjectList.begin();
    while((obj = CrazyCrush::AnimatorObjectList.next())!=NULL){
      obj->processTime(getTime());
    }
    if(CrazyCrush::core::triggerCheckMatrix.get()){
      CrazyCrush::core::checkFullMatrix();
      CrazyCrush::core::processFall();
    }
    
    realCallbackDestroy();
    realScreenHoverDestroy();
  pthread_mutex_lock(&ProcessTimeMutex);
  }
  LOG_INFO("Stopped ThreadProcessTime");
  return NULL;
}

}}