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
#include "AnimationCount.hpp"

#include <pthread.h>

namespace CrazyCrush {
namespace Screen {
namespace AnimationCount {

unsigned value = 0;
pthread_mutex_t access = PTHREAD_MUTEX_INITIALIZER;

void set(unsigned v){
  pthread_mutex_lock(&access);
  value = v;
  pthread_mutex_unlock(&access);
}

unsigned get(){
  unsigned v;
  pthread_mutex_lock(&access);
  v = value ;
  pthread_mutex_unlock(&access);
  return v;
}

unsigned increase(){
  unsigned r;
  pthread_mutex_lock(&access);
  value++;
  r = value;
  pthread_mutex_unlock(&access);
  return r;
}

unsigned increase(unsigned v){
  unsigned r;
  pthread_mutex_lock(&access);
  value += v;
  r = value;
  pthread_mutex_unlock(&access);
  return r;
}

unsigned decrease(){
  unsigned r = 0;
  pthread_mutex_lock(&access);
  if(value > 0)
    r = --value;
  pthread_mutex_unlock(&access);
  return r;
}

unsigned decrease(unsigned v){
  unsigned r = 0;
  pthread_mutex_lock(&access);
  if(v>value){
    value = 0;
  }else{
    value -= v;
    r = value;
  }
  pthread_mutex_unlock(&access);
  return r;
}

}}}