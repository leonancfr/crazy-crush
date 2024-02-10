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
#ifndef _GAME_SAVE_HPP_
#define _GAME_SAVE_HPP_ 1

namespace CrazyCrush {
  namespace Game {
    //! Espaço reservado às operações que salvam as pontuações do jogador
    namespace Save {
      //! Quantidade posições possíveis para o rank do modo TimeAttack
      const extern unsigned maxRankTimeAttack;
      
      //! Inicializa as dependências internas do espaço
      void initialize();
      
      //! Obtém o record do nível desejado
      /**
      \param level: Nível a saber o record
      \return O record
      */
      unsigned getLevelPoints(unsigned level);
      
      //! Obtém o record número um do modo TimeAttack
      /**
      \return O record
      */
      unsigned getTimeAttackRecord();
      
      //! Obtém o record do modo TimeAttack da posição informada
      /**
      \param position: Posição do rank
      \return O record
      */
      unsigned getTimeAttackAtPosition(unsigned position);
      
      //! Salva o record de um nível
      /**
      \param level: Nível a saber o record
      \param value: Valor do record a salvar
      \return Se ocorreu com sucesso
      */
      bool setLevelPoint(unsigned level,unsigned value);
      
      //! Salva o record do modo TimeAttack
      /**
      Internamente a função já ordena o record de forma decrescente
      \param value: Valor do record a salvar
      \return Se ocorreu com sucesso
      */
      bool setTimeAttackRecord(unsigned value);
    }
  }
}

#endif