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
#ifndef _GAME_LEVEL_FILE_HPP_
#define _GAME_LEVEL_FILE_HPP_ 1

#include <string>
#include "GameDefines.hpp"

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado à leitura dos dados do nível a partir de um arquivo
    namespace LevelFile {
      //! Tamanho do arquivo binário
      /**
      First 1 byte is guarantee of range (can truncate ¬¬')
      First 3 bits = How many gems are available
      Next 32 bits = level time
      Next  4 bits block = Num position is Game::stageTopPositionStart
      Next  3 bits block = first bit is if that gem is fixed, 2-3 bits is the point background value
      */
      const unsigned packetSize = 1+(3 + 32 + 4*Screen::num_columns + Screen::num_columns*Screen::num_rows*3)/8;
      
      //! Abre um nível de forma binária
      /**
      A estrutura usada é a supracitada
      \return Se ocorreu com sucesso
      \param filename: Nome do arquivo a abrir
      \param engine: Usar um arquivo que está dentro do arquivo que a engine está usando
      */
      bool openLevel(std::string filename,bool engine=true);
      
      //! Abre um nível da forma texto
      /**
      \return Se ocorreu com sucesso
      \param filename: Nome do arquivo a abrir
      \param engine: Usar um arquivo que está dentro do arquivo que a engine está usando
      */
      bool openLevelText(std::string filename,bool engine=true);
      
      //! Salva a fase atual num arquivo binário
      /**
      Usa a mesma estrutura binária da de abertura.
      É útil para converter uma estrutura em texto para a estrutura binária
      \return Se ocorreu com sucesso
      \param filename: Nome do arquivo a salvar
      */
      bool saveLevel(std::string filename);
      #ifdef DEBUG
      void debug();
      #endif
    }
  }
}

#endif