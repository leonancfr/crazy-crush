/* Universidade Federal do Rio de Janeiro
 * Escola Polit�cnica
 * Departamento de Eletr�nica e Computa��o
 * Prof. Fernando Silva
 * EEL 670 - Linguagem de Programa��o
 *
 * Authors: Daniel Dahis     (dahisdaniel@poli.ufrj.br)
 *          Leonan Fran�a    (leonancfr@poli.ufrj.br)
 *          Gustavo Silva    (diguser@gmail.com)
 *          Michael Douglas  (michaeldouglas@poli.ufrj.br)
 */
#include "CallbackGameExitButtonClick.hpp"
#include "MainDraw.hpp"
#include "AudioManager.hpp"

void CallbackGameExitButtonClick::aProcess(){
  CrazyCrush::AudioManager::play("sfx_hit",false,"sfx_hit.ogg");
  CrazyCrush::shutdownGame.set(true);
}