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
#include "CallbackButtonOnHover.hpp"

CallbackButtonOnHover::CallbackButtonOnHover(ScreenButton* b){
  propagate = NULL;
  btn = b;
}

CallbackButtonOnHover::~CallbackButtonOnHover(){
  if(propagate != NULL)
    delete propagate;
}

void CallbackButtonOnHover::setPropagate(Callback* c){
  if(propagate != NULL)
    delete propagate;
  propagate = c;
}

void CallbackButtonOnHover::aProcess(){
  if(btn != NULL)
    btn->onHover();
  if(propagate != NULL)
    propagate->process();
}