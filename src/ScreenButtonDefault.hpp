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
#ifndef _SCREEN_BUTTON_DEFAULT_HPP_
#define _SCREEN_BUTTON_DEFAULT_HPP_ 1

#include "ScreenButton.hpp"
#include "ScreenObject.hpp"
#include "ScreenText.hpp"

//! Implementação de um modelo padrão de botão
/**
A classe é instanciada com os seguintes valores padrões:
altura = 60
largura = 197
label:
alinhamento = centralizado
cor = (255,255,255,255)
*/
class ScreenButtonDefault : public ScreenButton {
  private:
    ScreenObject background;
    ScreenText label;
    int oZOrder;
  public:
    ScreenButtonDefault();
    ~ScreenButtonDefault();
    
    //! Define o texto do botão
    ScreenButtonDefault& setLabel(std::string);
    
    //! Obtém o texto do botão
    std::string getLabel();
    
    void onHover();
    void onOut();
    void propagateScreenSize();
    void propagateScreenPosition();
    void propagateDisplay();
    void setZIndex(int);
};

#endif