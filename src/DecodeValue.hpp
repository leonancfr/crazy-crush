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
#ifndef _DECODE_VALUE_HPP_
#define _DECODE_VALUE_HPP_ 1

#include <string>

//! Namespace antigo para funções comuns
namespace common {
  //! Converte uma string num double
  /**
  \param string: String a ser convertida
  \return O valor convertido
  */
  double decodeValue(const std::string string);
}

#endif
