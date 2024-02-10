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
#include "ScreenButton.hpp"
#include "CallbackButtonOnHover.hpp"
#include "CallbackButtonOnOut.hpp"
#include "CallbackDestroy.hpp"

ScreenButton::ScreenButton(){
  sHover = NULL;
  display = false;
  isHover = false;
  oHover = new CallbackButtonOnHover(this);
  oOut = new CallbackButtonOnOut(this);
  posX = 0;
  posY = 0;
  width = 0;
  height = 0;
}

ScreenButton::~ScreenButton(){
  /*
  if(oHover != NULL){
    deleteCallback(oHover);
  }
  if(oOut != NULL){
    deleteCallback(oOut);
  }
  */
  sHover->destroy();
}

unsigned char ScreenButton::getType(){
  return AnimatorObject::typeScreenButton;
}

void ScreenButton::processTime(irr::u32 t){

}

void ScreenButton::aSetDisplay(bool b){
  this->setDisplay(b);
}

void ScreenButton::aSetScreenSize(unsigned w,unsigned h){
  this->setScreenSize(w,h);
}

void ScreenButton::aSetScreenPosition(int x,int y){
 this->setScreenPosition(x,y);
}

void ScreenButton::aSetImageColor(irr::video::SColor* a){}

irr::video::SColor* ScreenButton::getColor(){return NULL;}

unsigned ScreenButton::getScreenWidth(){
  return width;
}

unsigned ScreenButton::getScreenHeight(){
  return height;
}

int ScreenButton::getScreenPositionX(){
  return posX;
}

int ScreenButton::getScreenPositionY(){
  return posY;
}

bool ScreenButton::getDisplay(){
  return display;
}


ScreenButton& ScreenButton::setScreenSize(unsigned w,unsigned h){
  width = w;
  height = h;
  propagateScreenSize();
  return *this;
}

ScreenButton& ScreenButton::setScreenPosition(int x,int y){
  posX = x;
  posY = y;
  propagateScreenPosition();
  return *this;
}

ScreenButton& ScreenButton::setDisplay(bool b){
  display = b;
  propagateDisplay();
  return *this;
}

ScreenButton& ScreenButton::setOnClick(Callback* c){
  sHover->setClickEvent(c);
  return *this;
}

ScreenButton& ScreenButton::setOnHover(Callback* c){
  ((CallbackButtonOnHover*)oHover)->setPropagate(c);
  return *this;
}

ScreenButton& ScreenButton::setOnOut(Callback* c){
  ((CallbackButtonOnOut*)oOut)->setPropagate(c);
  return *this;
}

ScreenButton& ScreenButton::suspendHover(){
  if(sHover != NULL)
    sHover->suspend();
  return *this;
}