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
#ifndef _SCREEN_TEXT_HPP_
#define _SCREEN_TEXT_HPP_ 1

#include "AnimatorObject.hpp"
#include "AnimatorQueue.hpp"
#include "Irrlicht/IGUIFont.h"
#include "SharedPointer.hpp"
#include <string>
#include <pthread.h>

//! Objeto primitivo para um texto
/**
Esta classe pode ser adicionada ao ZOrder.
É uma das duas classes primitivas de objeto da tela.
*/
class ScreenText : public AnimatorObject {
  private:
    AnimatorQueue* animatorQueue;
    SharedPointer<irr::gui::IGUIFont> font;
    std::string str;
    std::wstring wstr;
    int screenPositionX,screenPositionY;
    bool display;
    int oScreenPositionX,oScreenPositionY;
    irr::video::SColor color;
    unsigned char align;
    unsigned char valign;
    pthread_mutex_t mutexFont;
    pthread_mutex_t mutexString;
    pthread_mutex_t mutexColor;
    pthread_mutex_t mutexScreenPosition;
    pthread_mutex_t mutexOutScreenPosition;
    pthread_mutex_t mutexDisplay;
  public:
    //! Tipos de alinhamento do texto.
    /**
    Os três primeiros são na horizontal e os demais são na vertical. Ambos em relação à coordenada (x,y) definida em setScreenPosition()
    */
    enum {left,right,center,top,middle,bottom};
    
    //! Inicializa o objeto associando uma fonte
    /**
    Método recomendado
    */
    ScreenText(SharedPointer<irr::gui::IGUIFont>& font);
    
    //! Inicializa o objeto associando uma fonte
    /**
    Única forma de definir NULL
    */
    ScreenText(SharedPointer<irr::gui::IGUIFont>* font);
    
    //! Instancia o objeto com os atributos clonados de outro ScreenText
    ScreenText(ScreenText& object);
    
    ~ScreenText();
    
    //! Associa uma fonte ao objeto
    /**
    Método recomendado
    */
    ScreenText& setFont(SharedPointer<irr::gui::IGUIFont>& font);
    
    //! Associa uma fonte ao objeto
    /**
    Única forma de definir NULL
    */
    ScreenText& setFont(SharedPointer<irr::gui::IGUIFont>* font);
    
    //! Define o texto do objeto
    ScreenText& setString(const char* string);
    
    //! Define o texto do objeto
    ScreenText& setString(std::string& string);
    
    //! Define a cor do texto
    ScreenText& setColor(irr::video::SColor& color);
    
    //! Define a cor do texto
    /**
    \param a: Alpha
    \param r: Vermelho
    \param g: Verde
    \param b: Azul
    */
    ScreenText& setColor(unsigned char a,unsigned char r,unsigned char g,unsigned char b);
    
    //! Define a transparência do texto
    ScreenText& setAlpha(unsigned char alpha);
    
    //! Define a posição do texto na tela
    ScreenText& setScreenPosition(int x,int y);
    
    //! Define a orientação horizontal do texto em relação à posição informada
    ScreenText& setScreenAlign(unsigned char type);
    
    //! Define a orientação vertical do texto em relação à posição informada
    ScreenText& setScreenVAlign(unsigned char type);
    
    //! Define se o texto será exibido na tela
    ScreenText& setDisplay(bool value);
    
    //! Clona o AnimatorQueue passado por argumento para o AnimatorQueue interno do objeto
    ScreenText& setAnimatorQueue(AnimatorQueue& animator);
    
    //! Adiciona o ObjectMorph passado por argumento no AnimatorQueue interno
    /**
    Este ponteiro SERÁ deletado internamente
    */
    ScreenText& appendMorph(ObjectMorph* morph);
    
    //! Adiciona o Callback passado por argumento no AnimatorQueue interno
    /**
    Este ponteiro SERÁ deletado internamente
    */
    ScreenText& appendCallback(Callback* callback);
    
    //! Retorna a fonte usada pelo texto
    irr::gui::IGUIFont*       getFont();
    
    //! Retorna o texto do objeto
    std::string               getString();
    
    
    bool                      getDisplay();
    
    //! Obtém o alinhamento horizontal usado no objeto
    unsigned char             getScreenAlign();
    
    //! Obtém o alinhamento vertical usado no objeto
    unsigned char             getScreenVAlign();
    
    //! Obtém a posição do objeto na tela
    irr::core::rect<irr::s32> getScreenRect();
    
    //! Obtém a cor do texto
    irr::video::SColor        getSColor();
    
    void processTime(irr::u32);
    void aSetDisplay(bool);
    void aSetScreenSize(unsigned,unsigned);
    void aSetScreenPosition(int,int);
    void aSetImageColor(irr::video::SColor*);
    irr::video::SColor* getColor();
    unsigned    getScreenWidth();
    unsigned    getScreenHeight();
    int         getScreenPositionX();
    int         getScreenPositionY();
    unsigned char getType();
};

#endif
