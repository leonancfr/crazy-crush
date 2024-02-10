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
#include "CallbackMouseHoverMatrix.hpp"
#include "GameDefines.hpp"
#include "Screen.hpp"

CallbackMouseHoverMatrix::CallbackMouseHoverMatrix(int I,int J){
  i = I;
  j = J;
}

void CallbackMouseHoverMatrix::aProcess(){
  if(!CrazyCrush::Screen::matrix.at(i,j)->getEnabled()){
    CrazyCrush::Screen::frameSelectorPointer.setDisplay(false);
    return;
  }
  irr::core::position2d<irr::s32> t = CrazyCrush::Screen::convertMatrix2Screen(i,j);
  CrazyCrush::Screen::frameSelectorPointer.setScreenPosition(t.X,t.Y).setDisplay(true);
}