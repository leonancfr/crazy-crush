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
#ifndef _MAIN_DRAWN_HPP_
#define _MAIN_DRAWN_HPP_ 1

#include "Irrlicht/IrrlichtDevice.h"
#include "Irrlicht/IVideoDriver.h"
#include "EventReceiver.hpp"
#include "Protected.hpp"
#include <string>

namespace CrazyCrush {
  //! Dispositivo usado pela engine gráfica
  extern irr::IrrlichtDevice* device;
  
  //! Driver usado pela engine gráfica
  extern irr::video::IVideoDriver *driver;
  
  extern MyEventReceiver event;
  
  //! Trigger para encerrar o jogo
  extern Protected<bool> shutdownGame;
  
  //! Trigger para abrir um arquivo que está dentro do arquivo .ZIP usado pela engine gráfica
  extern Protected<bool> externalRead;
  
  //! Função principal que exibe todos elementos do ZOrder na tela
  void draw();
  
  //! Função usada para processar as requisições de leitura de arquivo
  /**
  Esta função só pode ser chamada pela thread que manipula a engine
  */
  void irrlicht_thread_read_file();
  
  //! Lê um arquivo do .ZIP da engine
  /**
  Esta função trava a thread que a chamou, até que a engine leia o arquivo.
  
  NUNCA use essa função na mesma thread da engine.
  \param filename: Nome do arquivo a ser lido
  \param buffer: Ponteiro de saída (deve estar alocado)
  \param length: Bytes a serem lidos do arquivo
  */
  bool readWithWait(std::string filename,char*& buffer,unsigned& length);
}

#endif