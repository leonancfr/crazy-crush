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
#include "ScreenButtonCircle.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "ScreenHoverCircle.hpp"

int colorToPositionX(unsigned char c){
  switch(c){
    case ScreenButtonCircle::red:
    case ScreenButtonCircle::blue_light:
      return 0;
    case ScreenButtonCircle::orange:
    case ScreenButtonCircle::blue:
      return 400;
    case ScreenButtonCircle::green:
    default:
      return 800;
  }
  return 0;
}

int colorToPositionY(unsigned char c){
  switch(c){
    case ScreenButtonCircle::red:
    case ScreenButtonCircle::orange:
    case ScreenButtonCircle::green:
    default:
      return 0;
    case ScreenButtonCircle::blue_light:
    case ScreenButtonCircle::blue:
      return 400;
  }
  return 0;
}

ScreenButtonCircle::ScreenButtonCircle():background(CrazyCrush::TextureCache::buttons_circle),label(CrazyCrush::TextureCache::font1){
  oZOrder = -20;
  width = 398;
  height = 398;
  normalColor = blue;
  hoverColor = blue_light;
  labelOffsetX = labelOffsetY = 0;
  sHover = new ScreenHoverCircle(0,0,199);
  sHover->setHoverEvent(oHover);
  sHover->setOutEvent(oOut);
  background.setDisplay(display);
  background.setResourcePosition(400,400);
  background.setResourceSize(398,398);
  label.setDisplay(display);
  label.setScreenAlign(ScreenText::center);
  label.setColor(255,255,255,255);
  label.setScreenPosition(0,0);
  propagateScreenSize();
  propagateScreenPosition();
}

ScreenButtonCircle::~ScreenButtonCircle(){
  CrazyCrush::z_order.remObject(&background,oZOrder);
  CrazyCrush::z_order.remObject(&label,oZOrder);
}

ScreenButtonCircle& ScreenButtonCircle::setLabel(std::string str){
  label.setString(str);
  return *this;
}

ScreenButtonCircle& ScreenButtonCircle::setLabelOffset(int X,int Y){
  labelOffsetX = X;
  labelOffsetY = Y;
  propagateScreenPosition();
  return *this;
}

ScreenButtonCircle& ScreenButtonCircle::setButtonColor(unsigned char c){
  normalColor = c;
  return *this;
}

ScreenButtonCircle& ScreenButtonCircle::setButtonColorHover(unsigned char c){
  hoverColor = c;
  return *this;
}

std::string ScreenButtonCircle::getLabel(){
  return label.getString();
}

int ScreenButtonCircle::getLabelOffsetX(){
  return labelOffsetX;
}

int ScreenButtonCircle::getLabelOffsetY(){
  return labelOffsetY;
}

unsigned char ScreenButtonCircle::getButtonColor(){
  return normalColor;
}

unsigned char ScreenButtonCircle::getButtonColorHover(){
  return hoverColor;
}

void ScreenButtonCircle::onHover(){
  if(isHover)
    return;
  isHover = true;
  background.setResourcePosition(colorToPositionX(hoverColor),colorToPositionY(hoverColor));
}

void ScreenButtonCircle::onOut(){
  if(!isHover)
    return;
  isHover = false;
  background.setResourcePosition(colorToPositionX(normalColor),colorToPositionY(normalColor));
}

void ScreenButtonCircle::propagateScreenSize(){
  background.setScreenSize(width,width);
  ((ScreenHoverCircle*)sHover)->setRadius(width/2);
  ((ScreenHoverCircle*)sHover)->setPosition((width/2)+posX,(width/2)+posY);
  label.setScreenPosition((width/2)+posX+labelOffsetX,(width/2)+posY+labelOffsetY);
}

void ScreenButtonCircle::propagateScreenPosition(){
  background.setScreenPosition(posX,posY);
  ((ScreenHoverCircle*)sHover)->setPosition((width/2)+posX,(width/2)+posY);
  label.setScreenPosition((width/2)+posX+labelOffsetX,(width/2)+posY+labelOffsetY);
}

void ScreenButtonCircle::propagateDisplay(){
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

void ScreenButtonCircle::setZIndex(int z){
  if(z == oZOrder)
    return;
  oZOrder = z;
}

ScreenText& ScreenButtonCircle::getLabelObject(){
  return label;
}