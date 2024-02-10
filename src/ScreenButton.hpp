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
#ifndef _SCREEN_BUTTON_HPP_
#define _SCREEN_BUTTON_HPP_ 1

#include "AnimatorObject.hpp"
#include "Callback.hpp"
#include "ScreenHover.hpp"

//! Classe abstrata que é modelo para os demais tipos de botões
class ScreenButton : public AnimatorObject {
  protected:
    int posX,posY;
    unsigned width,height;
    bool display,isHover;
    ScreenHover *sHover;
    Callback *oHover;
    Callback *oOut;
  public:
    ScreenButton();
    virtual ~ScreenButton();
    
    //! Define o tamanho que o botão ocupará na tela
    /**
    \param width: Largura do objeto
    \param height: Altura do objeto
    */
    ScreenButton& setScreenSize(unsigned width,unsigned height);
    
    //! Define a posição que o botão ocupará na tela
    /**
    \param x: Posição X na tela
    \param y: Posição Y na tela
    */
    ScreenButton& setScreenPosition(int x,int y);
    
    //! Define se o botão será exibido ou não
    ScreenButton& setDisplay(bool display);
    
    //! Associa um Callback que será executado quando o botão for clicado
    /**
    Este ponteiro será deletado internamente
    */
    ScreenButton& setOnClick(Callback* callback);
    
    //! Associa um Callback que será executado quando o mouse estiver sobre o botão
    /**
    Este ponteiro será deletado internamente
    */
    ScreenButton& setOnHover(Callback* callback);
    
    //! Associa um Callback que será executado quando o mouse sair de cima do botão
    /**
    Este ponteiro será deletado internamente
    */
    ScreenButton& setOnOut(Callback* callback);
    
    //! Suspende o efeito Hover (ver mais em ScreenHover::suspend())
    ScreenButton& suspendHover();
    
    //! Função automaticamente executada quando o mouse estiver sobre a região do botão
    /**
    Permite que cada tipo botão manipule seu evento OnHover da melhor forma
    */
    virtual void onHover()=0;
    
    //! Função automaticamente executada quando o mouse sair de cima do botão
    /**
    Permite que cada tipo botão manipule seu evento OnOut da melhor forma
    */
    virtual void onOut()=0;
    
    //! Função executada sempre que o tamanho do botão for alterado
    virtual void propagateScreenSize()=0;
    
    //! Função executada sempre que a posição do botão for alterado
    virtual void propagateScreenPosition()=0;
    
    //! Função executada sempre que o display do botão for alterado
    virtual void propagateDisplay()=0;
    
    //! Altera o index dos elementos do botão no ZOrder
    /**
    Cada botão possui uma quantidade de elementos diferentes, por isso essa função é virtual
    */
    virtual void setZIndex(int)=0;
    
    unsigned char getType();
    void processTime(irr::u32);
    virtual void aSetDisplay(bool);
    void aSetScreenSize(unsigned,unsigned);
    void aSetScreenPosition(int,int);
    void aSetImageColor(irr::video::SColor*);
    irr::video::SColor* getColor();
    unsigned    getScreenWidth();
    unsigned    getScreenHeight();
    int         getScreenPositionX();
    int         getScreenPositionY();
    bool        getDisplay();
};

#endif