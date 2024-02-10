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
#ifndef _SCREEN_BUTTON_CIRCLE_HPP_
#define _SCREEN_BUTTON_CIRCLE_HPP_ 1

#include "ScreenButton.hpp"
#include "ScreenObject.hpp"
#include "ScreenText.hpp"

//! Implementação de um botão circular
/**
A classe é instanciada com os seguintes valores padrões:
Raio = 199
label:
offset = (0,0)
alinhamento = centralizado
cor = (255,255,255,255)
botão:
cor normal = blue
cor hover = blue_light

Observação: O raio do botão é  largura/2
*/
class ScreenButtonCircle : public ScreenButton {
  private:
    ScreenObject background;
    ScreenText label;
    int oZOrder;
    int labelOffsetX,labelOffsetY;
    unsigned char normalColor,hoverColor;
  public:
    //! Possiveis cores que este botão pode ter
    enum { red,orange,green,blue_light,blue };
  
    ScreenButtonCircle();
    ~ScreenButtonCircle();
    
    //! Define o texto que será exibido no botão
    ScreenButtonCircle& setLabel(std::string string);
    
    //! Offset do texto do botão em relação ao centro do botão
    ScreenButtonCircle& setLabelOffset(int x,int y);
    
    //! Define a cor do botão
    ScreenButtonCircle& setButtonColor(unsigned char color);
    
    //! Define a cor do botão quando o mouse estiver sobre o mesmo
    ScreenButtonCircle& setButtonColorHover(unsigned char color);
    
    //! Obtém o texto do botão
    std::string getLabel();
    
    //! Obtém o ScreenText do texto do botão
    ScreenText& getLabelObject();
    
    //! Obtém a cor do botão
    unsigned char getButtonColor();
    
    //! Obtém a cor do botão quando está em OnHover
    unsigned char getButtonColorHover();
    
    //! Obtém o offset no eixo X do texto do botão
    int getLabelOffsetX();
    //! Obtém o offset no eixo Y do texto do botão
    int getLabelOffsetY();
    
    void onHover();
    void onOut();
    void propagateScreenSize();
    void propagateScreenPosition();
    void propagateDisplay();
    void setZIndex(int);
};

#endif