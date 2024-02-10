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
#ifndef _OBJECT_MORPH_HPP_
#define _OBJECT_MORPH_HPP_ 1

class ObjectMorph;

#include "Irrlicht/irrTypes.h"
#include "Irrlicht/rect.h"
#include "AnimatorObject.hpp"

//! Classe abstrata usada como base para outros tipos de Morph
class ObjectMorph {
  protected:
    AnimatorObject   *obj;
    irr::u32        startTime;
    bool            inRun;
    bool            iComplete;
    virtual void internalTrigger(irr::u32)=0;
  public:
    ObjectMorph();
    virtual ~ObjectMorph();
    //! Associa um objeto a este ObjectMorph
    /**
    \param object: Objeto a associar
    */
    void                                setObject(AnimatorObject* object);
    
    //! Se há algum objeto associado a este ObjectMorph
    bool                                hasObject();
    
    //! Inicia a animação no tempo informado
    /**
    \param time: Tempo de início em milisegundos
    \return Se ocorreu com sucesso
    */
    bool                                start(irr::u32 time);
    
    //! Para a animação
    /**
    \return Se ocorreu com sucesso
    */
    bool                                stop();
    
    //! Se a animação está em execução
    bool                                isRunning();
    
    //! Se a animação está concluída
    bool                                isComplete();
    
    //! Obtém a nova posição e novo tamanho da imagem na tela no tempo informado
    /**
    \param time: Tempo atual em milisegundos
    \return As coordenadas na tela
    */
    virtual irr::core::rect<irr::s32>   getScreenRect(irr::u32 time)=0;
    
    //! Obtém a nova posição e novo tamanho do resource da textura no tempo informado
    /**
    \param time: Tempo atual em milisegundos
    \return As coordenadas no resource
    */
    virtual irr::core::rect<irr::s32>   getResourceRect(irr::u32 time);
    
    //! Obtém a nova cor no tempo informado
    /**
    \param time: Tempo atual em milisegundos
    \return A cor
    */
    virtual irr::video::SColor*         getImageAlpha(irr::u32 time);
    
    //! Clona um ObjectMorph
    /**
    \param morph: Objeto a clonar
    \return O objeto atual
    */
    virtual ObjectMorph& operator=(ObjectMorph& morph);
};

#endif