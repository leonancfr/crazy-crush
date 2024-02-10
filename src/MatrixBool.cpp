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
#include "MatrixBool.hpp"

MatrixBool::MatrixBool(){
  access = PTHREAD_MUTEX_INITIALIZER;
}

MatrixBool::MatrixBool(unsigned i,unsigned j){
  access = PTHREAD_MUTEX_INITIALIZER;
  principal.resize(i,j);
}

MatrixBool& MatrixBool::resize(unsigned i,unsigned j){
  pthread_mutex_lock(&access);
  principal.resize(i,j);
  pthread_mutex_unlock(&access);
  return *this;
}

MatrixBool& MatrixBool::set(unsigned i,unsigned j,bool v){
  pthread_mutex_lock(&access);
  principal.at(i,j) = v;
  pthread_mutex_unlock(&access);
  return *this;
}

bool MatrixBool::get(unsigned i,unsigned j){
  bool t;
  pthread_mutex_lock(&access);
  t = principal.at(i,j);
  pthread_mutex_unlock(&access);
  return t;
}

MatrixBool& MatrixBool::fill(bool v){
  pthread_mutex_lock(&access);
  for(unsigned i=0;i<principal.getLines();i++){
    for(unsigned j=0;j<principal.getColumns();j++){
      principal.at(i,j) = v;
    }
  }
  pthread_mutex_unlock(&access);
  return *this;
}

#ifdef DEBUG
void MatrixBool::debug(){
  pthread_mutex_lock(&access);
  principal.debug();
  pthread_mutex_unlock(&access);
}
#endif