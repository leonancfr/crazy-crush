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
#include "ScreenButtonSprite.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "ScreenHoverRect.hpp"

ScreenButtonSprite::ScreenButtonSprite():button(CrazyCrush::TextureCache::sprites){
  oZOrder = -20;
  sHover = new ScreenHoverRect(0,0,0,0);
  sHover->setHoverEvent(oHover);
  sHover->setOutEvent(oOut);
  button.setDisplay(display);
  propagateScreenSize();
  propagateScreenPosition();
}

ScreenButtonSprite::~ScreenButtonSprite(){
  CrazyCrush::z_order.remObject(&button,oZOrder);
}

ScreenButtonSprite& ScreenButtonSprite::setNormalOffset(int x,int y){
  normalX = x;
  normalY = y;
  if(!isHover){
    button.setResourcePosition(x,y);
  }
  return *this;
}

ScreenButtonSprite& ScreenButtonSprite::setNormalSize(unsigned w,unsigned h){
  normalW = w;
  normalH = h;
  if(!isHover){
    button.setResourceSize(w,h);
  }
  return *this;
}

ScreenButtonSprite& ScreenButtonSprite::setHoverOffset(int x,int y){
  hoverX = x;
  hoverY = y;
  if(isHover){
    button.setResourcePosition(x,y);
  }
  return *this;
}

ScreenButtonSprite& ScreenButtonSprite::setHoverSize(unsigned w,unsigned h){
  hoverW = w;
  hoverH = h;
  if(isHover){
    button.setResourceSize(w,h);
  }
  return *this;
}


void ScreenButtonSprite::onHover(){
  if(isHover)
    return;
  isHover = true;
  button.setResourcePosition(hoverX,hoverY).setResourceSize(hoverW,hoverH);
}

void ScreenButtonSprite::onOut(){
  if(!isHover)
    return;
  isHover = false;
  button.setResourcePosition(normalX,normalY).setResourceSize(normalW,normalH);
}

void ScreenButtonSprite::propagateScreenSize(){
  button.setScreenSize(width,height);
  ((ScreenHoverRect*)sHover)->setSize(width,height);
}

void ScreenButtonSprite::propagateScreenPosition(){
  button.setScreenPosition(posX,posY);
  ((ScreenHoverRect*)sHover)->setPosition(posX,posY);
}

void ScreenButtonSprite::propagateDisplay(){
  button.setDisplay(display);
  sHover->setEnabled(display);
  if(display == true){
    CrazyCrush::z_order.addObject(&button,oZOrder);
  }else{
    CrazyCrush::z_order.remObject(&button,oZOrder);
  }
}

void ScreenButtonSprite::setZIndex(int z){
  if(z == oZOrder)
    return;
  oZOrder = z;
}

int ScreenButtonSprite::getOffsetX(unsigned char t){
  switch(t){
    default:
    case button_refresh:
    case button_right:
    case button_up:
      return 505;
    case button_refresh_gray:
    case button_right_gray:
    case button_up_gray:
      return 521;
    case button_no:
    case button_close:
    case button_down:
      return 537;
    case button_no_gray:
    case button_close_gray:
    case button_down_gray:
      return 553;
    case button_trash:
    case button_left:
    case button_right_white:
      return 569;
    case button_trash_gray:
    case button_left_gray:
    case button_left_white:
      return 585;
    case button_edit:
    case button_yes:
    case button_down_white:
      return 601;
    case button_edit_gray:
    case button_yes_gray:
    case button_up_white:
      return 617;
  }
  return 506;
}

int ScreenButtonSprite::getOffsetY(unsigned char t){
  switch(t){
    default:
    case button_refresh:
    case button_refresh_gray:
    case button_no:
    case button_no_gray:
    case button_trash:
    case button_trash_gray:
    case button_edit:
    case button_edit_gray:
      return 504;
    case button_close:
    case button_close_gray:
    case button_yes:
    case button_yes_gray:
    case button_right:
    case button_right_gray:
    case button_left:
    case button_left_gray:
      return 520;
    case button_up:
    case button_up_gray:
    case button_down:
    case button_down_gray:
    case button_right_white:
    case button_left_white:
    case button_down_white:
    case button_up_white:
      return 536;
  }
  return 504;
}

unsigned ScreenButtonSprite::getWidth(unsigned char t){
  return 16;
}

unsigned ScreenButtonSprite::getHeight(unsigned char t){
  return 16;
}