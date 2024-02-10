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
#ifndef _THREAD_PROCESS_TIME_HPP_
#define _THREAD_PROCESS_TIME_HPP_ 1

#include <pthread.h>

namespace CrazyCrush {
  namespace Thread {
    //! Inicia a thread que processa algumas coisas no tempo
    /**
    \return Se ocorreu com sucesso
    */
    bool startProcessTime();
    
    //! Pára a thread de processamento no tempo
    /**
    É bloqueante
    */
    void stopProcessTime();
  }
}

#endif