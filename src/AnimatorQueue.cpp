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
#include "AnimatorQueue.hpp"
#include "MorphLinear.hpp"
#include "CallbackDestroy.hpp"

AnimatorQueue::AnimatorQueue(){
  object = NULL;
  animationStart = 0;
  actualStep = 0;
  objColor = NULL;
  isComplete = false;
  skipCallback = false;
  isInCallback = false;
  vectors_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER;
}

AnimatorQueue& AnimatorQueue::operator=(AnimatorQueue& other){
  for(unsigned i=0; i < other.animations.size(); i++){
    animations.push_back(other.animations[i]);
  }
  return *this;
}

bool AnimatorQueue::setObject(AnimatorObject* nObj){
  if(object == NULL){
    object = nObj;
    for(unsigned i=animations.size(); i < animations.size(); i++){
      animations[i]->setObject(nObj);
    }
    return true;
  }
  if(object == nObj){
    for(unsigned i=animations.size(); i < animations.size(); i++){
      animations[i]->setObject(nObj);
    }
    return true;
  }
  return false;
}

void AnimatorQueue::processStep(irr::u32 time){
  if((animationStart == 0)||(isComplete))
    return;
  if(actualStep == time)
    return;
  actualStep = time;
  pthread_mutex_lock(&vectors_mutex);
  for(std::vector<ObjectMorph*>::iterator it=animations.begin();it!=animations.end();it++){
    if(*it == NULL)
      continue;
    if(!(*it)->isRunning())
      (*it)->start(time);
    screenRect = (*it)->getScreenRect(time);
    objColor = (*it)->getImageAlpha(time);
    if((*it)->isComplete()){
      object->aSetImageColor(objColor);
      object->aSetScreenPosition(screenRect.UpperLeftCorner.X,screenRect.UpperLeftCorner.Y);
      object->aSetScreenSize(screenRect.getWidth(),screenRect.getHeight());
      delete (*it);
      animations.erase(it);
    }
    pthread_mutex_unlock(&vectors_mutex);
    return;
  }
  isComplete = true;
  isInCallback = true;
  for(unsigned i=0;i<callbacks.size();i++){
    if(skipCallback)
      break;
    if(callbacks[i] == NULL)
      continue;
    callbacks[i]->process();
    if(skipCallback)
      break;
    deleteCallback(callbacks[i]);
    callbacks.erase(callbacks.begin()+i);
    i--;
  }
  isInCallback = false;
  skipCallback = false;
  pthread_mutex_unlock(&vectors_mutex);
}

irr::core::rect<irr::s32> AnimatorQueue::getScreenRect(irr::u32 time){
  if(animationStart == 0){
    return irr::core::rect<irr::s32>(
      object->getScreenPositionX(),
      object->getScreenPositionY(),
      object->getScreenPositionX()+object->getScreenWidth(),
      object->getScreenPositionY()+object->getScreenHeight()
    );
  }
  processStep(time);
  return screenRect;
}

irr::video::SColor* AnimatorQueue::getImageAlpha(irr::u32 time){
  if(animationStart == 0)
    return object->getColor();
  processStep(time);
  return objColor;
}

bool AnimatorQueue::isRunning(){
  if(isComplete)
    return false;
  if(animationStart == 0)
    return false;
  return true;
}

AnimatorQueue& AnimatorQueue::stopAnimation(){
  isComplete = true;
  pthread_mutex_lock(&vectors_mutex);
  animationStart = 0;
  isComplete = false;
  if(isInCallback){
    skipCallback = true;
  }
  for(unsigned i=0;i<animations.size();i++){
    if(animations[i] != NULL){
      delete animations[i];
      animations[i] = NULL;
    }
  }
  for(unsigned i=0;i<callbacks.size();i++){
    if(callbacks[i] != NULL){
      deleteCallback(callbacks[i]);
      callbacks[i] = NULL;
    }
  }
  animations.resize(0);
  callbacks.resize(0);
  pthread_mutex_unlock(&vectors_mutex);
  return *this;
}

AnimatorQueue& AnimatorQueue::startAnimation(irr::u32 time){
  animationStart = time;
  isComplete = false;
  return *this;
}

AnimatorQueue& AnimatorQueue::appendMorph(ObjectMorph* objMorph){
  animations.push_back(objMorph);
  return *this;
}

AnimatorQueue& AnimatorQueue::appendCallback(Callback* c){
  callbacks.push_back(c);
  return *this;
}