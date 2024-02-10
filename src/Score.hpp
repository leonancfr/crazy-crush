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
#ifndef _SCORE_HPP_
#define _SCORE_HPP_ 1

namespace CrazyCrush {
  //! Espaço reservado para manipulação da pontuação do jogo
  /**
  Cada ponto adicionado é multiplicado por um fator que cresce a cada vez que a pontuação aumenta..
  Mas esse multiplicador também decai após um intervalo
  */
  namespace Score {
    //! Pontuação para cada pedra que for quebrada
    const unsigned char points_per_broke = 10;
    
    //! Inicializa as dependências internas do espaço
    void initialize();
    
    //! Zera o multiplicador interno
    void resetMultiplier();
    
    //! Incrementa a pontuação
    /**
    Deprecated function
    Adiciona value pontos.. Se rand for diferente do rand anterior, o multiplicador é incrementado
    
    No início, cada peça executada essa função uma vez no loop de verificação de 'colisão'. Entretando não é mais necessária, mas foi mantida
    \param rand: Valor aleatório que serve para aumentar o multiplicador
    \param value: Valor a incrementar na pontuação
    */
    void increase(unsigned rand,unsigned value);
    
    //! Incrementa a pontuação
    /**
    \param value: Valor a incrementar na pontuação
    */
    void increase(unsigned value);
    
    //! Função que processa o decaimento do multiplicador
    void trigger();
    
    //! Exibe os elementos do Score na tela
    void show();
    
    //! Oculta os elemento do Score da tela
    void hide();
    
    //! Zera completamente o Score
    void resetAll();
    
    //! Obtém a pontuação atual
    unsigned getScore();
  }
}

#endif