/* Universidade Federal do Rio de Janeiro
 * Escola Polit�cnica
 * Departamento de Eletr�nica e Computa��o
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programa��o
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan Fran�a    (leonancfr@poli.ufrj.br)
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