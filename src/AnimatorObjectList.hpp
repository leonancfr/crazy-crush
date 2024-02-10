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
#ifndef _ANIMATOR_OBJECT_LIST_HPP_
#define _ANIMATOR_OBJECT_LIST_HPP_ 1

#include "AnimatorObject.hpp"
#include <vector>
#include <pthread.h>

//! Lista dos AnimatorObject que serão processados no tempo
/**
A classe não permite acesso direto aos seus elementos, ela mesma os manipula de forma conveniente
*/
class AnimatorObjList {
  private:
    std::vector<AnimatorObject*> content;
    unsigned pointer;
    pthread_mutex_t access;
  public:
    //! Construtor
    AnimatorObjList();
    
    //! Destrutor
    ~AnimatorObjList();
    
    //! Adiciona um elemento à lista
    /**
    \param object: AnimatorObject a ser adicionado na lista
    \return Se a operação ocorreu com sucesso
    */
    bool addObject(AnimatorObject* object);
    
    //! Remove um elemento da lista
    /**
    \param object: AnimatorObject a ser removido da lista
    \return Se a operação ocorreu com sucesso
    */
    bool remObject(AnimatorObject*);
    
    //! Move o ponteiro de amostragem para o início
    void begin();
    
    //! Retorna o próximo elemento da lista ou NULL caso chegue ao final
    /**
    \return O objeto a ser processado ou NULL
    */
    AnimatorObject* next();
};

namespace CrazyCrush {
  //! Instância global da lista de objetos a serem processados no tempo
  extern AnimatorObjList AnimatorObjectList;
}

#endif