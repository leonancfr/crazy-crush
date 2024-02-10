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
#ifndef _CALLBACK_BUTTON_ON_HOVER_HPP_
#define _CALLBACK_BUTTON_ON_HOVER_HPP_ 1

#include "Callback.hpp"
#include "ScreenButton.hpp"

//! Callback para o evento OnHover usado pelos botões na tela
/**
Este callback é responsável por chamar a função interna do botão para modificar sua aparência
*/
class CallbackButtonOnHover : public Callback {
  private:
    Callback *propagate;
    ScreenButton *btn;
  public:
    //! Instancia a classe para um ScreenButton
    /**
    \param button: Botão a ser associado
    */
    CallbackButtonOnHover(ScreenButton* button);
    
    ~CallbackButtonOnHover();
    
    //! Adiciona outro callback a ser executado no evento OnHover
    /**
    Observação: Este ponteiro será excluído internamente
    \param callback: Callback a atribuir
    */
    void setPropagate(Callback* callback);
    void aProcess();
};

#endif