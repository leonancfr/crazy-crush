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
#ifndef _PROTECTED_VARIABLE_HPP_
#define _PROTECTED_VARIABLE_HPP_ 1

#include <pthread.h>

//! Classe criada para proteger variaveis entre thread de forma fácil e rápida
/**
Basicamente é uma forma rápida de usar o mutex da pthread
*/
template<typename T>
class Protected {
  private:
    T var;
    pthread_mutex_t access;
  public:
    //! Instancia a classe definindo atribuindo um valor inicial
    /**
    \param value: Valor a ser atribuido
    */
    Protected(T value);
    
    //! Obtém o valor da variável
    T get();
    
    //! Atribui um valor a variável
    /**
    \param value: Valor a ser atribuido
    */
    void set(T value);
};

template<typename T>
Protected<T>::Protected(T v){
  var = v;
  access = PTHREAD_MUTEX_INITIALIZER;
}

template<typename T>
T Protected<T>::get(){
  T t;
  pthread_mutex_lock(&access);
  t = var;
  pthread_mutex_unlock(&access);
  return t;
}

template<typename T>
void Protected<T>::set(T v){
  pthread_mutex_lock(&access);
  var = v;
  pthread_mutex_unlock(&access);
}

#endif