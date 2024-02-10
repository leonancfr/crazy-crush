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
#ifndef _ANIMATOR_OBJECT_HPP_
#define _ANIMATOR_OBJECT_HPP_ 1

#include "Irrlicht/irrTypes.h"
#include "Irrlicht/rect.h"
#include "Irrlicht/SColor.h"

//! Classe abstrata que é base para os elementos da tela
/**
 A thread principal usa apenas os tipos primitivos ScreenObject e ScreenText.
 A grande utilidade dessa classe para as demais classes é o uso delas pela thread de processamento no tempo sem quaisquer outra adaptação.
 
 Observação: Nem todas as funções possuem real funcionalidade em todas as classes.
*/
class AnimatorObject {
  public:
    //! Tipos possíveis para as classes herdadas
    enum { typeScreenObject, typeScreenText, typeScreenButton };
    
    //! Retorna o tipo da classe
    /**
    \return O tipo da classe
    */
    virtual unsigned char getType()=0;
    
    //! Função para processamento no tempo para a classe
    /**
    \param time: O tempo atual para processamento
    */
    virtual void processTime(irr::u32 time)=0;
    
    //! Destrutor da classe
    virtual ~AnimatorObject(){};
    
    //! Função assíncrona para atribuição do display (exibir o objeto)
    /**
    Basicamente irá executar a função interna (setDisplay) da classe.
    Tal função (setDisplay) possui retorno de classe, essa função assíncrona não possui retorno
    \param value: Exibir o objeto
    */
    virtual void aSetDisplay(bool value)=0;
    
    //! Função assíncrona para atribuição do tamanho que o objeto irá ocupar na tela
    /**
    \param width: Largura do objeto
    \param height: Altura do objeto
    */
    virtual void aSetScreenSize(unsigned width,unsigned height)=0;
    
    //! Função assíncrona para atribuição da posição do objeto na tela
    /**
    \param x: Coordenada X
    \param y: Coordenada y
    */
    virtual void aSetScreenPosition(int x,int y)=0;
    
    //! Função assíncrona para definir a cor 
    /**
    \param color: Cor
    */
    virtual void aSetImageColor(irr::video::SColor* color)=0;
    
    //! Função assíncrona para obter a cor
    /**
    \return Objeto de cor
    */
    virtual irr::video::SColor* getColor()=0;
    
    //! Função assíncrona para obter a largura do objeto na tela
    /**
    \return A largura do objeto
    */
    virtual unsigned    getScreenWidth()=0;
    
    //! Função assíncrona para obter a altura do objeto na tela
    /**
    \return A altura do objeto
    */
    virtual unsigned    getScreenHeight()=0;
    
    //! Função assíncrona para obter a coordenada X do objeto na tela
    /**
    \return A coordenada X do objeto
    */
    virtual int         getScreenPositionX()=0;
    
    //! Função assíncrona para obter a coordenada Y do objeto na tela
    /**
    \return A coordenada Y do objeto
    */
    virtual int         getScreenPositionY()=0;
    
    //! Função assíncrona para saber se o elemento está visível na tela
    /**
    \return Se o elemento está visível
    */
    virtual bool        getDisplay()=0;
};

#endif