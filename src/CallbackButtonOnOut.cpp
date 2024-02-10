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