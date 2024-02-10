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
#include "ScreenWindow.hpp"
#include "TextureCache.hpp"
#include "Screen.hpp"
#include "ScreenButton.hpp"
#include "ScreenHoverList.hpp"
#include "ZOrder.hpp"
#include "Logger.hpp"

const unsigned type1_basicSpriteWidth = 596;
const unsigned type1_basicSpriteX = 170;
const unsigned type1_basicSpriteTopY = 51;
const unsigned type1_basicSpriteMiddleY = 162;
const unsigned type1_basicSpriteBottomY = 322;
const unsigned type1_basicMaginLeft = 32;
const unsigned type1_basicMaginRight = 32;
const unsigned type1_basicMaginTop = 80;
const unsigned type1_basicTopHeight = 111;
const unsigned type1_basicMiddleHeight = 160;
const unsigned type1_basicBottomHeight = 62;
const unsigned type1_minimumWindowWidth = type1_basicSpriteWidth;
const unsigned type1_minimumWindowHeight = type1_basicTopHeight+type1_basicBottomHeight;

const unsigned type2_spriteOffsetX = 0;
const unsigned type2_spriteOffsetY = 502;

const unsigned type2_top_left_x = type2_spriteOffsetX+0;
const unsigned type2_top_left_y = type2_spriteOffsetY+0;
const unsigned type2_top_left_width = 8;
const unsigned type2_top_left_height = 8;
const unsigned type2_top_middle_x = type2_top_left_x+type2_top_left_width;
const unsigned type2_top_middle_y = type2_top_left_y;
const unsigned type2_top_middle_width = 488;
const unsigned type2_top_middle_height = type2_top_left_height;
const unsigned type2_top_right_x = type2_top_middle_x+type2_top_middle_width;
const unsigned type2_top_right_y = type2_top_left_y;
const unsigned type2_top_right_width = 8;
const unsigned type2_top_right_height = type2_top_left_height;

const unsigned type2_middle_left_x = type2_top_left_x;
const unsigned type2_middle_left_y = type2_top_left_y+type2_top_left_height;
const unsigned type2_middle_left_width = type2_top_left_width;
const unsigned type2_middle_left_height = 238;
const unsigned type2_middle_middle_x = type2_top_middle_x;
const unsigned type2_middle_middle_y = type2_middle_left_y;
const unsigned type2_middle_middle_width = type2_top_middle_width;
const unsigned type2_middle_middle_height = type2_middle_left_height;
const unsigned type2_middle_right_x = type2_top_right_x;
const unsigned type2_middle_right_y = type2_middle_left_y;
const unsigned type2_middle_right_width = type2_top_right_width;
const unsigned type2_middle_right_height = type2_middle_left_height;

const unsigned type2_bottom_left_x = type2_top_left_x;
const unsigned type2_bottom_left_y = type2_middle_left_y+type2_middle_left_height;
const unsigned type2_bottom_left_width = type2_top_left_width;
const unsigned type2_bottom_left_height = 8;
const unsigned type2_bottom_middle_x = type2_top_middle_x;
const unsigned type2_bottom_middle_y = type2_bottom_left_y;
const unsigned type2_bottom_middle_width = type2_top_middle_width;
const unsigned type2_bottom_middle_height = type2_bottom_left_height;
const unsigned type2_bottom_right_x = type2_top_right_x;
const unsigned type2_bottom_right_y = type2_bottom_left_y;
const unsigned type2_bottom_right_width = type2_top_right_width;
const unsigned type2_bottom_right_height = type2_bottom_left_height;

const unsigned type2_minimumWindowWidth = type2_top_left_width+type2_top_right_width;
const unsigned type2_minimumWindowHeight = type2_top_left_height+type2_bottom_left_height;

ScreenWindow::ScreenWindow() :
  top_left(CrazyCrush::TextureCache::sprites),
  top_middle(CrazyCrush::TextureCache::sprites),
  top_right(CrazyCrush::TextureCache::sprites),
  middle_left(CrazyCrush::TextureCache::sprites),
  middle_middle(CrazyCrush::TextureCache::sprites),
  middle_right(CrazyCrush::TextureCache::sprites),
  bottom_left(CrazyCrush::TextureCache::sprites),
  bottom_middle(CrazyCrush::TextureCache::sprites),
  bottom_right(CrazyCrush::TextureCache::sprites),
  darkBg(CrazyCrush::TextureCache::sprites){
  
  screenType = type_1;
  isOpen = false;
  width = type1_minimumWindowWidth;
  height = type1_minimumWindowHeight;
  posX = (CrazyCrush::Screen::screenWidth-width)/2;
  posY = (CrazyCrush::Screen::screenHeight-height)/2;
  
  top_left.setDisplay(false);
  top_middle.setDisplay(false);
  top_right.setDisplay(false);
  middle_left.setDisplay(false);
  middle_middle.setDisplay(false);
  middle_right.setDisplay(false);
  bottom_left.setDisplay(false);
  bottom_middle.setDisplay(false);
  bottom_right.setDisplay(false);
  
  propagateType();
  propagatePosition();
  
  darkBg.setResourceSize(8,8).setResourcePosition(83,241).setScreenSize(CrazyCrush::Screen::screenWidth,CrazyCrush::Screen::screenHeight).setDisplay(false); // 70%
}

ScreenWindow::~ScreenWindow(){
  this->close();
  for(unsigned i=0;i<objList.size();i++){
    if((objList[i].obj->getType() == AnimatorObject::typeScreenObject)||
       (objList[i].obj->getType() == AnimatorObject::typeScreenText))
      CrazyCrush::z_order.remObject(objList[i].obj);
    delete objList[i].obj;
  }
}

void ScreenWindow::propagateType(){
  if(screenType == type_1){
    top_left.setResourceSize(type1_basicSpriteWidth,type1_basicTopHeight).setResourcePosition(type1_basicSpriteX,type1_basicSpriteTopY);
    middle_left.setResourceSize(type1_basicSpriteWidth,type1_basicMiddleHeight).setResourcePosition(type1_basicSpriteX,type1_basicSpriteMiddleY);
    bottom_left.setResourceSize(type1_basicSpriteWidth,type1_basicBottomHeight).setResourcePosition(type1_basicSpriteX,type1_basicSpriteBottomY);
    top_middle.setDisplay(false);
    top_right.setDisplay(false);
    middle_middle.setDisplay(false);
    middle_right.setDisplay(false);
    bottom_middle.setDisplay(false);
    bottom_right.setDisplay(false);
  }else{
    top_left.setResourcePosition(type2_top_left_x,type2_top_left_y).setResourceSize(type2_top_left_width,type2_top_left_height).setScreenSize(type2_top_left_width,type2_top_left_height);
    top_middle.setResourcePosition(type2_top_middle_x,type2_top_middle_y).setResourceSize(type2_top_middle_width,type2_top_middle_height);
    top_right.setResourcePosition(type2_top_right_x,type2_top_right_y).setResourceSize(type2_top_right_width,type2_top_right_height).setScreenSize(type2_top_right_width,type2_top_right_height);
    
    middle_left.setResourcePosition(type2_middle_left_x,type2_middle_left_y).setResourceSize(type2_middle_left_width,type2_middle_left_height);
    middle_middle.setResourcePosition(type2_middle_middle_x,type2_middle_middle_y).setResourceSize(type2_middle_middle_width,type2_middle_middle_height);
    middle_right.setResourcePosition(type2_middle_right_x,type2_middle_right_y).setResourceSize(type2_middle_right_width,type2_middle_right_height);
    
    bottom_left.setResourcePosition(type2_bottom_left_x,type2_bottom_left_y).setResourceSize(type2_bottom_left_width,type2_bottom_left_height).setScreenSize(type2_bottom_left_width,type2_bottom_left_height);
    bottom_middle.setResourcePosition(type2_bottom_middle_x,type2_bottom_middle_y).setResourceSize(type2_bottom_middle_width,type2_bottom_middle_height);
    bottom_right.setResourcePosition(type2_bottom_right_x,type2_bottom_right_y).setResourceSize(type2_bottom_right_width,type2_bottom_right_height).setScreenSize(type2_bottom_right_width,type2_bottom_right_height);
  }
}

void ScreenWindow::propagatePosition(){
  if(screenType == type_1){
    top_left.setScreenSize(width,type1_basicTopHeight).setScreenPosition(posX,posY);
    middle_left.setScreenSize(width,height-(type1_basicTopHeight+type1_basicBottomHeight)).setScreenPosition(posX,posY+type1_basicTopHeight);
    bottom_left.setScreenSize(width,type1_basicBottomHeight).setScreenPosition(posX,posY+type1_basicTopHeight+middle_left.getScreenHeight());
  }else{
    
    top_left.setScreenPosition(posX,posY);
    top_middle.setScreenPosition(posX+type2_top_left_width,posY)
              .setScreenSize(width-(type2_minimumWindowWidth),type2_top_middle_height);
    top_right.setScreenPosition(posX+type2_top_left_width+top_middle.getScreenWidth(),posY);
    
    middle_left.setScreenPosition(posX,posY+type2_top_left_height)
               .setScreenSize(type2_middle_left_width,height-type2_minimumWindowHeight);
    middle_middle.setScreenPosition(posX+type2_top_left_width,posY+type2_top_left_height)
                 .setScreenSize(width-type2_minimumWindowWidth,height-type2_minimumWindowHeight);
    middle_right.setScreenPosition(posX+type2_top_left_width+middle_middle.getScreenWidth(),posY+type2_top_left_height)
                .setScreenSize(type2_middle_right_width,height-type2_minimumWindowHeight);
    
    bottom_left.setScreenPosition(posX,posY+type2_top_left_height+middle_left.getScreenHeight());
    bottom_middle.setScreenPosition(posX+type2_top_left_width,posY+type2_top_left_height+middle_left.getScreenHeight())
                 .setScreenSize(width-type2_minimumWindowWidth,type2_bottom_middle_height);
    bottom_right.setScreenPosition(posX+type2_top_left_width+top_middle.getScreenWidth(),posY+type2_top_left_height+middle_left.getScreenHeight());
    
  }
}

ScreenWindow& ScreenWindow::setType(unsigned char t){
  if(isOpen)
    return *this;
  if(t!=screenType){
    screenType = t;
    propagateType();
    propagatePosition();
  }
  return *this;
}

ScreenWindow& ScreenWindow::setSize(unsigned w,unsigned h){
  if(screenType == type_1){
    if(w < type1_minimumWindowWidth)
      width = type1_minimumWindowWidth;
    else
      width = w;
    if(h < type1_minimumWindowHeight)
      height = type1_minimumWindowHeight;
    else
      height = h;
  }else{
    if(w < type2_minimumWindowWidth)
      width = type2_minimumWindowWidth;
    else
      width = w;
    if(h < type2_minimumWindowHeight)
      height = type2_minimumWindowHeight;
    else
      height = h;
  }
  propagatePosition();
  return *this;
}

ScreenWindow& ScreenWindow::setPosition(int x,int y){
  int tX,tY;
  for(unsigned i=0;i<objList.size();i++){
    tX = objList[i].obj->getScreenPositionX()-posX+x;
    tY = objList[i].obj->getScreenPositionY()-posY+y;
    objList[i].obj->aSetScreenPosition(tX,tY);
  }
  posX = x;
  posY = y;
  propagatePosition();
  return *this;
}

ScreenWindow& ScreenWindow::show(){
  if(isOpen)
    return *this;
  isOpen = true;
  int topOrder = CrazyCrush::z_order.getTopIndex();
  CrazyCrush::z_order.addObject(&darkBg,++topOrder);
  if(screenType == type_1){
    CrazyCrush::z_order.addObject(&top_left,++topOrder);
    CrazyCrush::z_order.addObject(&middle_left,topOrder);
    CrazyCrush::z_order.addObject(&bottom_left,topOrder);
    top_left.setDisplay(true);
    middle_left.setDisplay(true);
    bottom_left.setDisplay(true);
  }else{
    CrazyCrush::z_order.addObject(&top_left,++topOrder);
    CrazyCrush::z_order.addObject(&top_middle,topOrder);
    CrazyCrush::z_order.addObject(&top_right,topOrder);
    CrazyCrush::z_order.addObject(&middle_left,topOrder);
    CrazyCrush::z_order.addObject(&middle_middle,topOrder);
    CrazyCrush::z_order.addObject(&middle_right,topOrder);
    CrazyCrush::z_order.addObject(&bottom_left,topOrder);
    CrazyCrush::z_order.addObject(&bottom_middle,topOrder);
    CrazyCrush::z_order.addObject(&bottom_right,topOrder);
    top_left.setDisplay(true);
    top_middle.setDisplay(true);
    top_right.setDisplay(true);
    middle_left.setDisplay(true);
    middle_middle.setDisplay(true);
    middle_right.setDisplay(true);
    bottom_left.setDisplay(true);
    bottom_middle.setDisplay(true);
    bottom_right.setDisplay(true);
  }
  darkBg.setDisplay(true);
  onShow();
  CrazyCrush::ScreenHoverList::suspendAll();
  for(unsigned i=0;i<objList.size();i++){
    if(objList[i].lastIndex != topOrder + objList[i].relativeIndex){
      if((objList[i].obj->getType() == AnimatorObject::typeScreenObject)||
         (objList[i].obj->getType() == AnimatorObject::typeScreenText)){
        objList[i].lastIndex = topOrder + objList[i].relativeIndex;
      }else if(objList[i].obj->getType() == AnimatorObject::typeScreenButton){
        objList[i].lastIndex = topOrder + objList[i].relativeIndex;
        ((ScreenButton*)objList[i].obj)->setZIndex(objList[i].lastIndex);
      }
    }
    
    if((objList[i].obj->getType() == AnimatorObject::typeScreenObject)||
       (objList[i].obj->getType() == AnimatorObject::typeScreenText)){
    CrazyCrush::z_order.addObject(objList[i].obj,objList[i].lastIndex);
    }
    
    if(objList[i].visible){
      objList[i].obj->aSetDisplay(true);
    }else{
      objList[i].obj->aSetDisplay(false);
    }
  }
  return *this;
}

ScreenWindow& ScreenWindow::close(){
  if(!isOpen)
    return *this;
  isOpen = false;
  CrazyCrush::z_order.remObject(&darkBg);
  if(screenType == type_1){
    CrazyCrush::z_order.remObject(&top_left);
    CrazyCrush::z_order.remObject(&middle_left);
    CrazyCrush::z_order.remObject(&bottom_left);
  }else{
    CrazyCrush::z_order.remObject(&top_left);
    CrazyCrush::z_order.remObject(&top_middle);
    CrazyCrush::z_order.remObject(&top_right);
    CrazyCrush::z_order.remObject(&middle_left);
    CrazyCrush::z_order.remObject(&middle_middle);
    CrazyCrush::z_order.remObject(&middle_right);
    CrazyCrush::z_order.remObject(&bottom_left);
    CrazyCrush::z_order.remObject(&bottom_middle);
    CrazyCrush::z_order.remObject(&bottom_right);
  }
  darkBg.setDisplay(false);
  onClose();
  CrazyCrush::ScreenHoverList::resumeAll();
  for(unsigned i=0;i<objList.size();i++){
    objList[i].obj->aSetDisplay(false);
    if((objList[i].obj->getType() == AnimatorObject::typeScreenObject)||
       (objList[i].obj->getType() == AnimatorObject::typeScreenText)){
        CrazyCrush::z_order.remObject(objList[i].obj,objList[i].lastIndex);
    }
  }
  return *this;
}

ScreenWindow& ScreenWindow::inject(AnimatorObject* o,int z){
  AAB t;
  t.obj = o;
  t.lastIndex = z;
  t.relativeIndex = z;
  t.visible = true;
  o->aSetDisplay(isOpen);
  o->aSetScreenPosition(o->getScreenPositionX()+posX,o->getScreenPositionY()+posY);
  if((o->getType() == AnimatorObject::typeScreenObject)||
     (o->getType() == AnimatorObject::typeScreenText)){
    CrazyCrush::z_order.addObject(o,z);
  }else if(o->getType() == AnimatorObject::typeScreenButton){
    ((ScreenButton*)o)->setZIndex(z);
  }
  objList.push_back(t);
  return *this;
}

ScreenWindow& ScreenWindow::setVisibility(AnimatorObject* o,bool v){
  for(unsigned i=0;i<objList.size();i++){
    if(objList[i].obj == o){
      if(objList[i].visible != v){
        objList[i].obj->aSetDisplay(v);
        objList[i].visible = v;
      }
      break;
    }
  }
  return *this;
}

int ScreenWindow::getPositionX(){
  return posX;
}

int ScreenWindow::getPositionY(){
  return posY;
}

unsigned ScreenWindow::getWidth(){
  return width;
}

unsigned ScreenWindow::getHeight(){
  return height;
}