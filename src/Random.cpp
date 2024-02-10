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
#include "Random.hpp"

#include <ctime>
#include <cstdlib>

namespace CrazyCrush {
namespace Random {

int lastTime = 0;

const unsigned max = RAND_MAX;

int get(){
  if(lastTime != time(NULL)){
    lastTime = time(NULL);
    srand(lastTime*rand());
  }
  return rand();
}

}}