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
#ifndef _ANIMATOR_QUEUE_HPP_
#define _ANIMATOR_QUEUE_HPP_ 1

class AnimatorQueue;

#include <vector>
#include <pthread.h>
#include "Irrlicht/irrTypes.h"
#include "Irrlicht/rect.h"
#include "AnimatorObject.hpp"
#include "ObjectMorph.hpp"
#include "Callback.hpp"

//! Classe que implementa uma fila de animações(no tempo) e callbacks para algum AnimatorObject
/**
Após iniciar o processamento, essa fila primeiro processa todos os ObjectMorph (um após o outro) e, por fim, todos os Callback associados para, então, ser encerrado.
*/
class AnimatorQueue {
  private:
    std::vector<ObjectMorph*> animations;
    std::vector<Callback*> callbacks;
    AnimatorObject* object;
    irr::u32 animationStart;
    irr::u32 actualStep;
    irr::core::rect<irr::s32> screenRect;
    irr::video::SColor* objColor;
    bool isComplete;
    bool skipCallback,isInCallback;
    pthread_mutex_t vectors_mutex;
    
    //! Processa as informações no tempo
    void processStep(irr::u32);
  public:
    AnimatorQueue();
    
    //! Copia os atributos de um outro AnimatorObject para o atual
    /**
    \param queue: O AnimatorQueue a ser clonado
    \return O AnimatorQueue reusultante
    */
    AnimatorQueue& operator=(AnimatorQueue& queue);
    
    //! Atribui o AnimatorQueue a um AnimatorObject
    /**
    Observação: Só é possível associar um único AnimatorObject para cada AnimatorQueue
    \param object: Objeto a associar
    \return Se ocorreu com sucesso
    */
    bool setObject(AnimatorObject* object);
    
    //! Para saber se a classe está processando no tempo
    bool isRunning();
    
    //! Adiciona um ObjectMorph à lista
    /**
    A ordem em que cada ObjectMorph será executado é exatamente igual à ordem em que eles são inseridos na lista.
    Observação: Esse ponteiro será desalocado internamente
    \param morph: Ponteiro para o ObjectMorph a ser adicionado
    \return O objeto atual
    */
    AnimatorQueue& appendMorph(ObjectMorph* morph);
    
    //! Adiciona um Callback à lista
    /**
    A ordem em que cada Callback será executado é exatamente igual à ordem em que eles são inseridos na lista.
    Observação: Esse ponteiro será desalocado internamente
    \param callback: Ponteiro para o Callback a ser adicionado
    \return O objeto atual
    */
    AnimatorQueue& appendCallback(Callback* callback);
    
    //! Inicia a animação no tempo
    /**
    \param time: Tempo de quando se iniciou a animação
    \return O objeto atual
    */
    AnimatorQueue& startAnimation(irr::u32 time);
    
    //! Pára a classe e remove todos os ObjectMorph e Callback
    /**
    \return O objeto atual
    */
    AnimatorQueue& stopAnimation();
    
    //! Processa a posição e tamanho do objeto na tela
    /**
    Internamente chama a função processTime()
    \return A posição processada
    */
    irr::core::rect<irr::s32>   getScreenRect(irr::u32);
    
    //! Processa a cor (máscara) do objeto na tela
    /**
    Internamente chama a função processTime()
    \return A cor processada
    */
    irr::video::SColor*         getImageAlpha(irr::u32);
};

#endif