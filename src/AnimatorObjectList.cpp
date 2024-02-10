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
#include "AnimatorObjectList.hpp"

namespace CrazyCrush {
  AnimatorObjList AnimatorObjectList;
}

AnimatorObjList::AnimatorObjList(){
  pointer = 0;
  access = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
}

AnimatorObjList::~AnimatorObjList(){}

bool AnimatorObjList::addObject(AnimatorObject* o){
  pthread_mutex_lock(&access);
  content.push_back(o);
  pthread_mutex_unlock(&access);
  return true;
}

bool AnimatorObjList::remObject(AnimatorObject* o){
  pthread_mutex_lock(&access);
  bool finded = false;
  for(unsigned i=0;i<content.size();i++){
    if(content[i] == o){
      finded = true;
      content.erase(content.begin()+i);
      if(pointer > i)
        pointer--;
      i--;
    }
  }
  
  pthread_mutex_unlock(&access);
  return finded;
}

void AnimatorObjList::begin(){
  pthread_mutex_lock(&access);
  pointer = 0;
  pthread_mutex_unlock(&access);
}

AnimatorObject* AnimatorObjList::next(){
  AnimatorObject* t = NULL;
  pthread_mutex_lock(&access);
  if(pointer < content.size())
    t = content[pointer++];
  pthread_mutex_unlock(&access);
  return t;
}