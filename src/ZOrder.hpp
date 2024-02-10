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
#ifndef _MEGA_ZORDER_HPP_
#define _MEGA_ZORDER_HPP_ 1

#include <vector>
#include <pthread.h>
#include "AnimatorObject.hpp"

//! Grande classe problemática que dá ordem com qual os objetos serão exibidos na tela
/**
Como a engine exibe os elementos um sobre o outro na ordem em que são "pedidos para desenhar", essa classe permite que a ordem de objetos adicionados não influenciem tanto na ordem com que os mesmo são exibidos
*/
template<typename T>
class ZOrder {
  private:
    typedef struct{
      int ZIndex;
      int size;
      std::vector<T> content;
    } ZVal;
    std::vector<ZVal> content;
    unsigned aPosPrincipal, aPosInner;
    unsigned insertIndex(int);
    pthread_mutex_t access;
  public:
    ZOrder();
    ~ZOrder();
    
    //! Adiciona um objeto ao índice informado
    /**
    \param object: Objeto a adiconar à lista
    \param index: Índice a ser adicionado
    \return Se ocorreu com sucesso
    */
    bool addObject(T object,int index);
    
    //! Remove o objeto do índice informado
    /**
    \param object: Objeto a remover da lista
    \param index: Índice donde será removido o objeto
    \return Se encontrou e removeu o objeto do índice passado
    */
    bool remObject(T object,int index);
    
    //! Remove o objeto
    /**
    \param object: Objeto a remover da lista
    \return Se encontrou e removeu o objeto em quaisquer índice
    */
    bool remObject(T object);
    
    //! Move o ponteiro de exibição para o início da lista
    void begin();
    
    //! Se há mais algum objeto na lista
    bool hasNext();
    
    //! Retorna o próximo elemento da lista (e move o ponteiro para o próximo elemento)
    T next();
    
    //! Obtém o maior índice usado no momento
    int getTopIndex();

    static const unsigned char index_background = 0;
    static const unsigned char index_stage = index_background+1;
    static const unsigned char index_stagePoints = index_stage+1;
    static const unsigned char index_gems = index_stagePoints+1;
    static const unsigned char index_selectPointer = index_gems+1;
    static const unsigned char index_select = index_selectPointer+1;
    static const unsigned char index_score_bg = index_stage+1;
    static const unsigned char index_score_bar = index_score_bg+1;
    static const unsigned char index_score_bar_divider = index_score_bar+1;
    #ifdef DEBUG
    void debug();
    #endif
};

template<typename T>
unsigned ZOrder<T>::insertIndex(int zIndex){
  ZVal cont;
  cont.ZIndex = zIndex;
  cont.size=0;
  int i = 0;
  content.push_back(cont);
  for(i=(content.size()-1);i>=0;i--){
    if((i!=0)&&(content[i-1].ZIndex > zIndex)){
      content[i] = content[i-1];
    }else{
      content[i] = cont;
      break;
    }
  }
  return i;
}

template<typename T>
ZOrder<T>::ZOrder(){
  aPosPrincipal = 0;
  aPosInner = 0;
  access = PTHREAD_MUTEX_INITIALIZER;
}

template<typename T>
ZOrder<T>::~ZOrder(){}

template<typename T>
bool ZOrder<T>::addObject(T obj,int zIndex){
  unsigned mainIndex = (unsigned)(-1);
  pthread_mutex_lock(&access);
  for(unsigned i=0;i<content.size();i++){
    if(content[i].ZIndex == zIndex){
      mainIndex = i;
      break;
    }
  }
  if(mainIndex != (unsigned)(-1)){
    content[mainIndex].content.push_back(obj);
    content[mainIndex].size++;
    pthread_mutex_unlock(&access);
    return true;
  }
  mainIndex = insertIndex(zIndex);
  if(mainIndex == (unsigned)(-1)){
    pthread_mutex_unlock(&access);
    return false;
  }
  content[mainIndex].content.push_back(obj);
  content[mainIndex].size++;
  pthread_mutex_unlock(&access);
  return true;
}

template<typename T>
bool ZOrder<T>::remObject(T obj,int zIndex){
  bool finded = false;
  pthread_mutex_lock(&access);
  for(unsigned i=0;i<content.size();i++){
    if(content[i].ZIndex == zIndex){
      for(unsigned j=0;j<content[i].content.size();j++){
        if(content[i].content[j] == obj){
          finded = true;
          content[i].content[j] = NULL;
          content[i].size--;
          content[i].content.erase(content[i].content.begin()+j);
          if(content[i].content.size() == 0){
            content.erase(content.begin()+i);
            i--;
            pthread_mutex_unlock(&access);
            return finded;
          }
          j--;
        }
      }
      break;
    }
  }
  pthread_mutex_unlock(&access);
  return finded;
}

template<typename T>
bool ZOrder<T>::remObject(T obj){
  bool finded = false;
  pthread_mutex_lock(&access);
  for(unsigned i=0;i<content.size();i++){
    for(unsigned j=0;j<content[i].content.size();j++){
      if(content[i].content[j] == obj){
        content[i].content[j] = NULL;
        content[i].size--;
        finded = true;
        content[i].content.erase(content[i].content.begin()+j);
        j--;
      }
    }
  }
  pthread_mutex_unlock(&access);
  return finded;
}

template<typename T>
bool ZOrder<T>::hasNext(){
  pthread_mutex_lock(&access);
  if(aPosPrincipal >= content.size()){
    pthread_mutex_unlock(&access);
    return false;
  }
  pthread_mutex_unlock(&access);
  return true;
}

template<typename T>
void ZOrder<T>::begin(){
  aPosPrincipal = 0;
  aPosInner = 0;
  pthread_mutex_lock(&access);
  bool finded = false;
  for(aPosPrincipal=0;aPosPrincipal<content.size();aPosPrincipal++){
    if(content[aPosPrincipal].size == 0)
      continue;
    for(aPosInner=0;aPosInner<content[aPosPrincipal].content.size();aPosInner++){
      if(content[aPosPrincipal].content[aPosInner] != NULL){
        finded = true;
        break;
      }
    }
    if(finded) break;
  }
  pthread_mutex_unlock(&access);
}
template<typename T>
T ZOrder<T>::next(){
  if(!hasNext())
    return NULL;
  unsigned i = aPosPrincipal;
  unsigned j = aPosInner;
  aPosInner++;
  pthread_mutex_lock(&access);
  if(content[i].content.size() <= aPosInner){
    aPosInner = 0;
    aPosPrincipal++;
    bool finded = false;
    for(;aPosPrincipal<content.size();aPosPrincipal++){
      if(content[aPosPrincipal].size == 0)
        continue;
      for(aPosInner=0;aPosInner<content[aPosPrincipal].content.size();aPosInner++){
        if(content[aPosPrincipal].content[aPosInner]!=NULL){
          finded = true;
          break;
        }
      }
      if(finded) break;
    }
  }
  T t = content[i].content[j];
  pthread_mutex_unlock(&access);
  return t;
}

template<typename T>
int ZOrder<T>::getTopIndex(){
  int v = -1000;
  pthread_mutex_lock(&access);
  for(unsigned i=0;i<content.size();i++){
    if(content[i].size == 0)
      continue;
    if(content[i].content.size() != 0){
      for(unsigned j=0;j<content[i].content.size();j++){
        if(content[i].content[j] == NULL)
          continue;
        if(content[i].ZIndex > v)
          v = content[i].ZIndex;
        break;
      }
    }
  }
  pthread_mutex_unlock(&access);
  return v;
}

#ifdef DEBUG
template<typename T>
void ZOrder<T>::debug(){
  /*
  unsigned obj_num = 0;
  pthread_mutex_lock(&access);
  std::cout << "ZOrder:: debug" <<std::endl;
  for(unsigned i=0;i<content.size();i++){
    if(content[i].content.size() != 0){
      obj_num+=content[i].content.size();
      std::cout << content[i].ZIndex << ": ";
      for(unsigned j=0;j<content[i].content.size();j++){
        std::cout << content[i].content[j] << " ";
      }
      std::cout << std::endl;
    }
  }
  std::cout << "ZOrder:: total objects = " << obj_num <<std::endl;
  pthread_mutex_unlock(&access);
  */
}
#endif

namespace CrazyCrush {
  //! Instancia global do ZOrder
  extern ZOrder<AnimatorObject*> z_order;
}

#endif