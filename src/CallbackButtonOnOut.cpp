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
#include "CallbackButtonOnOut.hpp"

CallbackButtonOnOut::CallbackButtonOnOut(ScreenButton* b){
  propagate = NULL;
  btn = b;
}

CallbackButtonOnOut::~CallbackButtonOnOut(){
  if(propagate != NULL)
    delete propagate;
}

void CallbackButtonOnOut::setPropagate(Callback* c){
  if(propagate != NULL)
    delete propagate;
  propagate = c;
}

void CallbackButtonOnOut::aProcess(){
  if(btn != NULL)
    btn->onOut();
  if(propagate != NULL)
    propagate->process();
}