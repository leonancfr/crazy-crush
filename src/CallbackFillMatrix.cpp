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
#include "CallbackFillMatrix.hpp"
#include "Screen.hpp"
#include "CoreProcess.hpp"

void CallbackFillMatrix::aProcess(){
  CrazyCrush::Screen::noMoreMovesObj.setDisplay(false);
  CrazyCrush::core::fillMatrix();
}