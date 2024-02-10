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
#include "CallbackProcessMatrix.hpp"
#include "GameDefines.hpp"
#include "Gem.hpp"
#include "MorphLinear.hpp"
#include "CoreProcess.hpp"
#include "Timer.hpp"
#include "Score.hpp"

CallbackProcessMatrix::~CallbackProcessMatrix(){}

CallbackProcessMatrix& CallbackProcessMatrix::setMatrixPositionObj1(unsigned I,unsigned J){
  i1 = I;
  j1 = J;
  return *this;
}

CallbackProcessMatrix& CallbackProcessMatrix::setMatrixPositionObj2(unsigned I,unsigned J){
  i2 = I;
  j2 = J;
  return *this;
}

void CallbackProcessMatrix::aProcess(){
  CrazyCrush::Screen::matrix.at(i1,j1)->setEnabled(true);
  if(!CrazyCrush::Screen::matrix.at(i2,j2)->getEnabled())
    return;
  bool moved = false;
  if(CrazyCrush::core::simpleCheck(i1,j1))
    moved = true;
  if((!moved)&&(CrazyCrush::core::simpleCheck(i2,j2)))
    moved = true;
  if(moved == false){
    CrazyCrush::Score::resetMultiplier();
    MorphLinear* morphObj1 = new MorphLinear();
    MorphLinear* morphObj2 = new MorphLinear();
    morphObj1->setDuration(200).setFinalPosition(CrazyCrush::Screen::convertMatrix2Screen(i2,j2));
    morphObj2->setDuration(200).setFinalPosition(CrazyCrush::Screen::convertMatrix2Screen(i1,j1));
    CrazyCrush::Screen::matrix.at(i1,j1)->appendMorph((ObjectMorph*)morphObj1).startAnimator(getGameTime());
    CrazyCrush::Screen::matrix.at(i2,j2)->appendMorph((ObjectMorph*)morphObj2).startAnimator(getGameTime());
    Gem* swap = CrazyCrush::Screen::matrix.at(i1,j1);
    CrazyCrush::Screen::matrix.at(i1,j1) = CrazyCrush::Screen::matrix.at(i2,j2);
    CrazyCrush::Screen::matrix.at(i2,j2) = swap;
  }else{
    CrazyCrush::core::triggerCheckMatrix.set(true);
    // TODO: Informar para processar (i1,j1) e (i2,j2) em outra thread (de preferencia)
  }
}