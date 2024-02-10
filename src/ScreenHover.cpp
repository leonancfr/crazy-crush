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
#include "ScreenHover.hpp"
#include "ZOrder.hpp"
#include "ScreenHoverList.hpp"
#include "CallbackDestroy.hpp"
#include <stack>

ScreenHover::ScreenHover(){
  callback = NULL;
  hover = NULL;
  out = NULL;
  enabled = false;
  mutexEnabled = PTHREAD_MUTEX_INITIALIZER;
  mutexClick = PTHREAD_MUTEX_INITIALIZER;
  mutexHover = PTHREAD_MUTEX_INITIALIZER;
  mutexOut = PTHREAD_MUTEX_INITIALIZER;
  CrazyCrush::ScreenHoverList::addObject(this);
}

ScreenHover::~ScreenHover(){
  pthread_mutex_lock(&mutexEnabled);
  enabled = false;
  pthread_mutex_unlock(&mutexEnabled);
  CrazyCrush::ScreenHoverList::remObject(this);
  pthread_mutex_lock(&mutexClick);
  pthread_mutex_lock(&mutexHover);
  pthread_mutex_lock(&mutexOut);
  if(callback != NULL){
    deleteCallback(callback);
  }
  if(hover != NULL){
    deleteCallback(hover);
  }
  if(out != NULL){
    deleteCallback(out);
  }
  pthread_mutex_unlock(&mutexClick);
  pthread_mutex_unlock(&mutexHover);
  pthread_mutex_unlock(&mutexOut);
}

ScreenHover& ScreenHover::setClickEvent(Callback* t){
  pthread_mutex_lock(&mutexClick);
  if(callback != NULL)
    deleteCallback(callback);
  callback = t;
  pthread_mutex_unlock(&mutexClick);
  return *this;
}

ScreenHover& ScreenHover::setHoverEvent(Callback* t){
  pthread_mutex_lock(&mutexHover);
  if(hover != NULL)
    deleteCallback(hover);
  hover = t;
  pthread_mutex_unlock(&mutexHover);
  return *this;
}

ScreenHover& ScreenHover::setOutEvent(Callback* t){
  pthread_mutex_lock(&mutexOut);
  if(out != NULL)
    deleteCallback(out);
  out = t;
  pthread_mutex_unlock(&mutexOut);
  return *this;
}

bool ScreenHover::mouseHover(int x,int y){
  pthread_mutex_lock(&mutexHover);
  if(!isHover(x,y)){
    pthread_mutex_unlock(&mutexHover);
    return false;
  }
  if(hover != NULL)
    hover->process();
  pthread_mutex_unlock(&mutexHover);
  return true;
}

bool ScreenHover::mouseClick(int x,int y){
  pthread_mutex_lock(&mutexClick);
  if(!isHover(x,y)){
    pthread_mutex_unlock(&mutexClick);
    return false;
  }
  if(callback != NULL)
    callback->process();
  pthread_mutex_unlock(&mutexClick);
  return true;
}

void ScreenHover::mouseOut(){
  pthread_mutex_lock(&mutexOut);
  if(out != NULL)
    out->process();
  pthread_mutex_unlock(&mutexOut);
}

bool ScreenHover::isEnabled(){
  bool t;
  pthread_mutex_lock(&mutexEnabled);
  t = enabled;
  pthread_mutex_unlock(&mutexEnabled);
  return t;
}

void ScreenHover::setEnabled(bool t){
  pthread_mutex_lock(&mutexEnabled);
  if((enabled)&&(t==false))
    this->mouseOut();
  enabled = t;
  pthread_mutex_unlock(&mutexEnabled);
}

void ScreenHover::resetStack(bool v){
  pthread_mutex_lock(&mutexEnabled);
  while(!stackEnabled.empty())
    stackEnabled.pop();
  if(enabled&&!v)
    this->mouseOut();
  enabled = v;
  pthread_mutex_unlock(&mutexEnabled);
}

void ScreenHover::suspend(){
  pthread_mutex_lock(&mutexEnabled);
  stackEnabled.push(enabled);
  if(enabled)
    this->mouseOut();
  enabled = false;
  pthread_mutex_unlock(&mutexEnabled);
}

void ScreenHover::resume(){
  pthread_mutex_lock(&mutexEnabled);
  if(stackEnabled.empty())
    return;
  enabled = stackEnabled.top();
  stackEnabled.pop();
  pthread_mutex_unlock(&mutexEnabled);
}


std::stack<ScreenHover*> stackHover;
pthread_mutex_t accessStackHover = PTHREAD_MUTEX_INITIALIZER;


void ScreenHover::destroy(){
  CrazyCrush::ScreenHoverList::remObject(this);
  pthread_mutex_lock(&accessStackHover);
  stackHover.push(this);
  pthread_mutex_unlock(&accessStackHover);
  return;
}

void realScreenHoverDestroy(){
  pthread_mutex_lock(&accessStackHover);
  if(!stackHover.empty()){
    delete stackHover.top();
    stackHover.pop();
  }
  pthread_mutex_unlock(&accessStackHover);
}