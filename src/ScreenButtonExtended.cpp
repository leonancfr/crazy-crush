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
#include "ScreenButtonExtended.hpp"
#include "ScreenHoverRect.hpp"
#include "TextureCache.hpp"
#include "ZOrder.hpp"

const int offset_normal_x = 9;
const int offset_normal_y = 760;
const int offset_hover_x = 9;
const int offset_hover_y = 833;

const unsigned left_width = 105;
const unsigned middle_width = 323;
const unsigned right_width = 109;
const unsigned top_height = 34;
const unsigned middle_height = 15;
const unsigned bottom_height = 24;

ScreenButtonExtended::ScreenButtonExtended():
  bg_top_left(CrazyCrush::TextureCache::sprites),
  bg_top_middle(CrazyCrush::TextureCache::sprites),
  bg_top_right(CrazyCrush::TextureCache::sprites),
  bg_middle_left(CrazyCrush::TextureCache::sprites),
  bg_middle_middle(CrazyCrush::TextureCache::sprites),
  bg_middle_right(CrazyCrush::TextureCache::sprites),
  bg_bottom_left(CrazyCrush::TextureCache::sprites),
  bg_bottom_middle(CrazyCrush::TextureCache::sprites),
  bg_bottom_right(CrazyCrush::TextureCache::sprites),
  label(CrazyCrush::TextureCache::font1),
  subLbl(CrazyCrush::TextureCache::font1),
  txtNormal(255,255,255,255),
  txtHover(255,255,255,255),
  txtSNormal(255,255,255,255),
  txtSHover(255,255,255,255)
{
  oZOrder = -20;
  width = left_width+right_width;
  height = top_height+bottom_height;
  lblOffsetX = width/2;
  lblOffsetY = top_height/2;
  label.setScreenAlign(ScreenText::center).setScreenVAlign(ScreenText::middle);
  
  sHover = new ScreenHoverRect(0,0,width,height);
  sHover->setHoverEvent(oHover);
  sHover->setOutEvent(oOut);
  
  bg_top_left.setResourceSize(left_width,top_height).setResourcePosition(offset_normal_x,offset_normal_y).setDisplay(false).setScreenSize(left_width,top_height);
  bg_top_middle.setResourceSize(middle_width,top_height).setResourcePosition(offset_normal_x+left_width,offset_normal_y).setDisplay(false);
  bg_top_right.setResourceSize(right_width,top_height).setResourcePosition(offset_normal_x+left_width+middle_width,offset_normal_y).setDisplay(false).setScreenSize(right_width,top_height);
  
  bg_middle_left.setResourceSize(left_width,middle_height).setResourcePosition(offset_normal_x,offset_normal_y+top_height).setDisplay(false);
  bg_middle_middle.setResourceSize(middle_width,middle_height).setResourcePosition(offset_normal_x+left_width,offset_normal_y+top_height).setDisplay(false);
  bg_middle_right.setResourceSize(right_width,middle_height).setResourcePosition(offset_normal_x+left_width+middle_width,offset_normal_y+top_height).setDisplay(false);
  
  bg_bottom_left.setResourceSize(left_width,bottom_height).setResourcePosition(offset_normal_x,offset_normal_y+top_height+middle_height).setDisplay(false).setScreenSize(left_width,bottom_height);
  bg_bottom_middle.setResourceSize(middle_width,bottom_height).setResourcePosition(offset_normal_x+left_width,offset_normal_y+top_height+middle_height).setDisplay(false);
  bg_bottom_right.setResourceSize(right_width,bottom_height).setResourcePosition(offset_normal_x+left_width+middle_width,offset_normal_y+top_height+middle_height).setDisplay(false).setScreenSize(right_width,bottom_height);
  
  label.setDisplay(false);
  subLbl.setDisplay(false);
}

ScreenButtonExtended::~ScreenButtonExtended(){

}

///   Label Start

ScreenButtonExtended& ScreenButtonExtended::setLabel(std::string str){
  label.setString(str);
  return *this;
}

ScreenButtonExtended& ScreenButtonExtended::setLabelOffset(int x,int y){
  lblOffsetX = x;
  lblOffsetY = y;
  propagateAdjust();
  return *this;
}

ScreenButtonExtended& ScreenButtonExtended::setLabelColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b){
  txtNormal.set(a,r,g,b);
  return *this;
}

ScreenButtonExtended& ScreenButtonExtended::setLabelColorHover(unsigned char a,unsigned char r,unsigned char g,unsigned char b){
  txtHover.set(a,r,g,b);
  return *this;
}

//\   Label End

///   SubLabel Start

ScreenButtonExtended& ScreenButtonExtended::setSubLabel(std::string str){
  subLbl.setString(str);
  return *this;
}

ScreenButtonExtended& ScreenButtonExtended::setSubLabelOffset(int x,int y){
  slblOffsetX = x;
  slblOffsetY = y;
  propagateAdjust();
  return *this;
}

ScreenButtonExtended& ScreenButtonExtended::setSubLabelColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b){
  txtSNormal.set(a,r,g,b);
  return *this;
}

ScreenButtonExtended& ScreenButtonExtended::setSubLabelColorHover(unsigned char a,unsigned char r,unsigned char g,unsigned char b){
  txtSHover.set(a,r,g,b);
  return *this;
}

//\   SubLabel End

ScreenText& ScreenButtonExtended::getLabelObject(){
  return label;
}

ScreenText& ScreenButtonExtended::getSubLabelObject(){
  return subLbl;
}

void ScreenButtonExtended::onHover(){
  if(isHover)
    return;
  isHover = true;
  propagateAdjust();
}

void ScreenButtonExtended::onOut(){
  if(!isHover)
    return;
  isHover = false;
  propagateAdjust();
}

///   Propagate Functions Start

void ScreenButtonExtended::propagateAdjust(){
 if(!display)
   return;
 int middle_X = posX+left_width;
 int right_X = posX+width-right_width;
 int middle_Y = posY+top_height;
 int bottom_Y = posY+height-bottom_height;
 unsigned middle_H = height-top_height-bottom_height;
 unsigned middle_W = width-left_width-right_width;
 
 ((ScreenHoverRect*)sHover)->setPosition(posX,posY);
 ((ScreenHoverRect*)sHover)->setSize(width,height);
 
 bg_top_left.setScreenPosition(posX,posY);
 bg_top_middle.setScreenPosition(middle_X,posY).setScreenSize(middle_W,top_height);
 bg_top_right.setScreenPosition(right_X,posY);
 
 bg_middle_left.setScreenPosition(posX,middle_Y).setScreenSize(left_width,middle_H);
 bg_middle_middle.setScreenPosition(middle_X,middle_Y).setScreenSize(middle_W,middle_H);
 bg_middle_right.setScreenPosition(right_X,middle_Y).setScreenSize(right_width,middle_H);
 
 bg_bottom_left.setScreenPosition(posX,bottom_Y);
 bg_bottom_middle.setScreenPosition(middle_X,bottom_Y).setScreenSize(middle_W,bottom_height);
 bg_bottom_right.setScreenPosition(right_X,bottom_Y);
 
 label.setScreenPosition(posX+lblOffsetX,posY+lblOffsetY);
 subLbl.setScreenPosition(posX+slblOffsetX,posY+slblOffsetY);
 
 if(isHover){
   label.setColor(txtHover);
   subLbl.setColor(txtSHover);
   
   bg_top_left.setResourcePosition(offset_hover_x,offset_hover_y);
   bg_top_middle.setResourcePosition(offset_hover_x+left_width,offset_hover_y);
   bg_top_right.setResourcePosition(offset_hover_x+left_width+middle_width,offset_hover_y);
   
   bg_middle_left.setResourcePosition(offset_hover_x,offset_hover_y+top_height);
   bg_middle_middle.setResourcePosition(offset_hover_x+left_width,offset_hover_y+top_height);
   bg_middle_right.setResourcePosition(offset_hover_x+left_width+middle_width,offset_hover_y+top_height);
   
   bg_bottom_left.setResourcePosition(offset_hover_x,offset_hover_y+top_height+middle_height);
   bg_bottom_middle.setResourcePosition(offset_hover_x+left_width,offset_hover_y+top_height+middle_height);
   bg_bottom_right.setResourcePosition(offset_hover_x+left_width+middle_width,offset_hover_y+top_height+middle_height);
 }else{
   label.setColor(txtNormal);
   subLbl.setColor(txtSNormal);
   
   bg_top_left.setResourcePosition(offset_normal_x,offset_normal_y);
   bg_top_middle.setResourcePosition(offset_normal_x+left_width,offset_normal_y);
   bg_top_right.setResourcePosition(offset_normal_x+left_width+middle_width,offset_normal_y);
   
   bg_middle_left.setResourcePosition(offset_normal_x,offset_normal_y+top_height);
   bg_middle_middle.setResourcePosition(offset_normal_x+left_width,offset_normal_y+top_height);
   bg_middle_right.setResourcePosition(offset_normal_x+left_width+middle_width,offset_normal_y+top_height);
   
   bg_bottom_left.setResourcePosition(offset_normal_x,offset_normal_y+top_height+middle_height);
   bg_bottom_middle.setResourcePosition(offset_normal_x+left_width,offset_normal_y+top_height+middle_height);
   bg_bottom_right.setResourcePosition(offset_normal_x+left_width+middle_width,offset_normal_y+top_height+middle_height);
 }
  //bg_top_left
}

void ScreenButtonExtended::propagateScreenSize(){
  if(width < left_width+right_width)
    width = left_width+right_width;
  if(height < top_height+bottom_height)
    height = top_height+bottom_height;
  propagateAdjust();
}

void ScreenButtonExtended::propagateScreenPosition(){
  propagateAdjust();
}

void ScreenButtonExtended::propagateDisplay(){
  bg_top_left.setDisplay(display);
  bg_top_middle.setDisplay(display);
  bg_top_right.setDisplay(display);
  bg_middle_left.setDisplay(display);
  bg_middle_middle.setDisplay(display);
  bg_middle_right.setDisplay(display);
  bg_bottom_left.setDisplay(display);
  bg_bottom_middle.setDisplay(display);
  bg_bottom_right.setDisplay(display);
  label.setDisplay(display);
  subLbl.setDisplay(display);
  sHover->setEnabled(display);
  if(display){
    propagateAdjust();
    CrazyCrush::z_order.addObject(&bg_top_left,oZOrder);
    CrazyCrush::z_order.addObject(&bg_top_middle,oZOrder);
    CrazyCrush::z_order.addObject(&bg_top_right,oZOrder);
    CrazyCrush::z_order.addObject(&bg_middle_left,oZOrder);
    CrazyCrush::z_order.addObject(&bg_middle_middle,oZOrder);
    CrazyCrush::z_order.addObject(&bg_middle_right,oZOrder);
    CrazyCrush::z_order.addObject(&bg_bottom_left,oZOrder);
    CrazyCrush::z_order.addObject(&bg_bottom_middle,oZOrder);
    CrazyCrush::z_order.addObject(&bg_bottom_right,oZOrder);
    CrazyCrush::z_order.addObject(&label,oZOrder);
    CrazyCrush::z_order.addObject(&subLbl,oZOrder);
  }else{
    CrazyCrush::z_order.remObject(&bg_top_left,oZOrder);
    CrazyCrush::z_order.remObject(&bg_top_middle,oZOrder);
    CrazyCrush::z_order.remObject(&bg_top_right,oZOrder);
    CrazyCrush::z_order.remObject(&bg_middle_left,oZOrder);
    CrazyCrush::z_order.remObject(&bg_middle_middle,oZOrder);
    CrazyCrush::z_order.remObject(&bg_middle_right,oZOrder);
    CrazyCrush::z_order.remObject(&bg_bottom_left,oZOrder);
    CrazyCrush::z_order.remObject(&bg_bottom_middle,oZOrder);
    CrazyCrush::z_order.remObject(&bg_bottom_right,oZOrder);
    CrazyCrush::z_order.remObject(&label,oZOrder);
    CrazyCrush::z_order.remObject(&subLbl,oZOrder);
  }
}

void ScreenButtonExtended::setZIndex(int z){
  if(oZOrder == z)
    return;
  if(display){
    CrazyCrush::z_order.remObject(&bg_top_left,oZOrder);
    CrazyCrush::z_order.remObject(&bg_top_middle,oZOrder);
    CrazyCrush::z_order.remObject(&bg_top_right,oZOrder);
    CrazyCrush::z_order.remObject(&bg_middle_left,oZOrder);
    CrazyCrush::z_order.remObject(&bg_middle_middle,oZOrder);
    CrazyCrush::z_order.remObject(&bg_middle_right,oZOrder);
    CrazyCrush::z_order.remObject(&bg_bottom_left,oZOrder);
    CrazyCrush::z_order.remObject(&bg_bottom_middle,oZOrder);
    CrazyCrush::z_order.remObject(&bg_bottom_right,oZOrder);
    CrazyCrush::z_order.remObject(&label,oZOrder);
    CrazyCrush::z_order.remObject(&subLbl,oZOrder);
  }
  oZOrder = z;
  if(display){
    CrazyCrush::z_order.addObject(&bg_top_left,oZOrder);
    CrazyCrush::z_order.addObject(&bg_top_middle,oZOrder);
    CrazyCrush::z_order.addObject(&bg_top_right,oZOrder);
    CrazyCrush::z_order.addObject(&bg_middle_left,oZOrder);
    CrazyCrush::z_order.addObject(&bg_middle_middle,oZOrder);
    CrazyCrush::z_order.addObject(&bg_middle_right,oZOrder);
    CrazyCrush::z_order.addObject(&bg_bottom_left,oZOrder);
    CrazyCrush::z_order.addObject(&bg_bottom_middle,oZOrder);
    CrazyCrush::z_order.addObject(&bg_bottom_right,oZOrder);
    CrazyCrush::z_order.addObject(&label,oZOrder);
    CrazyCrush::z_order.addObject(&subLbl,oZOrder);
  }
}