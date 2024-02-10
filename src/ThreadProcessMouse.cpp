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
#include "ThreadProcessMouse.hpp"
#include "Protected.hpp"
#include "ScreenHoverList.hpp"
#include "Logger.hpp"
#include <pthread.h>
#include <unistd.h>

namespace CrazyCrush {
namespace ThreadProcessMouse {

  pthread_t ProcessMouseThread;
  Protected<bool> isRunning(false),click(false);
  Protected<int> X(-1),Y(-1);

  //! Thread de processamento do Mouse
  void* ProcessMouse(void* t){
    int lastX = -1;
    int lastY = -1;
    while(isRunning.get()){
      if(lastX==X.get()&&lastY==Y.get()&&!click.get()){
        usleep(1000);
        continue;
      }
      lastX = X.get();
      lastY = Y.get();
      ScreenHoverList::mouseHover(lastX,lastY);
      if(click.get()){
        click.set(false);
        ScreenHoverList::mouseClick(lastX,lastY);
      }
    }
    LOG_INFO("Stopped ThreadProcessMouse");
    return NULL;
  }
  
  void setCursor(int x,int y){
    X.set(x);
    Y.set(y);
  }
  
  void setClick(){
    click.set(true);
  }
}
namespace Thread {

  bool startProcessMouse(){
    ThreadProcessMouse::isRunning.set(true);
    LOG_INFO("Starting ThreadProcessMouse");
    if(pthread_create(&ThreadProcessMouse::ProcessMouseThread,NULL,ThreadProcessMouse::ProcessMouse,NULL) != 0)
      return false;
    return true;
  }
  
  void stopProcessMouse(){
    LOG_INFO("Stopping ThreadProcessMouse");
    ThreadProcessMouse::isRunning.set(false);
    pthread_join(ThreadProcessMouse::ProcessMouseThread,NULL);
  }

}}