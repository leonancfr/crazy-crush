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
#include "CallbackDestroy.hpp"
#include <stack>
#include <pthread.h>

std::stack<Callback*> callbackStack;
pthread_mutex_t access = PTHREAD_MUTEX_INITIALIZER;

void deleteCallback(Callback*& c){
  pthread_mutex_lock(&access);
  callbackStack.push(c);
  c = NULL;
  pthread_mutex_unlock(&access);
}

void realCallbackDestroy(){
  pthread_mutex_lock(&access);
  if(!callbackStack.empty()){
    delete callbackStack.top();
    callbackStack.pop();
  }
  pthread_mutex_unlock(&access);
}