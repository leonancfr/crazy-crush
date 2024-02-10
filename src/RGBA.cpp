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
#include "RGBA.hpp"

RGBA::RGBA(){
  color = NULL;
}

RGBA::~RGBA(){
  if(color != NULL)
    delete color;
}

RGBA& RGBA::initColor(){
  color = new irr::video::SColor[4];
  color[0] = irr::video::SColor(255,255,255,255);
  color[1] = irr::video::SColor(255,255,255,255);
  color[2] = irr::video::SColor(255,255,255,255);
  color[3] = irr::video::SColor(255,255,255,255);
  return *this;
}

irr::video::SColor* RGBA::getColor(){
  return color;
}

RGBA& RGBA::setColor(irr::video::SColor* c){
  if(color != NULL)
    delete color;
  color = c;
  return *this;
}

RGBA& RGBA::setAlpha(irr::u8 a){
  if(color == NULL)
    initColor();
  color[0].setAlpha(a);
  color[1].setAlpha(a);
  color[2].setAlpha(a);
  color[3].setAlpha(a);
  return *this;
}

RGBA& RGBA::setRed(irr::u8 r){
  if(color == NULL)
    initColor();
  color[0].setRed(r);
  color[1].setRed(r);
  color[2].setRed(r);
  color[3].setRed(r);
  return *this;
}

RGBA& RGBA::setGreen(irr::u8 g){
  if(color == NULL)
    initColor();
  color[0].setGreen(g);
  color[1].setGreen(g);
  color[2].setGreen(g);
  color[3].setGreen(g);
  return *this;
}

RGBA& RGBA::setBlue(irr::u8 b){
  if(color == NULL)
    initColor();
  color[0].setBlue(b);
  color[1].setBlue(b);
  color[2].setBlue(b);
  color[3].setBlue(b);
  return *this;
}

RGBA& RGBA::setRGB(irr::u8 r,irr::u8 g,irr::u8 b){
  color[0].set(color[0].getAlpha(),r,g,b);
  color[1].set(color[1].getAlpha(),r,g,b);
  color[2].set(color[2].getAlpha(),r,g,b);
  color[3].set(color[3].getAlpha(),r,g,b);
  return *this;
}

RGBA& RGBA::operator=(RGBA& other){
  if(other.color == NULL){
    color = NULL;
  }else{
    color = new irr::video::SColor[4];
    color[0] = other.color[0];
    color[1] = other.color[1];
    color[2] = other.color[2];
    color[3] = other.color[3];
  }
  return *this;
}