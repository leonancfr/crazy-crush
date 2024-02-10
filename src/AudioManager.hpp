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
#ifndef _AUDIO_MANAGER_HPP_
#define _AUDIO_MANAGER_HPP_ 1

#include "ScreenProgress.hpp"

namespace CrazyCrush {
  //! Espaço reservado ao controlador de áudio
  namespace AudioManager {
    //! Inicializa o audio
    /**
    \return O sucesso da inicialização
    */
    bool initialize();
    
    //! Quantidade de instruções que serão executadas
    unsigned char getTotalProgress();
    
    //! Carrega o áudio base da AudioCache
    /**
    \return Se ocorreu com sucesso
    \param progress: Objeto que imprime o progresso na tela
    */
    bool preLoadAudio(ScreenProgress& progress);
        
    //! Dá play num stream de áudio, se não existir, abre o filename
    /**
    \return Se ocorreu com sucesso
    \param name: Nome associado ao áudio a executar
    \param loop: Se a faixa será tocada em loop
    \param filename: Arquivo a abrir caso o áudio não esteja carregado
    */
    bool play(const char* name,bool loop=false, const char* filename = NULL);
    
    //! Pausa um stream de áudio
    /**
    \return Se ocorreu com sucesso
    \param name: Nome associado ao áudio à pausar
    */
    bool pause(const char* name);
    
    //! Pára um stream de áudio
    /**
    \return Se ocorreu com sucesso
    \param name: Nome associado ao áudio à parar
    */
    bool stop(const char* name);
    
    //! Pára e desaloca um stream de áudio
    /**
    \return Se ocorreu com sucesso
    \param name: Nome associado ao áudio à fechar
    */
    bool close(const char* name);
    
    //! Lê um arquivo de áudio para a memória
    /**
    \return Se ocorreu com sucesso
    \param name: Nome associado ao áudio a abrir
    \param filename: Arquivo a ser aberto
    */
    bool open(const char* name,const char* filename);
    
    //! Define o volume para um determinado stream de áudio
    /**
    \return Se ocorreu com sucesso
    \param name: Nome associado ao áudio
    \param value: Valor entre 0 e 1.
    */
    bool setVolume(const char* name,float value);
    
    //! Obtém o volume para um determinado stream de áudio
    /**
    \return O volume do stream
    \param name: Nome associado ao áudio
    */
    float getVolume(const char* name);
    
    //! Suspende o controlador de áudio
    void suspend();
    
    //! Continua o controlador de áudio
    void resume();
    
    //! Destrói (desaloca) o controlador de áudio
    void destroy();
    
    //! Define o valor global do volume
    /**
    \param value: Volume entre 0 e 1
    */
    void setMasterVolume(float value);
    
    //! Obtém o valor global do volume
    /**
    \return Volume entre 0 e 1
    */
    float getMasterVolume();
  }
}

#endif