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
#include "Callback.hpp"

Callback::Callback(){
  access = PTHREAD_MUTEX_INITIALIZER;
}

Callback::~Callback(){
  pthread_mutex_lock(&access);
  pthread_mutex_unlock(&access);
}

void Callback::process(){
  pthread_mutex_lock(&access);
  this->aProcess();
  pthread_mutex_unlock(&access);
}