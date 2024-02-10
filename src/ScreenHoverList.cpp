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
#include "ScreenHoverList.hpp"

#include <pthread.h>
#include <vector>
#include <stack>

namespace CrazyCrush {
namespace ScreenHoverList {

pthread_mutex_t access = PTHREAD_MUTEX_INITIALIZER;
typedef std::vector<ScreenHover*> sList;
sList list;
ScreenHover* lastHover = NULL;

bool addObject(ScreenHover* o){
  pthread_mutex_lock(&access);
  list.push_back(o);
  pthread_mutex_unlock(&access);
  return true;
}

bool remObject(ScreenHover* o,bool del){
  bool ret = false;
  pthread_mutex_lock(&access);
  if(lastHover == o)
    lastHover = NULL;
  for(sList::iterator it = list.begin(); it != list.end(); it++){
    if(*it == o){
      ret = true;
      if(del)
        (*it)->destroy();
      *it = NULL;
      list.erase(it);
      break;
    }
  }
  pthread_mutex_unlock(&access);
  return ret;
}

void mouseHover(int x,int y){
  pthread_mutex_lock(&access);
  bool find = false;
  for(sList::iterator it = list.begin(); it != list.end(); it++){
    if(*it == NULL)
      continue;
    if(!((*it)->isEnabled()))
      continue;
    if((*it)->mouseHover(x,y)){
      if(*it != lastHover){
        if(lastHover!=NULL){
          lastHover->mouseOut();
        }
        lastHover = *it;
      }
      find = true;
      break;
    }
  }
  if((lastHover!=NULL)&&(!find)){
    lastHover->mouseOut();
    lastHover = NULL;
  }
  pthread_mutex_unlock(&access);
}

void mouseClick(int x,int y){
  pthread_mutex_lock(&access);
  for(sList::iterator it = list.begin(); it != list.end(); it++){
    if(*it == NULL)
      continue;
    if(!((*it)->isEnabled()))
      continue;
    if((*it)->mouseHover(x,y)){
      ScreenHover *t = (*it);
      pthread_mutex_unlock(&access);
      t->mouseClick(x,y);
      return;
    }
  }
  pthread_mutex_unlock(&access);
}

void suspendAll(){
  pthread_mutex_lock(&access);
  for(sList::iterator it = list.begin(); it != list.end(); it++){
    if(*it == NULL)
      continue;
    (*it)->suspend();
  }
  pthread_mutex_unlock(&access);
}

void resumeAll(){
  pthread_mutex_lock(&access);
  for(sList::iterator it = list.begin(); it != list.end(); it++){
    if(*it == NULL)
      continue;
    (*it)->resume();
  }
  pthread_mutex_unlock(&access);
}

#ifdef DEBUG
void debug(){
  /*
  pthread_mutex_lock(&access);
  std::cout << __FILE__ << " @" << __LINE__ << "  stackPrint max: " << list.size() << std::endl;
  int i=0;
  for(sList::iterator it = list.begin(); it != list.end(); it++){
    std::cout << (*it) << " ";
    i++;
    if(i%5 == 0){
      std::cout << std::endl;
      i=0;
    }
  }
  if(i!=0)
    std::cout << std::endl;
  pthread_mutex_unlock(&access);
  */
}
#endif

}}