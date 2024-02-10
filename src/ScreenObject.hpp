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
#ifndef _SCREEN_OBJECT_HPP_
#define _SCREEN_OBJECT_HPP_ 1

class ScreenObject;

#include <pthread.h>
#include "Irrlicht/ITexture.h"
#include "Irrlicht/irrTypes.h"
#include "Irrlicht/rect.h"
#include "Irrlicht/SColor.h"
#include "AnimatorQueue.hpp"
#include "SpriteAnimator.hpp"
#include "ObjectMorph.hpp"
#include "Callback.hpp"
#include "RGBA.hpp"
#include "AnimatorObject.hpp"
#include "SharedPointer.hpp"

//! Objeto primitivo para um Sprite
/**
Esta classe pode ser adicionada ao ZOrder.
É uma das duas classes primitivas de objeto da tela
*/
class ScreenObject : public AnimatorObject {
  private:
    SpriteAnimator* spriteAnimator;
    AnimatorQueue* animatorQueue;
    SharedPointer<irr::video::ITexture> mTexture;
    RGBA mColor;
    RGBA oMColor;
    irr::u32 spriteAnimatorTime;
    unsigned screenWidth,screenHeight;
    int screenPositionX,screenPositionY;
    unsigned resourceWidth,resourceHeight;
    int resourcePositionX,resourcePositionY;
    unsigned oScreenWidth,oScreenHeight;
    int oScreenPositionX,oScreenPositionY;
    unsigned oResourceWidth,oResourceHeight;
    int oResourcePositionX,oResourcePositionY;
    bool mDisplay;
    pthread_mutex_t mutexTexture;
    pthread_mutex_t mutexScreenPosition;
    pthread_mutex_t mutexScreenSize;
    pthread_mutex_t mutexResourcePosition;
    pthread_mutex_t mutexResourceSize;
    pthread_mutex_t mutexDisplay;
    pthread_mutex_t mutexColor;
    pthread_mutex_t mutexOutScreenPosition;
    pthread_mutex_t mutexOutScreenSize;
    pthread_mutex_t mutexOutResourcePosition;
    pthread_mutex_t mutexOutResourceSize;
    pthread_mutex_t mutexOutColor;
  public:
    //! Instancia a classe associando a textura passada pelo ponteiro
    /**
    É a única forma de poder passar NULL
    */
    ScreenObject(SharedPointer<irr::video::ITexture>* texture);
    
    //! Instancia a classe associando a textura informada
    /**
    Esta é a forma mais recomendada
    */
    ScreenObject(SharedPointer<irr::video::ITexture>& texture);
    
    //! Instancia a classe clonando os aspectos de outra instância
    /**
    Aspectos clonados: SpriteAnimator, AnimatorQueue, ITexture, SColor, tamanhos e posições (screen e resource), tempo de início da animação de textura e display
    */
    ScreenObject(ScreenObject& object);
    
    ~ScreenObject();
    
    //! Associa uma textura ao objeto
    /**
    Única forma de permitir o argumento NULL
    */
    ScreenObject& setTexture(SharedPointer<irr::video::ITexture>* texture);
    
    //! Associa uma textura ao objeto
    /**
    Esta é a forma mais recomendada
    */
    ScreenObject& setTexture(SharedPointer<irr::video::ITexture>& texture);
    
    //! Define o SpriteAnimator interno do objeto
    /**
    Este ponteiro NUNCA é deletado internamente
    */
    ScreenObject& setSpriteAnimator(SpriteAnimator* animator);
    
    //! Clona o AnimatorQueue passado por argumento para o AnimatorQueue interno do objeto
    ScreenObject& setAnimatorQueue(AnimatorQueue& animator);
    
    //! Adiciona o ObjectMorph passado por argumento no AnimatorQueue interno
    /**
    Este ponteiro SERÁ deletado internamente
    */
    ScreenObject& appendMorph(ObjectMorph* morph);
    
    //! Adiciona o Callback passado por argumento no AnimatorQueue interno
    /**
    Este ponteiro SERÁ deletado internamente
    */
    ScreenObject& appendCallback(Callback* callback);
    
    //! Define o tamanho que o sprite ocupará na tela
    /**
    \param width: Largura do sprite
    \param height: Altura do sprite
    */
    ScreenObject& setScreenSize(unsigned width,unsigned height);
    
    //! Define a coordenada (x,y) do topo esquerdo do sprite na tela
    ScreenObject& setScreenPosition(int x,int y);
    
    //! Define o tamanho que o sprite usa da textura
    /**
    \param width: Largura do sprite
    \param height: Altura do sprite
    */
    ScreenObject& setResourceSize(unsigned width,unsigned height);
    
    //! Define a coordenada (x,y) do topo esquerdo que o sprite usa da textura
    ScreenObject& setResourcePosition(int x,int y);
    
    //! Define a cor que é usada pela engine para sobrepor o sprite
    ScreenObject& setImageColor(irr::video::SColor* color);
    
    //! Define a transparência da imagem.
    /**
    0 = transparente
    255 = completamente visível
    */
    ScreenObject& setImageAlpha(irr::u8 alpha);
    
    //! Define se o objeto será exibido na tela
    ScreenObject& setDisplay(bool value);
    
    //! Inicia o SpriteAnimator no tempo informado
    ScreenObject& startSpriteAnimation(irr::u32 time);
    
    //! Pára o SpriteAnimator
    ScreenObject& stopSpriteAnimation();
    
    //! Pára o SpriteAnimator e volta os valores de Resource para os valores antigos
    /**
    Os valores que o SpriteAnimator modificam estão separados dos valores definidos pelas funções.
    Quando se dá o reset, os valores de saída será o valor definido.
    */
    ScreenObject& resetSpriteAnimation();
    
    //! Inicia o AnimatorQueue no tempo informado
    ScreenObject& startAnimator(irr::u32 time);
    
    
    void          processTime(irr::u32);
    irr::video::SColor* getColor();
    unsigned getScreenWidth();
    unsigned getScreenHeight();
    int getScreenPositionX();
    int getScreenPositionY();
    bool getDisplay();
    
    //! Retorna a textura usada pelo sprite
    irr::video::ITexture*       getTexture();
    
    //! Retorna o SpriteAnimator do objeto
    SpriteAnimator*             getSpriteAnimator();
    
    //! Retorna o AnimatorQueue do objeto
    AnimatorQueue&              getAnimatorQueue();
    
    //! Obtém o retângulo(posição e tamanho) que o sprite ocupará na tela
    irr::core::rect<irr::s32>   getScreenRect();
    
    //! Obtém o retângulo(posição e tamanho) que o sprite usará da textura
    irr::core::rect<irr::s32>   getResourceRect();
    
    //! Obtém a cor que irá sobrepor a imagem
    /**
    Segundo a engine, se for NULL, a imagem será exibida normalmente
    */
    irr::video::SColor*         getImageColor();
    
    //! Clona os atributos de um ScreenObjeto no objeto atual
    ScreenObject& operator=(ScreenObject& other);
    
    virtual void aSetDisplay(bool);
    void aSetScreenSize(unsigned,unsigned);
    virtual void aSetScreenPosition(int,int);
    void aSetImageColor(irr::video::SColor*);
    unsigned char getType();
};

#endif
