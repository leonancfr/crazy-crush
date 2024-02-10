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
#ifndef _CALLBACK_HPP_
#define _CALLBACK_HPP_

#include <pthread.h>

//! Classe abstrata para evitar o uso de ponteiros de função
class Callback {
  private:
    pthread_mutex_t access;
  public:
    Callback();
    
    //! O destrutor base
    /**
    Esse destrutor trava a classe para evitar que ela seja destruída enquanto ainda está sendo executada
    */
    virtual ~Callback();
    
    //! Função "única" da classe
    /**
    Internamente ela trava a classe e chama a função aProcess()
    */
    void process();
    
    //! Função a ser implementada pelas classes herdadas
    /**
    Recomenda-se não usar essa função diretamente
    */
    virtual void aProcess()=0;
};

#endif