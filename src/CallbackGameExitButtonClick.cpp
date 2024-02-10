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
#include "CallbackGameExitButtonClick.hpp"
#include "MainDraw.hpp"
#include "AudioManager.hpp"

void CallbackGameExitButtonClick::aProcess(){
  CrazyCrush::AudioManager::play("sfx_hit",false,"sfx_hit.ogg");
  CrazyCrush::shutdownGame.set(true);
}