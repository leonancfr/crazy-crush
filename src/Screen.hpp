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
#ifndef _SCREEN_HPP_
#define _SCREEN_HPP_ 1

#include <vector>
#include "Matrix.hpp"
#include "ScreenObject.hpp"
#include "ScreenHover.hpp"

namespace CrazyCrush {
  namespace Screen {
    //! Coordenada Y do "tabuleiro" do jogo em relação ao topo
    const unsigned stageBackgroundTop = 15;
    
    //! Coordenada X do "tabuleiro" do jogo em relação à lateral esquerda
    const unsigned stageBackgroundLeft = 175;
    
    //! Largura da tela/janela
    const unsigned screenWidth = 640;
    //! Altura da tela/janela
    const unsigned screenHeight = 480;

    //! Matriz dos ScreenHover dos elementos da tela
    extern Matrix<ScreenHover*> matrixHover;
    
    //! ScreenHover da parte de fora do tabuleiro
    extern ScreenHover* outHover;
    
    //! Sprite que aparece quando o mouse está sobre uma pedra
    extern ScreenObject frameSelectorPointer;
    //! Sprite que aparece sobre a pedra quando a mesma está selecionada
    extern ScreenObject frameSelector;
    //! Plano de fundo do "tabuleiro"
    extern ScreenObject stageBackground;
    //! Plano de fundo do jogo
    extern ScreenObject gameBackground;
    //! Sprite do texto de "No More Moves"
    extern ScreenObject noMoreMovesObj;
    //! Sprite da animação de dica de movimento
    extern ScreenObject hintIcon;
    
    //! Inicializa os objetos básicos da tela
    /**
    \return Se ocorreu com sucesso
    */
    bool initializeScreen();
    
    //! Atualize a posição de um objeto na tela com base nas suas coordenadas matricial
    /**
    \param object: Objeto a posicionar
    \param i: Índice i do objeto na matriz
    \param j: Índice j do objeto na matriz
    */
    void updateScreenPosition(ScreenObject& object,unsigned i,unsigned j);
  }
}

#endif