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
#ifndef _CALLBACK_DESTROY_HPP_
#define _CALLBACK_DESTROY_HPP_ 1

#include "Callback.hpp"

//! Agenda um Callback para ser deletado
/**
Passando o ponteiro por referência, o ponteiro original terá seu valor alterado
\param callback: Callback a ser deletado
*/
void deleteCallback(Callback*& callback);

//! Deleta cada Callback agendado para ser deletado
/**
Recomenda-se o uso desta função fora de quaisquer callback
*/
void realCallbackDestroy();

#endif