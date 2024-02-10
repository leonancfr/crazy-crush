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
#ifndef _SCREEN_BUTTON_SPRITE_HPP_
#define _SCREEN_BUTTON_SPRITE_HPP_ 1

#include "ScreenButton.hpp"
#include "ScreenObject.hpp"

//! Implementação de um botão formado apenas por sprites
class ScreenButtonSprite : public ScreenButton {
  private:
    ScreenObject button;
    int oZOrder;
    int normalX,normalY,hoverX,hoverY;
    unsigned normalW,normalH,hoverW,hoverH;
  public:
    //! Tipos de sprites possíveis
    enum { button_refresh, button_no, button_trash, button_edit, button_close, button_yes, button_right, button_left, button_up, button_down, button_right_white, button_left_white, button_up_white, button_down_white,
           button_refresh_gray, button_no_gray, button_trash_gray, button_edit_gray, button_close_gray, button_yes_gray, button_right_gray, button_left_gray, button_up_gray, button_down_gray };
    ScreenButtonSprite();
    ~ScreenButtonSprite();
    
    //! Define o offset do sprite do botão
    ScreenButtonSprite& setNormalOffset(int x,int y);
    
    //! Define o tamanho do sprite do botão
    ScreenButtonSprite& setNormalSize(unsigned width,unsigned height);
    
    //! Define o offset do sprite do botão no modo hover
    ScreenButtonSprite& setHoverOffset(int x,int y);
    
    //! Define o tamanho do sprite do botão no modo hover
    ScreenButtonSprite& setHoverSize(unsigned width,unsigned height);
    
    //! Obtém o offset X do sprite do botão
    int getNormalOffsetX();
    
    //! Obtém o offset Y do sprite do botão
    int getNormalOffsetY();
    
    //! Obtém a largura do sprite do botão
    unsigned getNormalWidth();
    
    //! Obtém altura do sprite do botão
    unsigned getNormalHeight();
    
    //! Obtém o offset X do sprite do botão no modo hover
    int getHoverOffsetX();
    
    //! Obtém o offset Y do sprite do botão no modo hover
    int getHoverOffsetY();
    
    //! Obtém a largura do sprite do botão no modo hover
    unsigned getHoverWidth();
    
    //! Obtém a altura do sprite do botão no modo hover
    unsigned getHoverHeight();
    
    //! Obtém o offset X do sprite do ícone de um dos tipos enumerados
    static int getOffsetX(unsigned char type);
    
    //! Obtém o offset Y do sprite do ícone de um dos tipos enumerados
    static int getOffsetY(unsigned char type);
    
    //! Obtém a largura do sprite do ícone de um dos tipos enumerados
    static unsigned getWidth(unsigned char type);
    
    //! Obtém a altura do sprite do ícone de um dos tipos enumerados
    static unsigned getHeight(unsigned char type);
    
    void onHover();
    void onOut();
    void propagateScreenSize();
    void propagateScreenPosition();
    void propagateDisplay();
    void setZIndex(int);
};

#endif