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
#include "DecodeValue.hpp"
#include <cmath>
double common::decodeValue(const std::string valueStr){
	double value = 0;
    unsigned tmp = 0;
    bool div = false;
    double multiplier = 1;
    char signal = 1;
    for(std::size_t i=0;i<valueStr.length();i++){
      switch(valueStr[i]){
        case '-':
          signal = -1;
          break;
        case '.':
          multiplier = 2;
          break;
        case '0':
          if(multiplier == 1)
            value *=10;
          break;
        case '1':
          if(multiplier < 1)
            value += multiplier*1;
          else
            value = 10*value + 1;
          break;
        case '2':
          if(multiplier < 1)
            value += multiplier*2;
          else
            value = 10*value + 2;
          break;
        case '3':
          if(multiplier < 1)
            value += multiplier*3;
          else
            value = 10*value + 3;
          break;
        case '4':
          if(multiplier < 1)
            value += multiplier*4;
          else
            value = 10*value + 4;
          break;
        case '5':
          if(multiplier < 1)
            value += multiplier*5;
          else
            value = 10*value + 5;
          break;
        case '6':
          if(multiplier < 1)
            value += multiplier*6;
          else
            value = 10*value + 6;
          break;
        case '7':
          if(multiplier < 1)
            value += multiplier*7;
          else
            value = 10*value + 7;
          break;
        case '8':
          if(multiplier < 1)
            value += multiplier*8;
          else
            value = 10*value + 8;
          break;
        case '9':
          if(multiplier < 1)
            value += multiplier*9;
          else
            value = 10*value + 9;
          break;
        case 'm':
        case 'M':
          if((i == valueStr.length()-1)||
            ((valueStr[i+1] != 'e')&&(valueStr[i+1] == 'E'))){
              return signal*value/1000;
          }
          if((i <= valueStr.length()-3)&&
             ((valueStr[i+1] == 'e')||(valueStr[i+1] == 'E'))&&
             ((valueStr[i+2] == 'g')||(valueStr[i+2] == 'G'))){
              return signal*value*1000000;
          }
          break;
        case 'e':
        case 'E':
          for(std::size_t j=i+1;j<valueStr.length();j++){
            switch(valueStr[j]){
              case '-': div = true; break;
              case '0': tmp = tmp*10; break;
              case '1': tmp = tmp*10+1; break;
              case '2': tmp = tmp*10+2; break;
              case '3': tmp = tmp*10+3; break;
              case '4': tmp = tmp*10+4; break;
              case '5': tmp = tmp*10+5; break;
              case '6': tmp = tmp*10+6; break;
              case '7': tmp = tmp*10+7; break;
              case '8': tmp = tmp*10+8; break;
              case '9': tmp = tmp*10+9; break;
              default: break;
            }
          }
          if(div)
            return signal*value/pow(10,tmp);
          else
            return signal*value*pow(10,tmp);
          break;
        case 'G':
        case 'g':
          value *=1000000;
          /* no break */
        case 'k':
        case 'K':
          value *=1000;
          break;
        case 'p':
        case 'P':
          value /=1000;
          /* no break */
        case 'n':
        case 'N':
          value /=1000;
          /* no break */
        case 'u':
        case 'U':
          value /=1000000;
          break;
        default: break;
      }
      if(multiplier < 1)
        multiplier *= .1;
      else if(multiplier == 2)
        multiplier = .1;
    }
    return signal*value;
  }
