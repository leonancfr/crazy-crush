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
#ifndef _SCREEN_BUTTON_EXTENDED_HPP_
#define _SCREEN_BUTTON_EXTENDED_HPP_ 1

#include "ScreenButton.hpp"
#include "ScreenObject.hpp"
#include "ScreenText.hpp"
#include "Irrlicht/SColor.h"
#include <vector>

//! Implementação de um botão com suporte a dois labels (vide botão de seleção de nível)
/**
A classe é instanciada com os seguintes valores padrões:
altura = 58
largura = 214

label:
offset = (107,17)
alinhamento = centralizado
alinhamento vertical = centralizado
cor = (255,255,255,255)
cor hover = (255,255,255,255)
*/
class ScreenButtonExtended : public ScreenButton {
  private:
    ScreenObject bg_top_left,bg_top_middle,bg_top_right;
    ScreenObject bg_middle_left,bg_middle_middle,bg_middle_right;
    ScreenObject bg_bottom_left,bg_bottom_middle,bg_bottom_right;
    ScreenText label;
    ScreenText subLbl;
    int oZOrder;
    int lblOffsetX,lblOffsetY,slblOffsetX,slblOffsetY;
    irr::video::SColor txtNormal, txtHover;
    irr::video::SColor txtSNormal, txtSHover;
    void propagateAdjust();
  public:
  
    ScreenButtonExtended();
    ~ScreenButtonExtended();
    
    //! Define o texto principal do botão
    /**
    \param string: String que será o texto do botão
    */
    ScreenButtonExtended& setLabel(std::string string);
    
    //! Define o offset do texto principal em relação ao canto superior esquerdo do botão
    /**
    \param x: Offset no eixo X
    \param y: Offset no eixo Y
    */
    ScreenButtonExtended& setLabelOffset(int x,int y);
    
    //! Define a cor do texto principal normal
    /**
    \param a: Alpha
    \param r: Vermelho
    \param g: Verde
    \param b: Azul
    */
    ScreenButtonExtended& setLabelColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b);
    
    //! Define a cor do texto principal quando o mouse estiver sobre o botão
    /**
    \param a: Alpha
    \param r: Vermelho
    \param g: Verde
    \param b: Azul
    */
    ScreenButtonExtended& setLabelColorHover(unsigned char a,unsigned char r,unsigned char g,unsigned char b);
    
    //! Define o texto secundário do botão
    /**
    \param string: String que será o texto do botão
    */
    ScreenButtonExtended& setSubLabel(std::string string);
    
    //! Define o offset do texto secundário em relação ao canto superior esquerdo do botão
    /**
    \param x: Offset no eixo X
    \param y: Offset no eixo Y
    */
    ScreenButtonExtended& setSubLabelOffset(int x,int y);
    
    //! Define a cor do texto secundário normal
    /**
    \param a: Alpha
    \param r: Vermelho
    \param g: Verde
    \param b: Azul
    */
    ScreenButtonExtended& setSubLabelColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b);
    
    //! Define a cor do texto secundário quando o mouse estiver sobre o botão
    /**
    \param a: Alpha
    \param r: Vermelho
    \param g: Verde
    \param b: Azul
    */
    ScreenButtonExtended& setSubLabelColorHover(unsigned char a,unsigned char r,unsigned char g,unsigned char b);
    
    ScreenText& getLabelObject();
    ScreenText& getSubLabelObject();
    
    void onHover();
    void onOut();
    void propagateScreenSize();
    void propagateScreenPosition();
    void propagateDisplay();
    void setZIndex(int);
};

#endif