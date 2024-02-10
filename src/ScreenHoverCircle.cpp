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
#include "ScreenHoverCircle.hpp"

ScreenHoverCircle::ScreenHoverCircle(int X,int Y,unsigned R){
  x = X;
  y = Y;
  r = R;
  xmin = X-R;
  ymin = Y-R;
  xmax = X+R;
  ymax = Y+R;
}

void ScreenHoverCircle::setPosition(int X,int Y){
  x = X;
  y = Y;
  xmin = X-r;
  ymin = Y-r;
  xmax = X+r;
  ymax = Y+r;
}

void ScreenHoverCircle::setRadius(unsigned R){
  r = R;
  xmin = x-R;
  ymin = y-R;
  xmax = x+R;
  ymax = y+R;
}

int ScreenHoverCircle::getPositionX(){
  return x;
}

int ScreenHoverCircle::getPositionY(){
  return y;
}

unsigned ScreenHoverCircle::getRadius(){
  return r;
}


bool ScreenHoverCircle::isHover(int X,int Y){
  if((X<xmin)||(X>xmax)||(Y<ymin)||(Y>ymax))
    return false;
  if(( ((unsigned)((X-x)*(X-x)))+((unsigned)((Y-y)*(Y-y)))) <= (r*r))
    return true;
  return false;
}