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
#ifndef _SCREEN_BUTTON_SIMPLE_HPP_
#define _SCREEN_BUTTON_SIMPLE_HPP_ 1

#include "ScreenButton.hpp"
#include "ScreenObject.hpp"
#include "ScreenText.hpp"
#include "Irrlicht/SColor.h"

//! Implemetação de um botão simples com grande controle de seus atributos
class ScreenButtonSimple : public ScreenButton {
  private:
    ScreenObject background;
    ScreenObject icon;
    ScreenText label;
    int oZOrder;
    typedef struct{
      int X,Y;
      unsigned W,H;
    } Coord;
    Coord bg_normal,bg_hover,text_normal,text_hover,icon_normal,icon_hover,bg_normal_resource,bg_hover_resource,icon_normal_resource,icon_hover_resource;
    unsigned char iconAlign;
    irr::video::SColor normalText,hoverText;
    //! Ajusta os componentes internos
    void propagateAdjust();
    
    //! Ajusta o icone no modo normal
    void propagateIcon();
    
    //! Ajusta o icone no modo hover
    void propagateIconHover();
  public:
    //! Tipos de botão e alinhamento do ícone
    enum { red,green,blue,gray,red_light,green_light,blue_light,gray_light, button_left,button_right,text_right,text_left };
  
    ScreenButtonSimple();
    ~ScreenButtonSimple();
    
    //! Define o texto do botão
    ScreenButtonSimple& setLabel(std::string);
    
    //! Define o offset do texto do botão
    ScreenButtonSimple& setLabelOffset(int x,int y);
    
    //! Define o offset do texto do botão no modo hover
    ScreenButtonSimple& setLabelOffsetHover(int x,int y);
    
    //! Define a cor do texto do botão
    ScreenButtonSimple& setLabelColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b);
    
    //! Define a cor do texto do botão no modo hover
    ScreenButtonSimple& setLabelColorHover(unsigned char a,unsigned char r,unsigned char g,unsigned char b);
    
    
    //! Define o offset do ícone do botão
    ScreenButtonSimple& setIconOffset(int x,int y);
    
    //! Define o offset do ícone do botão no modo hover
    ScreenButtonSimple& setIconOffsetHover(int x,int y);
    
    //! Define o tamanho do ícone do botão
    ScreenButtonSimple& setIconSize(unsigned width,unsigned height);
    
    //! Define o tamanho do ícone do botão no modo hover
    ScreenButtonSimple& setIconSizeHover(unsigned width,unsigned height);
    
    //! Define o offset da textura do ícone do botão
    ScreenButtonSimple& setIconResourceOffset(int x,int y);
    
    //! Define o offset da textura do ícone do botão no modo hover
    ScreenButtonSimple& setIconResourceOffsetHover(int x,int y);
    
    //! Define o tamanho da textura do ícone do botão
    ScreenButtonSimple& setIconResourceSize(unsigned width,unsigned height);
    
    //! Define o tamanho da textura do ícone do botão no modo hover
    ScreenButtonSimple& setIconResourceSizeHover(unsigned width,unsigned height);
    
    //! Define a cor do botão
    /**
    \param type: Um dos tipos enumerados
    */
    ScreenButtonSimple& setButtonColor(unsigned char type);
    
    //! Define a cor do botão no modo hover
    /**
    \param type: Um dos tipos enumerados
    */
    ScreenButtonSimple& setButtonColorHover(unsigned char type);
    
    //! Define o offset do botão
    ScreenButtonSimple& setButtonOffset(int x,int y);
    
    //! Define o offset do botão no modo hover
    ScreenButtonSimple& setButtonOffsetHover(int x,int y);
    
    //! Define o tamanho do botão
    ScreenButtonSimple& setButtonSize(unsigned width,unsigned height);
    
    //! Define o tamanho do botão no modo hover
    ScreenButtonSimple& setButtonSizeHover(unsigned width,unsigned height);
    
    
    //! Obtém o objeto do texto do botão
    ScreenText& getLabelObject();
    
    //! Obtém o objeto do ícone do botão
    ScreenObject& getIconObject();
    
    //! Offset X no sprite para uma cor de botão
    static int buttonOffsetX(unsigned char type);
    
    //! Offset Y no sprite para uma cor de botão
    static int buttonOffsetY(unsigned char type);
    
    //! Largura no sprite para uma cor de botão
    static int defaultScreenWidth(unsigned char type);
    
    //! Altura no sprite para uma cor de botão
    static int defaultScreenHeight(unsigned char type);
    
    void onHover();
    void onOut();
    void propagateScreenSize();
    void propagateScreenPosition();
    void propagateDisplay();
    void setZIndex(int);
};

#endif