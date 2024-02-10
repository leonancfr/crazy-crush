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