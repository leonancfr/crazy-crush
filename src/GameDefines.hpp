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
#ifndef _GAME_DEFINES_HPP_
#define _GAME_DEFINES_HPP_ 1

#include "Matrix.hpp"
#include "Gem.hpp"
#include "Percentage.hpp"

namespace CrazyCrush {
  namespace Game {
    //! Total de pedras permitido no jogo atual
    extern unsigned char totalGemsEnabled;
    
    //! Probabilidade de uma pedra vir com bônus de tempo (não implementado ainda)
    extern Percentage::HPercent timeBonusGemProbability;
    
    //! Vetor com as posições das quais as pedras começam a cair
    extern std::vector<unsigned> stageTopPositionStart;
    
    //! Se o jogo é do tipo TimeAttack
    extern bool gameIsTimeAttack;
    
    //! Total de pedras que o jogo pode ter
    extern const unsigned char maxGemExistent;
    
    //! Inicializador das dependências
    void initialize();
  }
  namespace Screen {
    
    //! Número de linhas na matriz.
    /**
    Também corresponde a quantidade de pedras em cada coluna
    */
    const unsigned char num_rows = 15;
    
    //! Número de colunas da matriz
    /**
    Também corresponde a quantidade de pedras em cada linha
    */
    const unsigned char num_columns = 15;
    
    //! Velocidade de queda de cada pedra
    const float fall_velocity = 0.2;
    
    //! Matriz de pedras
    extern Matrix<Gem*> matrix;
    
    //! Converte uma posição na tela para um índice da matriz
    /**
    Obs.: i = -1 e j = -1 são retornados quando a região delimitada por X e Y estão fora da matriz
    \param x: Posição X na tela
    \param y: Posição Y na tela
    \return Uma estrutura com os índices I e J na matriz
    */
    MatrixPosition convertScreen2Matrix(irr::u16 x,irr::u16 y);
    
    //! Converte um índice da matriz para uma posição na tela
    /**
    \param i: Índice i da matriz
    \param j: Índice j da matriz
    \return Uma estrutura com as coordenadas X e Y na tela
    */
    irr::core::position2d<irr::s32> convertMatrix2Screen(unsigned i,unsigned j);
    
    //! Obtém os índices referente ao último bloco selecionado
    /**
    Obs.: i = -1 e j = -1 são retornados quando não há nenhum elemento selecionado
    \return: Estrutura com os índices. 
    */
    MatrixPosition getLastBlock();
    
    //! Desseleciona quaisquer bloco que esteja selecionado
    void unselectBlock();
    
    //! Desseleciona o bloco da coordenada passada
    /**
    \param i: Índice i da matriz
    \param j: Índice j da matriz
    */
    void unselectBlock(unsigned i,unsigned j);
    
    //! Seleciona o bloco da coordenada passada
    /**
    \param i: Índice i da matriz
    \param j: Índice j da matriz
    */
    void selectBlock(unsigned i,unsigned j);
  }
}

#endif