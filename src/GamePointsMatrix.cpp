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
#include "GamePointsMatrix.hpp"

#include "Matrix.hpp"
#include "GameDefines.hpp"
#include "ScreenObject.hpp"
#include "TextureCache.hpp"
#include "Screen.hpp"
#include "ZOrder.hpp"

namespace CrazyCrush {
namespace Game {
namespace Points {

Matrix<unsigned char> pointsMatrix(Screen::num_rows,Screen::num_columns);
Matrix<ScreenObject*> objPointsMatrix(Screen::num_rows,Screen::num_columns);
Protected<bool> IsComplete(false);

const unsigned offset_green = 86;
const unsigned offset_blue = 172;
const unsigned offset_red = 258;

void initialize(){
  ScreenObject* t;
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      t = new ScreenObject(TextureCache::rock);
      t->setResourceSize(84,84)
        .setResourcePosition(offset_red,0)
        .setScreenSize(TextureCache::gemWidth,TextureCache::gemHeight)
        .setScreenPosition(Screen::stageBackgroundLeft+j*TextureCache::gemWidth,(Screen::stageBackgroundTop+Screen::num_rows*TextureCache::gemHeight)-((i+1)*TextureCache::gemHeight))
        .setDisplay(false);
      pointsMatrix.at(i,j) = 0;
      objPointsMatrix.at(i,j) = t;
      z_order.addObject(t,z_order.index_gems-1);
    }
  }
}

void formatPosition(unsigned i,unsigned j, unsigned char v){
  if(v == 3){
    objPointsMatrix.at(i,j)->setResourcePosition(offset_red,0).setDisplay(true);
  }else if(v==2){
    objPointsMatrix.at(i,j)->setResourcePosition(offset_blue,0).setDisplay(true);
  }else if(v==1){
    objPointsMatrix.at(i,j)->setResourcePosition(offset_green,0).setDisplay(true);
  }else if(v==0){
    objPointsMatrix.at(i,j)->setDisplay(false);
  }
}

void checkMatrix(){
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      if(pointsMatrix.at(i,j)!=0){
        IsComplete.set(false);
        return;
      }
    }
  }
  IsComplete.set(true);
}

void decreasePoint(unsigned i,unsigned j){
  unsigned char v = pointsMatrix.at(i,j);
  if(v == 0)
    return;
  v--;
  pointsMatrix.at(i,j) = v;
  formatPosition(i,j,v);
}

void setPoint(unsigned i,unsigned j,unsigned char v){
  pointsMatrix.at(i,j) = v;
  formatPosition(i,j,v);
  if(v!=0){
    IsComplete.set(false);
  }
}

unsigned char getPoint(unsigned i,unsigned j){
  return pointsMatrix.at(i,j);
}

bool isComplete(){
  return IsComplete.get();
}

void erase(){
  for(unsigned i=0;i<Screen::num_rows;i++){
    for(unsigned j=0;j<Screen::num_columns;j++){
      pointsMatrix.at(i,j) = 0;
      objPointsMatrix.at(i,j)->setDisplay(false);
    }
  }
}

}}}