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
#ifndef _EVENT_RECEIVER_HPP_
#define _EVENT_RECEIVER_HPP_ 1

#include "Irrlicht/IEventReceiver.h"
#include <pthread.h>
#include <vector>

//! Classe para tratamento dos eventos (mouse, teclado, joystick) gerados pela engine
class MyEventReceiver : public irr::IEventReceiver {
  private:
    std::vector<bool> KeyIsDown;
    pthread_mutex_t mouse;
    pthread_mutex_t keyboard;
    bool mouseLeftButtonDown;
    unsigned mouseX,mouseY;
  public:
    MyEventReceiver();
    
    //! Função herdada que trata o evento (click do mouse, pressionamento de uma tecla)
    /**
    \param event: Evento
    */
    bool OnEvent(const irr::SEvent& event);
    
    //! Retorna se uma dada tecla está pressionada
    /**
    \param key: Código da tecla pressionada
    \return Se a tecla foi pressionada
    */
    bool IsKeyDown(irr::EKEY_CODE key);
    
    //! Retorna a atual posição do mouse no eixo X
    unsigned getMouseX();
    
    //! Retorna a atual posição do mouse no eixo Y
    unsigned getMouseY();
    
    //! Retorna o estado do botão esquerdo do mouse
    bool mouseLeftButtonPressed();
};

namespace CrazyCrush {
  //! Instância global para o gerenciador de eventos
  extern MyEventReceiver event;
}

#endif