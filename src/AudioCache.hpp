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
#ifndef _AUDIO_CACHE_HPP_
#define _AUDIO_CACHE_HPP_ 1

#include "cAudio/IAudioSource.h"
#include "cAudio/IAudioManager.h"
#include "ScreenProgress.hpp"

namespace CrazyCrush {
  //! Espaço reservado ao Cache de Audio
  namespace AudioCache {
    extern cAudio::IAudioSource* sfxPoint;
    extern cAudio::IAudioSource* gameBg;
    
    //! Carrega os arquivos de áudio para cachear (apenas o necessário)
    /**
    \return Se ocorreu com sucesso
    \param progress: Objeto que imprime o progresso na tela
    \param audio: Gerenciador de áudio
    */
    bool initialize(ScreenProgress& progress,cAudio::IAudioManager& audio);
    
    //! Quantidade de arquivos que serão carregados
    /**
    Para ser usado na instância do ScreenObject
    */
    unsigned char getTotalAudioLoadNumber();
  }
}

#endif