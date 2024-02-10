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
#include "ScreenButtonDefault.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "ScreenHoverRect.hpp"

ScreenButtonDefault::ScreenButtonDefault():background(CrazyCrush::TextureCache::buttons),label(CrazyCrush::TextureCache::font1){
  oZOrder = -20;
  width = 197;
  height = 60;
  sHover = new ScreenHoverRect(0,0,197,60);
  sHover->setHoverEvent(oHover);
  sHover->setOutEvent(oOut);
  background.setDisplay(display);
  background.setResourcePosition(1,1);
  background.setResourceSize(197,60);
  label.setDisplay(display);
  label.setScreenAlign(ScreenText::center);
  label.setColor(255,255,255,255);
  propagateScreenSize();
  propagateScreenPosition();
}

ScreenButtonDefault::~ScreenButtonDefault(){
  CrazyCrush::z_order.remObject(&background,oZOrder);
  CrazyCrush::z_order.remObject(&label,oZOrder);
}

ScreenButtonDefault& ScreenButtonDefault::setLabel(std::string str){
  label.setString(str);
  return *this;
}

std::string ScreenButtonDefault::getLabel(){
  return label.getString();
}

void ScreenButtonDefault::onHover(){
  if(isHover)
    return;
  isHover = true;
  background.setResourcePosition(1,63);
}

void ScreenButtonDefault::onOut(){
  if(!isHover)
    return;
  isHover = false;
  background.setResourcePosition(1,1);
}

void ScreenButtonDefault::propagateScreenSize(){
  background.setScreenSize(width,height);
  ((ScreenHoverRect*)sHover)->setSize(width,height);
}

void ScreenButtonDefault::propagateScreenPosition(){
  background.setScreenPosition(posX,posY);
  ((ScreenHoverRect*)sHover)->setPosition(posX,posY);
  label.setScreenPosition((width/2)+posX,(height/2)+posY);
}

void ScreenButtonDefault::propagateDisplay(){
  background.setDisplay(display);
  label.setDisplay(display);
  sHover->setEnabled(display);
  if(display == true){
    CrazyCrush::z_order.addObject(&background,oZOrder);
    CrazyCrush::z_order.addObject(&label,oZOrder);
  }else{
    CrazyCrush::z_order.remObject(&background,oZOrder);
    CrazyCrush::z_order.remObject(&label,oZOrder);
  }
}

void ScreenButtonDefault::setZIndex(int z){
  if(z == oZOrder)
    return;
  oZOrder = z;
}