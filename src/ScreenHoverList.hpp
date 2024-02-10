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
#ifndef _SCREEN_HOVER_LIST_HPP_
#define _SCREEN_HOVER_LIST_HPP_ 1

#include "ScreenHover.hpp"

namespace CrazyCrush {
  //! Espaço reservado à lista de ScreenHover
  namespace ScreenHoverList {
    //! Adiciona um ScreenHover à lista
    /**
    \param hover: Elemento a ser adicionado à lista
    \return Se ocorreu com sucesso
    */
    bool addObject(ScreenHover* hover);
    
    //! Remove um ScreenHover da lista
    /**
    \param hover: Elemento a ser removido da lista
    \param destroy: Informa se o elemento pode ser destruido internamente
    \return Se ocorreu com sucesso
    */
    bool remObject(ScreenHover* hover,bool destroy=false);
    
    //! Executa a função suspend() de todos os ScreenHover da lista
    void suspendAll();
    
    //! Executa a função resume() de todos os ScreenHover da lista
    void resumeAll();
    
    //! Executa o evento OnHover do primeiro ScreenHover da lista que estiver ativo e cuja área delimitada abranje a coordenada (x,y)
    void mouseHover(int x,int y);
    
    //! Executa o evento OnClick do primeiro ScreenHover da lista que estiver ativo e cuja área delimitada abranje a coordenada (x,y)
    void mouseClick(int x,int y);
    
    #ifdef DEBUG
    void debug();
    #endif
  }
}

#endif