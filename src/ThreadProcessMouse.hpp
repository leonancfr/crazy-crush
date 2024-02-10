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
#ifndef _THREAD_PROCESS_MOUSE_HPP_
#define _THREAD_PROCESS_MOUSE_HPP_ 1

namespace CrazyCrush {
  //! Espaço reservado às Threads
  namespace Thread{
    //! Inicia a thread que processa o mouse
    /**
    \return Se ocorreu com sucesso
    */
    bool startProcessMouse();
    
    //! Pára a thread do mouse
    /**
    É bloqueante
    */
    void stopProcessMouse();
  }
  
  //! Espaço reservado à Thread do Mouse
  namespace ThreadProcessMouse {
    //! Informa a thread do mouse que o mouse se encontra sobre essas coordenadas
    void setCursor(int x,int y);
    
    //! Informa a thread do mouse que o botão direito foi pressionado
    void setClick();
  }
}

#endif