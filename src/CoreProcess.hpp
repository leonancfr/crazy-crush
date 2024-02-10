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
#ifndef _CORE_PROCESS_HPP_
#define _CORE_PROCESS_HPP_ 1

#include "Protected.hpp"

namespace CrazyCrush {
  //! Espaço reservado ao processamento do núcleo do jogo
  namespace core {
    //! Verifica se a peça nas coordenadas passadas irá "quebrar"
    /**
    \param i: Coordenada i da peça a ser testada
    \param j: Coordenada j da peça a ser testada
    \return Retorna se há colisão
    */
    bool simpleCheck(unsigned i,unsigned j);
    
    //! Verifica toda a matriz para saber se alguma peça irá "quebrar"
    /**
    \return Retorna se houve alguma colisão
    */
    bool checkFullMatrix();
    
    //! Verifica se há algum movimento possível
    /**
    \return Se há algum movimento possível
    */
    bool checkIfHasMoveLeft();
    
    //! Se houve colisão, processa o caimento das pedras
    /**
    \return Se alguma peça caiu (se moveu)
    */
    bool processFall();
    
    //! Pausa o processamento do jogo
    void pauseGame();
    
    //! Continua o processamento do jogo
    void resumeGame();
    
    //! Preenche toda a matriz de pedras
    void fillMatrix();
    
    //! Trigger para forçar a função de verificação da matriz
    extern Protected<bool> triggerCheckMatrix;
    
    //! Informação de quando foi a última vez que a matriz foi verificada (usado pela função de dicas)
    extern Protected<unsigned> lastFullCheck;
  }
}

#endif