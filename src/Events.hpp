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
#ifndef _EVENTS_HPP_
#define _EVENTS_HPP_ 1

#include "Callback.hpp"

//! Classe para gerenciar eventos básicos dos elementos (botões, por exemplo)
/**
Observação: Todos os ponteiros manipulados por essa classe serão destruídos por ela mesma
*/
class Events {
  private:
    Callback *click,*hover,*show,*close;
  protected:
    void onClick();
    void onHover();
    void onShow();
    void onClose();
  public:
    Events();
    ~Events();
    
    //! Define um Callback para o evento OnClick
    /**
    \param callback: Callback a ser associado
    */
    void setOnClick(Callback* callback);
    
    //! Define um Callback para o evento OnHover
    /**
    \param callback: Callback a ser associado
    */
    void setOnHover(Callback* callback);
    
    //! Define um Callback para o evento OnShow
    /**
    \param callback: Callback a ser associado
    */
    void setOnShow(Callback* callback);
    
    //! Define um Callback para o evento OnClose
    /**
    \param callback: Callback a ser associado
    */
    void setOnClose(Callback* callback);
};

#endif