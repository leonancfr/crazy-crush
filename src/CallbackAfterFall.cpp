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
#include "CallbackAfterFall.hpp"
#include "AnimationCount.hpp"
#include "CoreProcess.hpp"
#include "Screen.hpp"
#include "GameDefines.hpp"
#include "Timer.hpp"
#include "CallbackFillMatrix.hpp"
#include "MorphTimer.hpp"
#include "GameControl.hpp"

CallbackAfterFall::CallbackAfterFall(unsigned I,unsigned J){
  i = I;
  j = J;
}

void CallbackAfterFall::aProcess(){
  CrazyCrush::Screen::matrix.at(i,j)->setEnabled(true);
  if(CrazyCrush::Screen::AnimationCount::decrease() == 0){
    CrazyCrush::Game::Control::setAllGemsFalled(true);
    if(CrazyCrush::core::checkFullMatrix()){
      if(!CrazyCrush::Game::Control::gameIsRunning())
        return;
      CrazyCrush::core::processFall();
    }else{
      if(!CrazyCrush::Game::Control::gameIsRunning())
        return;
      if(!CrazyCrush::core::checkIfHasMoveLeft()){
        CrazyCrush::Game::Control::setNoMoreMoves(true);
        CrazyCrush::Screen::noMoreMovesObj.setDisplay(true);
        CrazyCrush::Screen::noMoreMovesObj.appendMorph(new MorphTimer(1000));
        CrazyCrush::Screen::noMoreMovesObj.appendCallback(new CallbackFillMatrix());
        CrazyCrush::Screen::noMoreMovesObj.startAnimator(getGameTime());
      }
    }
  }
}