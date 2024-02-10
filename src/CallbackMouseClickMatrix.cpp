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
#include "CallbackMouseClickMatrix.hpp"
#include "GameDefines.hpp"
#include "MorphLinear.hpp"
#include "CallbackProcessMatrix.hpp"
#include "Timer.hpp"

CallbackMouseClickMatrix::CallbackMouseClickMatrix(int I,int J){
  i = I;
  j = J;
}

void CallbackMouseClickMatrix::aProcess(){
  MatrixPosition lPos = CrazyCrush::Screen::getLastBlock();
  if((!CrazyCrush::Screen::matrix.at(i,j)->getEnabled())||
     (!CrazyCrush::Screen::matrix.at(i,j)->getDisplay()))
    return;
  if((i==lPos.i)&&(j==lPos.j)){
    CrazyCrush::Screen::unselectBlock();
    return;
  }
  if((lPos.i!=-1)&&(lPos.j!=-1)){
    CrazyCrush::Screen::matrix.at(lPos.i,lPos.j)->resetSpriteAnimation();
  }
  if(
    ((lPos.i == i)&&((lPos.j == j-1)||(lPos.j == j+1)))||
    ((lPos.j == j)&&((lPos.i == i-1)||(lPos.i == i+1)))
  ){
    CrazyCrush::Screen::matrix.at(lPos.i,lPos.j)->setEnabled(false);
    CrazyCrush::Screen::matrix.at(i,j)->setEnabled(false);
    MorphLinear* morphObj1 = new MorphLinear();
    MorphLinear* morphObj2 = new MorphLinear();
    CallbackProcessMatrix* callObj1 = new CallbackProcessMatrix();
    CallbackProcessMatrix* callObj2 = new CallbackProcessMatrix();
    callObj1->setMatrixPositionObj1(i,j).setMatrixPositionObj2(lPos.i,lPos.j);
    callObj2->setMatrixPositionObj2(i,j).setMatrixPositionObj1(lPos.i,lPos.j);
    morphObj1->setDuration(200).setFinalPosition(CrazyCrush::Screen::convertMatrix2Screen(i,j));
    morphObj2->setDuration(200).setFinalPosition(CrazyCrush::Screen::convertMatrix2Screen(lPos.i,lPos.j));
    Gem* tObject = CrazyCrush::Screen::matrix.at(lPos.i,lPos.j);
    tObject->appendMorph(morphObj1).startAnimator(getGameTime());
    tObject->appendCallback(callObj1);
    CrazyCrush::Screen::matrix.at(i,j)->appendMorph(morphObj2).startAnimator(getGameTime());
    CrazyCrush::Screen::matrix.at(i,j)->appendCallback((Callback*)callObj2);
    CrazyCrush::Screen::matrix.at(lPos.i,lPos.j) = CrazyCrush::Screen::matrix.at(i,j);
    CrazyCrush::Screen::matrix.at(i,j) = tObject;
    CrazyCrush::Screen::unselectBlock();
    return;
  }
  CrazyCrush::Screen::selectBlock(i,j);
}