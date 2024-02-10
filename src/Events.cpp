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
#include "Events.hpp"
#include "CallbackDestroy.hpp"
#include <cstdio>

Events::Events(){
  click = NULL;
  hover = NULL;
  show = NULL;
  close = NULL;
}

Events::~Events(){
  if(click != NULL)
    deleteCallback(click);
  if(hover != NULL)
    deleteCallback(hover);
  if(show != NULL)
    deleteCallback(show);
  if(close != NULL)
    deleteCallback(close);
}

void Events::onClick(){
  if(click == NULL)
    return;
  click->process();
}

void Events::onHover(){
  if(hover == NULL)
    return;
  hover->process();
}

void Events::onShow(){
  if(show == NULL)
    return;
  show->process();
}

void Events::onClose(){
  if(close == NULL)
    return;
  close->process();
}

void Events::setOnClick(Callback* c){
  if(click != NULL)
    deleteCallback(click);
  click = c;
}

void Events::setOnHover(Callback* c){
  if(hover != NULL)
    deleteCallback(hover);
  hover = c;
}

void Events::setOnShow(Callback* c){
  if(show != NULL)
    deleteCallback(show);
  show = c;
}

void Events::setOnClose(Callback* c){
  if(close != NULL)
    deleteCallback(close);
  close = c;
}