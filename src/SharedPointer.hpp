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
#ifndef _DIG_SHARED_POINTER_HPP_
#define _DIG_SHARED_POINTER_HPP_ 1

#include <vector>
#include <pthread.h>

//! Template para um ponteiro compartilhado
/**
É uma forma de compartilhar o valor de um ponteiro entre outros ponteiros.

Imagine a situação onde tem-se um ponteiro "pai" e diversos "filhos". Se mudarmos o valor do "pai", deseja-se que os "filhos" também tenha seus valores alterados.

Essa classe faz isso
*/
template<typename T>
class SharedPointer {
  private:
    T* value;
    std::vector< SharedPointer<T>* > sharedList;
    SharedPointer<T>* parent;
    bool del;
    pthread_mutex_t access;
    //! Função chamada pelo pai nos filhos na hora de propagar o valor do ponteiro 
    void internalSet(T*);
    
    //! Associa um filho a este
    void append(SharedPointer<T>* pointer);
    
    //! Remove um filho
    void remove(SharedPointer<T>* pointer);
    
    //! Propaga o valor do ponteiro para os filhos
    void propagate();
  public:
    //! Instancia a classe
    /**
    \param destroy: Se definido como true, ao destruir o objeto, o ponteiro interno será desalocado
    */
    SharedPointer(bool destroy= false);
    
    //! Instancia a classe com valor pré-definido
    /**
    \param value: Valor a atribuir
    \param destroy: Se definido como true, ao destruir o objeto, o ponteiro interno será desalocado
    */
    SharedPointer(T* value,bool destroy= false);
    
    ~SharedPointer();
    
    //! Define o valor do ponteiro
    /**
    Caso seja pai, modifica o valor e propaga para os filhos.
    
    Caso seja filho, informa para o pai o novo valor.
    Se o novo valor for NULL, apenas desassocia do pai (e atribui NULL a si mesmo)
    */
    void set(T* value);
    
    //! Retorna o ponteiro interno
    T*   get();
    
    //! Retorna a referência para o conteúdo apontado pelo ponteiro interno
    T&   operator*();
    
    //! Retorna o ponteiro interno
    T*   operator->();
    
    //! Associa o objeto a um objeto pai
    SharedPointer<T>& operator=(SharedPointer<T>& father);
};

template<typename T>
SharedPointer<T>::SharedPointer(bool d){
  parent = NULL;
  value = NULL;
  del = d;
  access = PTHREAD_MUTEX_INITIALIZER;
}

template<typename T>
SharedPointer<T>::SharedPointer(T* v,bool d){
  parent = NULL;
  value = v;
  del = d;
  access = PTHREAD_MUTEX_INITIALIZER;
}

template<typename T>
SharedPointer<T>::~SharedPointer(){
  if(parent != NULL){
    parent->remove(this);
    return;
  }
  if((del)&&(value != NULL))
    delete value;
  value = NULL;
  for(unsigned i=0;i<sharedList.size();i++){
    sharedList[i]->parent = NULL;
    sharedList[i]->value = NULL;
  }
}

template<typename T>
void SharedPointer<T>::set(T* v){
  if(v == NULL){
    if(parent != NULL)
      parent->remove(this);
    parent = NULL;
    pthread_mutex_lock(&access);
    value = NULL;
    pthread_mutex_unlock(&access);
    propagate();
    return;
  }
  if(parent == NULL){
    pthread_mutex_lock(&access);
    if((del)&&(value != NULL))
      delete value;
    value = v;
    pthread_mutex_unlock(&access);
    propagate();
  }else{
    parent->set(v);
  }
}

template<typename T>
T* SharedPointer<T>::get(){
  T* t;
  pthread_mutex_lock(&access);
  t = value;
  pthread_mutex_unlock(&access);
  return t;
}

template<typename T>
T& SharedPointer<T>::operator*(){
  return *value;
}

template<typename T>
T* SharedPointer<T>::operator->(){
  T* t;
  pthread_mutex_lock(&access);
  t = value;
  pthread_mutex_unlock(&access);
  return t;
}

template<typename T>
SharedPointer<T>& SharedPointer<T>::operator=(SharedPointer<T>& n){
  if(parent != NULL)
    parent->remove(this);
  n.append(this);
  return *this;
}

template<typename T>
void SharedPointer<T>::append(SharedPointer<T>* n){
  n->parent = this;
  n->value = value;
  sharedList.push_back(n);
}

template<typename T>
void SharedPointer<T>::remove(SharedPointer<T>* n){
  n->parent = NULL;
  for(unsigned i=0;i<sharedList.size();i++){
    if(sharedList[i] == n){
      sharedList.erase(sharedList.begin()+i);
      break;
    }
  }
}

template<typename T>
void SharedPointer<T>::propagate(){
  for(unsigned i=0;i<sharedList.size();i++){
    sharedList[i]->internalSet(value);
  }
}

template<typename T>
void SharedPointer<T>::internalSet(T* v){
  pthread_mutex_lock(&access);
  value = v;
  pthread_mutex_unlock(&access);
  propagate();
}

#endif