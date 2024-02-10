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
#include "ScreenHoverRect.hpp"

ScreenHoverRect::ScreenHoverRect(int X,int Y,unsigned W,unsigned H){
  x = X;
  y = Y;
  w = W;
  h = H;
}

void ScreenHoverRect::setPosition(int X,int Y){
  x = X;
  y = Y;
}

void ScreenHoverRect::setSize(unsigned W,unsigned H){
  w=W;
  h=H;
}

int ScreenHoverRect::getPositionX(){
  return x;
}

int ScreenHoverRect::getPositionY(){
  return y;
}

unsigned ScreenHoverRect::getWidth(){
  return w;
}

unsigned ScreenHoverRect::getHeight(){
  return h;
}

bool ScreenHoverRect::isHover(int X,int Y){
  if((X>=x)&&(X<=(int)(x+w))&&(Y>=y)&&(Y<=(int)(y+h)))
    return true;
  return false;
}