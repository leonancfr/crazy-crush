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
#include "ScreenButtonSimple.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"
#include "ScreenHoverRect.hpp"

ScreenButtonSimple::ScreenButtonSimple():
  background(CrazyCrush::TextureCache::buttons),
  icon(CrazyCrush::TextureCache::sprites),
  label(CrazyCrush::TextureCache::font1),
  normalText(255,255,255,255),
  hoverText(255,255,255,255)
{
  oZOrder = -20;
  sHover = new ScreenHoverRect(0,0,0,0);
  sHover->setHoverEvent(oHover);
  sHover->setOutEvent(oOut);
  background.setDisplay(display);
  icon.setDisplay(display);
  label.setDisplay(display);
  iconAlign = button_left;
  bg_normal_resource.W = bg_hover_resource.W = bg_normal.W = bg_hover.W = 156;
  bg_normal_resource.H = bg_hover_resource.H = bg_normal.H = bg_hover.H = 32;
  bg_normal.X = bg_normal.Y = bg_hover.X = bg_hover.Y = 0;
  text_normal.X = text_normal.Y = text_hover.X = text_hover.Y = 0;
  icon_normal.X = icon_normal.Y = icon_hover.X = icon_hover.Y = 0;
  icon_normal.W = icon_normal.H = icon_hover.W = icon_hover.H = 0;
  propagateScreenSize();
  propagateScreenPosition();
}

ScreenButtonSimple::~ScreenButtonSimple(){
  CrazyCrush::z_order.remObject(&background,oZOrder);
  CrazyCrush::z_order.remObject(&icon,oZOrder);
  CrazyCrush::z_order.remObject(&label,oZOrder);
}

///   TEXT Start

ScreenButtonSimple& ScreenButtonSimple::setLabel(std::string s){
  label.setString(s);
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setLabelOffset(int x,int y){
  text_normal.X = x;
  text_normal.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setLabelOffsetHover(int x,int y){
  text_hover.X = x;
  text_hover.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setLabelColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b){
  normalText.set(a,r,g,b);
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setLabelColorHover(unsigned char a,unsigned char r,unsigned char g,unsigned char b){
  hoverText.set(a,r,g,b);
  return *this;
}

//\   TEXT END

///   ICON Start

ScreenButtonSimple& ScreenButtonSimple::setIconOffset(int x,int y){
  icon_normal.X = x;
  icon_normal.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setIconOffsetHover(int x,int y){
  icon_hover.X = x;
  icon_hover.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setIconSize(unsigned w,unsigned h){
  icon_normal.W = w;
  icon_normal.H = h;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setIconSizeHover(unsigned w,unsigned h){
  icon_hover.W = w;
  icon_hover.H = h;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setIconResourceOffset(int x,int y){
  icon_normal_resource.X = x;
  icon_normal_resource.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setIconResourceOffsetHover(int x,int y){
  icon_hover_resource.X = x;
  icon_hover_resource.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setIconResourceSize(unsigned w,unsigned h){
  icon_normal_resource.W = w;
  icon_normal_resource.H = h;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setIconResourceSizeHover(unsigned w,unsigned h){
  icon_hover_resource.W = w;
  icon_hover_resource.H = h;
  propagateAdjust();
  return *this;
}

//\   ICON End

///   BG   Start

ScreenButtonSimple& ScreenButtonSimple::setButtonColor(unsigned char t){
  bg_normal_resource.X = buttonOffsetX(t);
  bg_normal_resource.Y = buttonOffsetY(t);
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setButtonColorHover(unsigned char t){
  bg_hover_resource.X = buttonOffsetX(t);
  bg_hover_resource.Y = buttonOffsetY(t);
  propagateAdjust();
  return *this;
}


ScreenButtonSimple& ScreenButtonSimple::setButtonOffset(int x,int y){
  bg_normal.X = x;
  bg_normal.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setButtonOffsetHover(int x,int y){
  bg_hover.X = x;
  bg_hover.Y = y;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setButtonSize(unsigned w,unsigned h){
  bg_normal.W = w;
  bg_normal.H = h;
  propagateAdjust();
  return *this;
}

ScreenButtonSimple& ScreenButtonSimple::setButtonSizeHover(unsigned w,unsigned h){
  bg_hover.W = w;
  bg_hover.H = h;
  propagateAdjust();
  return *this;
}

//\   BG End

///   Events Start

void ScreenButtonSimple::onHover(){
  if(isHover)
    return;
  isHover = true;
  propagateAdjust();
}

void ScreenButtonSimple::onOut(){
  if(!isHover)
    return;
  isHover = false;
  propagateAdjust();
}

//\   Events End

///   Propagates functions

void ScreenButtonSimple::propagateIconHover(){
  if(!display)
    return;
  icon.setScreenSize(icon_hover.W,icon_hover.H).setResourcePosition(icon_hover_resource.X,icon_hover_resource.Y).setResourceSize(icon_hover_resource.W,icon_hover_resource.H);
  if((iconAlign == button_left)||((iconAlign == text_left)&&(label.getScreenAlign() == ScreenText::left))){
    icon.setScreenPosition(posX+bg_hover.X+icon_hover.X,posY+bg_hover.Y+icon_hover.Y);
    if(label.getScreenAlign() == ScreenText::left){
      label.setScreenPosition(posX+bg_hover.X+icon_hover.X+icon_hover.W+text_hover.X,posY+bg_hover.Y+text_hover.Y);
    }else if(label.getScreenAlign() == ScreenText::center){
      label.setScreenPosition(posX+bg_hover.X+(icon_hover.X+icon_hover.W+text_hover.X+bg_hover.W)/2,posY+bg_hover.Y+text_hover.Y);
    }else{
      label.setScreenPosition(posX+bg_hover.X+bg_hover.W-text_hover.X,posY+bg_hover.Y+text_hover.Y);
    }
    return;
  }
  if((iconAlign == button_right)||((iconAlign == text_right)&&(label.getScreenAlign() == ScreenText::right))){
    icon.setScreenPosition(posX+bg_hover.X+bg_hover.Y-icon_hover.W-icon_hover.X,posY+bg_hover.Y+icon_hover.Y);
    if(label.getScreenAlign() == ScreenText::left){
      label.setScreenPosition(posX+bg_hover.X+text_hover.X,posY+bg_hover.Y+text_hover.Y);
    }else if(label.getScreenAlign() == ScreenText::center){
      label.setScreenPosition(posX+bg_hover.X+text_hover.X+(bg_hover.W-icon_hover.X-icon_hover.W)/2,posY+bg_hover.Y+text_hover.Y);
    }else{
      label.setScreenPosition(posX+bg_hover.X+bg_hover.W-text_hover.X-icon_hover.X-icon_hover.W,posY+bg_hover.Y+text_hover.Y);
    }
    return;
  }
  if(iconAlign == text_left){
    if(label.getScreenAlign() == ScreenText::center){
      label.setScreenPosition(posX+bg_hover.X+text_hover.X+(bg_hover.W)/2,posY+bg_hover.Y+text_hover.Y);
      icon.setScreenPosition(posX+bg_hover.X+text_hover.X+icon_hover.X+((bg_hover.W-label.getScreenWidth())/2),posY+bg_hover.Y+icon_hover.Y);
    }else{
      label.setScreenPosition(posX+bg_hover.X+bg_hover.W-text_hover.X,posY+bg_hover.Y+text_hover.Y);
      icon.setScreenPosition(posX+bg_hover.X+bg_hover.W-text_hover.X-label.getScreenWidth(),posY+bg_hover.Y+icon_hover.Y);
    }
    return;
  }
  if(label.getScreenAlign() == ScreenText::center){
    label.setScreenPosition(posX+bg_hover.X+text_hover.X+(bg_hover.W)/2,posY+bg_hover.Y+text_hover.Y);
    icon.setScreenPosition(posX+bg_hover.X+text_hover.X+icon_hover.X+((bg_hover.W+label.getScreenWidth())/2),posY+bg_hover.Y+icon_hover.Y);
  }else{
    label.setScreenPosition(posX+bg_hover.X+text_hover.X,posY+bg_hover.Y+text_hover.Y);
    icon.setScreenPosition(posX+bg_hover.X+text_hover.X+label.getScreenWidth(),posY+bg_hover.Y+icon_hover.Y);
  }
}

void ScreenButtonSimple::propagateIcon(){
  if(!display)
    return;
  icon.setScreenSize(icon_normal.W,icon_normal.H).setResourcePosition(icon_normal_resource.X,icon_normal_resource.Y).setResourceSize(icon_normal_resource.W,icon_normal_resource.H);
  if((iconAlign == button_left)||((iconAlign == text_left)&&(label.getScreenAlign() == ScreenText::left))){
    icon.setScreenPosition(posX+bg_normal.X+icon_normal.X,posY+bg_normal.Y+icon_normal.Y);
    if(label.getScreenAlign() == ScreenText::left){
      label.setScreenPosition(posX+bg_normal.X+icon_normal.X+icon_normal.W+text_normal.X,posY+bg_normal.Y+text_normal.Y);
    }else if(label.getScreenAlign() == ScreenText::center){
      label.setScreenPosition(posX+bg_normal.X+(icon_normal.X+icon_normal.W+text_normal.X+bg_normal.W)/2,posY+bg_normal.Y+text_normal.Y);
    }else{
      label.setScreenPosition(posX+bg_normal.X+bg_normal.W-text_normal.X,posY+bg_normal.Y+text_normal.Y);
    }
    return;
  }
  if((iconAlign == button_right)||((iconAlign == text_right)&&(label.getScreenAlign() == ScreenText::right))){
    icon.setScreenPosition(posX+bg_normal.X+bg_normal.Y-icon_normal.W-icon_normal.X,posY+bg_normal.Y+icon_normal.Y);
    if(label.getScreenAlign() == ScreenText::left){
      label.setScreenPosition(posX+bg_normal.X+text_normal.X,posY+bg_normal.Y+text_normal.Y);
    }else if(label.getScreenAlign() == ScreenText::center){
      label.setScreenPosition(posX+bg_normal.X+text_normal.X+(bg_normal.W-icon_normal.X-icon_normal.W)/2,posY+bg_normal.Y+text_normal.Y);
    }else{
      label.setScreenPosition(posX+bg_normal.X+bg_normal.W-text_normal.X-icon_normal.X-icon_normal.W,posY+bg_normal.Y+text_normal.Y);
    }
    return;
  }
  if(iconAlign == text_left){
    if(label.getScreenAlign() == ScreenText::center){
      label.setScreenPosition(posX+bg_normal.X+text_normal.X+(bg_normal.W)/2,posY+bg_normal.Y+text_normal.Y);
      icon.setScreenPosition(posX+bg_normal.X+text_normal.X+icon_normal.X+((bg_normal.W-label.getScreenWidth())/2),posY+bg_normal.Y+icon_normal.Y);
    }else{
      label.setScreenPosition(posX+bg_normal.X+bg_normal.W-text_normal.X,posY+bg_normal.Y+text_normal.Y);
      icon.setScreenPosition(posX+bg_normal.X+bg_normal.W-text_normal.X-label.getScreenWidth(),posY+bg_normal.Y+icon_normal.Y);
    }
    return;
  }
  if(label.getScreenAlign() == ScreenText::center){
    label.setScreenPosition(posX+bg_normal.X+text_normal.X+(bg_normal.W)/2,posY+bg_normal.Y+text_normal.Y);
    icon.setScreenPosition(posX+bg_normal.X+text_normal.X+icon_normal.X+((bg_normal.W+label.getScreenWidth())/2),posY+bg_normal.Y+icon_normal.Y);
  }else{
    label.setScreenPosition(posX+bg_normal.X+text_normal.X,posY+bg_normal.Y+text_normal.Y);
    icon.setScreenPosition(posX+bg_normal.X+text_normal.X+label.getScreenWidth(),posY+bg_normal.Y+icon_normal.Y);
  }
}

void ScreenButtonSimple::propagateAdjust(){
  if(!display)
    return;
  if(isHover){
    background.setResourcePosition(bg_hover_resource.X,bg_hover_resource.Y).setResourceSize(bg_hover_resource.W,bg_hover_resource.H);
    background.setScreenPosition(posX+bg_hover.X,posY+bg_hover.Y).setScreenSize(bg_hover.W,bg_hover.H);
    label.setColor(hoverText);
    ((ScreenHoverRect*)sHover)->setPosition(posX+bg_hover.X,posY+bg_hover.Y);
    ((ScreenHoverRect*)sHover)->setSize(bg_hover.W,bg_hover.H);
    propagateIconHover();
  }else{
    background.setResourcePosition(bg_normal_resource.X,bg_normal_resource.Y).setResourceSize(bg_normal_resource.W,bg_normal_resource.H);
    background.setScreenPosition(posX+bg_normal.X,posY+bg_normal.Y).setScreenSize(bg_normal.W,bg_normal.H);
    label.setColor(normalText);
    ((ScreenHoverRect*)sHover)->setPosition(posX+bg_normal.X,posY+bg_normal.Y);
    ((ScreenHoverRect*)sHover)->setSize(bg_normal.W,bg_normal.H);
    propagateIcon();
  }
}

void ScreenButtonSimple::propagateScreenSize(){
  if(display)
    propagateAdjust();
}

void ScreenButtonSimple::propagateScreenPosition(){
  if(display)
    propagateAdjust();
}

void ScreenButtonSimple::propagateDisplay(){
  background.setDisplay(display);
  icon.setDisplay(display);
  label.setDisplay(display);
  sHover->setEnabled(display);
  if(display == true){
    CrazyCrush::z_order.addObject(&background,oZOrder);
    CrazyCrush::z_order.addObject(&icon,oZOrder);
    CrazyCrush::z_order.addObject(&label,oZOrder);
    propagateAdjust();
  }else{
    CrazyCrush::z_order.remObject(&background,oZOrder);
    CrazyCrush::z_order.remObject(&icon,oZOrder);
    CrazyCrush::z_order.remObject(&label,oZOrder);
  }
}

void ScreenButtonSimple::setZIndex(int z){
  if(z == oZOrder)
    return;
  oZOrder = z;
}

///   Static Members Start

int ScreenButtonSimple::buttonOffsetY(unsigned char t){
  switch(t){
    default:
    case green:
      return 124;
    case green_light:
      return 156;
    case blue:
      return 188;
    case blue_light:
      return 220;
    case gray:
      return 252;
    case gray_light:
      return 284;
    case red:
      return 316;
    case red_light:
      return 348;
    case 255:
      return 400;
  }
}

int ScreenButtonSimple::buttonOffsetX(unsigned char t){
  switch(t){
    default:
      return 0;
  }
}

int ScreenButtonSimple::defaultScreenWidth(unsigned char t){
  return 156;
}
int ScreenButtonSimple::defaultScreenHeight(unsigned char t){
  return 32;
}

ScreenText& ScreenButtonSimple::getLabelObject(){
  return label;
}