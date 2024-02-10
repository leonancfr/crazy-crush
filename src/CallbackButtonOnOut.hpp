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
#ifndef _CALLBACK_BUTTON_ON_OUT_HPP_
#define _CALLBACK_BUTTON_ON_OUT_HPP_ 1

#include "Callback.hpp"
#include "ScreenButton.hpp"

//! Callback para quando o mouse sai de cima do botão
class CallbackButtonOnOut : public Callback {
  private:
    Callback *propagate;
    ScreenButton *btn;
  public:
    //! Instancia a classe para um ScreenButton
    /**
    \param button: Botão a ser associado
    */
    CallbackButtonOnOut(ScreenButton* button);
    
    ~CallbackButtonOnOut();
    
    //! Adiciona outro callback a ser executado no evento OnOut
    /**
    Observação: Este ponteiro será excluído internamente
    \param callback: Callback a atribuir
    */
    void setPropagate(Callback*);
    void aProcess();
};

#endif