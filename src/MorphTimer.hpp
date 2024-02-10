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
#ifndef _MORPH_TIMER_HPP_
#define _MORPH_TIMER_HPP_ 1

#include "ObjectMorph.hpp"

//! Classe que funciona apenas como um timer
/**
Muito útil para agendar e concatenar Callbacks ou outros movimentos
*/
class MorphTimer : public ObjectMorph {
  private:
    irr::u32 duration;
    void internalTrigger(irr::u32);
  public:
    //! Instacia a classe definindo o tempo de duração
    /**
    \param duration: Duração em milisegundos
    */
    MorphTimer(irr::u32 duration);
    
    //! Define a duração do evento
    /**
    \param duration: Duração em milisegundos
    \return O objeto
    */
    MorphTimer& setDuration(irr::u32);
    
    irr::core::rect<irr::s32> getScreenRect(irr::u32);
};

#endif