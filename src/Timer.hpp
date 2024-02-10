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
#ifndef _GLOBAL_TIMER_HPP_
#define _GLOBAL_TIMER_HPP_ 1

#include "Irrlicht/irrTypes.h"

//! Define o tempo do timer geral
void setTime(irr::u32 time);

//! Obtém o tempo do timer geral sem proteção
/**
Como é uma função usada pela mesma e única thread que executa a função setTimer(), não há problemas
*/
irr::u32 getUnprotectedTime();

//! Obtém o tempo do timer global (com proteção)
irr::u32 getTime();


//! Obtém o tempo do timer de jogo
/**
Enquanto o timer da engine não pára, este timer pára quando a janela do jogo perde foco
*/
irr::u32 getGameTime();

//! Pausa o timer de jogo
void pauseGameTimer();

//! Continua o timer de jogo
void resumeGameTimer();


//! Obtém o tempo do timer do nível
/**
Este timer se baseia no timer do jogo e é usado apenas no nível
*/
irr::u32 getLevelTime();

//! Pausa o timer do nível
void pauseLevelTimer();

//! Continua o timer do nível
void resumeLevelTimer();

//! Reinicia o timer do nível
void resetLevelTimer();

//! Incrementa o timer do nível em n milisegundos
void increaseLevelTimer(unsigned n);

//! Decrementa o timer do nível em n milisegundos
void decreaseLevelTimer(unsigned n);

#endif