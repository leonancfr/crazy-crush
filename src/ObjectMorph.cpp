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
#include "ObjectMorph.hpp"
#include <stdexcept>

ObjectMorph::ObjectMorph(){
  obj = NULL;
  startTime = 0;
  inRun = false;
  iComplete = false;
}

ObjectMorph::~ObjectMorph(){}

void ObjectMorph::setObject(AnimatorObject* nObj){
  obj = nObj;
}

bool ObjectMorph::hasObject(){
  if(obj == NULL)
    return false;
  return true;
}

/*
ScreenObject& ObjectMorph::getObject(){
  if(obj == NULL)
    throw std::runtime_error("ObjectMorph::getObject() -> null pointer");
  return *obj;
}
*/

bool ObjectMorph::start(irr::u32 time){
  if(inRun)
    return false;
  startTime = time;
  inRun = true;
  internalTrigger(time);
  return true;
}

bool ObjectMorph::stop(){
  if(!inRun)
    return false;
  inRun = false;
  return true;
}

bool ObjectMorph::isRunning(){
  return inRun;
}

irr::core::rect<irr::s32> ObjectMorph::getResourceRect(irr::u32 time){
  return irr::core::rect<irr::s32>(0,0,0,0);
}

irr::video::SColor* ObjectMorph::getImageAlpha(irr::u32 time){
  return obj->getColor();
}

bool ObjectMorph::isComplete(){
  return iComplete;
}

ObjectMorph& ObjectMorph::operator=(ObjectMorph& other){
  obj = other.obj;
  startTime = other.startTime;
  inRun = other.inRun;
  iComplete = other.iComplete;
  return *this;
}