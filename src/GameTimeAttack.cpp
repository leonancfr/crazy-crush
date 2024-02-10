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
#include "GameTimeAttack.hpp"
#include "GameControl.hpp"
#include "GameDefines.hpp"
#include "GamePointsMatrix.hpp"

namespace CrazyCrush {
namespace Game {
namespace TimeAttack {

void initialize(){
  
}

bool play(){
  if(Game::Control::gameIsRunning())
    return false;
  Game::gameIsTimeAttack = true;
  Game::Control::setLevelTotalTime(120000);
  Game::Points::erase();
  Game::totalGemsEnabled = Game::maxGemExistent;
  for(unsigned j=0;j<Screen::num_columns;j++){
    Game::stageTopPositionStart[j] = 0;
    for(unsigned i=0;i<Screen::num_rows;i++){
      Screen::matrix.at(i,j)->randGem();
    }
  }
  CrazyCrush::Game::Control::gamePlay();
  return true;
}

}}}
    