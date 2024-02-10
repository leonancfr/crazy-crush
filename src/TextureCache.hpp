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
#ifndef _TEXTURE_CACHE_HPP_
#define _TEXTURE_CACHE_HPP_ 1

#include "Irrlicht/ITexture.h"
#include "Irrlicht/IGUIFont.h"
#include "ScreenObject.hpp"
#include "SpriteAnimator.hpp"
#include "ScreenProgress.hpp"
#include "SharedPointer.hpp"

namespace CrazyCrush{
  //! Espaço reservado ao cache das texturas usadas
  namespace TextureCache{
    //! Largura básica na tela da pedra
    const unsigned char gemWidth = 30;
    
    //! Altura básica na tela da pedra
    const unsigned char gemHeight = 30;
    
    //! Textura de uma das pedras
    extern SharedPointer<irr::video::ITexture> gem0;
    //! Textura de uma das pedras
    extern SharedPointer<irr::video::ITexture> gem1;
    //! Textura de uma das pedras
    extern SharedPointer<irr::video::ITexture> gem2;
    //! Textura de uma das pedras
    extern SharedPointer<irr::video::ITexture> gem3;
    //! Textura de uma das pedras
    extern SharedPointer<irr::video::ITexture> gem4;
    //! Textura de uma das pedras
    extern SharedPointer<irr::video::ITexture> gem5;
    //! Textura de uma das pedras
    extern SharedPointer<irr::video::ITexture> gem6;
    //! Textura das pedras e do fundo das pontuações
    extern SharedPointer<irr::video::ITexture> rock;
    
    //! Textura da animação da dica na vertical
    extern SharedPointer<irr::video::ITexture> seta_v;
    
    //! Textura da animação da dica na horizontal
    extern SharedPointer<irr::video::ITexture> seta_h;
    
    //! Textura do selecionador
    extern SharedPointer<irr::video::ITexture> selector;
    
    //! Textura do "tabuleiro"
    extern SharedPointer<irr::video::ITexture> stageBackground;
    
    //! Textura do fundo do jogo
    extern SharedPointer<irr::video::ITexture> gameBackground;
    
    //! Textura multi-uso
    extern SharedPointer<irr::video::ITexture> sprites;
    
    //! Textura para alguns botões
    extern SharedPointer<irr::video::ITexture> buttons;
    
    //! Textura dos botões circulares
    extern SharedPointer<irr::video::ITexture> buttons_circle;
    
    //! Uma das fontes
    extern SharedPointer<irr::gui::IGUIFont> font1;
    //! Uma das fontes
    extern SharedPointer<irr::gui::IGUIFont> fontSFComic;
    
    //! Modelo de pedra
    extern ScreenObject ObjectModel;
    
    //! SpriteAnimator das pedras
    extern SpriteAnimator DefaultAnimator;
    
    //! Carrega as definições padrões
    void setDefault();
    
    //! Carrega todas as texturas
    /**
    \param progress: Tela de progresso usada
    \return Se ocorreu com sucesso
    */
    bool loadTextures(ScreenProgress& progress);
    
    //! Obtém o total de texturas (e fontes) a carregar 
    unsigned char getTotalTexturesLoadNumber();
  }
}

#endif
